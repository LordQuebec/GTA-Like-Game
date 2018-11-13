#include "GameManager.h"

#include "../../VBO/VBO.h"

GameManager* GameManager::m_instance = nullptr;

GameManager::GameManager()
	:m_GameState(Start)
{}


GameManager* GameManager::CreateInstance()
{
	if (!m_instance)
		m_instance = sNew GameManager();
	return m_instance;
}

void GameManager::GameInfo(std::wstring p_name, DWORDLONG p_diskSpace, DWORDLONG p_ram, DWORDLONG p_virtualRam)
{
	//ZeroMemory(&m_GameInfo, sizeof(m_GameInfo));

	m_GameInfo.GameName = p_name;
	m_GameInfo.DiskSpaceNeeded = p_diskSpace;
	m_GameInfo.RamNeeded = p_ram;
	m_GameInfo.VirtualRamNeeded = p_virtualRam;
	m_GameInfo.CPUSpeed = 0;
}

int GameManager::InitializeGame(UINT p_tFPS, HINSTANCE p_hInstance, WNDPROC p_wndProc, int p_nCmdShow)
{
	//Check if the app exist and if we have enough HardDrive/Ram
	//Get the CPU Speed
	if (CheckExistance())
		return 1;
	if (!CheckHardDriveSpace())
	{
		ERR_MSG("Not Enough Hard Drive Space");
		return 2;
	}
	if (!CheckMemory())
	{
		ERR_MSG("Not enough Ram Or Virtual Memory");
		return 3;
	}
	if (!CalculateCPUSpeed())
	{
		ERR_MSG("Can't find CPU Speed");
		return 4;
	}

	Time = TimeManager::CreateInstance();
	Time->SetTargetFPS(p_tFPS);

	//Lang MGR
	//Script MGR
	//Event MGR

	Window = WindowMgr::CreateInstance();
	Window->Create(m_GameInfo.GameName, p_hInstance, p_wndProc, p_nCmdShow);

	Input = InputManager::CreateInstance();
	Input->LoadInputs("Ressources/Config/Input.txt");

	GetScreenInfo();//Get Resolution and name of the monitor

	OpenGL = OGL::CreateInstance();
	OpenGL->Enable(Window->GetHandle(), Color(1, 0, 1, 1), Window->GetSize());
	
	m_shaderProgramID = OpenGL->LoadShader("Ressources/Shaders/Default/VertexShader.vs", "Ressources/Shaders/Default/FragmentShader.fs");

	if (m_shaderProgramID == 0)
	{
		ERR_MSG("Error Creating the default shader");
		return 5;
	}

	//Splash screen
	//check set save game directory

	return 0;
}

WPARAM GameManager::MainLoop()
{
	GameObject::CallStart();//Start all GameObjects
	GameObject::CallAwake();

	VBO test;

	std::vector<glm::vec3>pos = { glm::vec3(-1, -1, 0), glm::vec3(1, -1, 0), glm::vec3(0, 1, 0) };
	std::vector<glm::vec4>color = { glm::vec4(1, 0, 0, 1), glm::vec4(0, 1, 0, 1), glm::vec4(0, 0, 1, 1) };

	test.SendData(GL_STATIC_DRAW, pos, color);

	while(!m_quit)//Main Loop
	{
		//Check if we got a message
		while (PeekMessage(&m_msg, NULL, 0, 0, PM_REMOVE))
		{
			m_quit = m_msg.message == WM_QUIT;//Do we quit the loop

			TranslateMessage(&m_msg);
			DispatchMessage(&m_msg);
		}

		GameObject::CallFrameStartUpdate();


		if (Input->GetInput("walk"))
			MSG_BOX("KeyPress", "OK");

		OpenGL->ClearScreen();

		GameObject::CallUpdate();
		GameObject::CallRender();
		
		glUseProgram(m_shaderProgramID);
		test.Render();

		//EnableGUI
		GameObject::CallOnGUI();
		//DisableGUI

		OpenGL->SwapBuffer();//Display Frame

		GameObject::CallFrameEndUpdate();

		Sleep(static_cast<DWORD>(Time->GetSleepTime()));
	}

	OpenGL->Disable(Window->GetHandle());

	GameObject::CallEnd();

	sDelete(OpenGL);
	sDelete(Window);
	sDelete(Time);

	GameObject::Clean();

	return m_msg.wParam;
}


void GameManager::Quit(const int p_exitCode)
{
	m_quit = false;
	m_GameState = GameState::Quit;
	PostQuitMessage(p_exitCode);//Send Quit Message To Win32
}

bool GameManager::CheckExistance()
{
	//Create Mutex for the game
	HANDLE handle = CreateMutex(NULL, TRUE, std::wstring(m_GameInfo.GameName.begin(), m_GameInfo.GameName.end()).c_str());

	//If the mutex creation failed
	if (GetLastError() != ERROR_SUCCESS)
	{
		//Find previous window
		HWND hwnd = FindWindow(m_GameInfo.GameName.c_str(), NULL);
		if (hwnd)
		{
			ShowWindow(hwnd, SW_SHOWNORMAL);
			SetFocus(hwnd);
			SetForegroundWindow(hwnd);
			SetActiveWindow(hwnd);
		}
		return true;//The game is already running
	}
	return false;
}

bool GameManager::CheckHardDriveSpace()
{
	struct _diskfree_t diskFree;
	_getdiskfree(_getdrive(), &diskFree);

	unsigned __int64 const neededClusters = m_GameInfo.DiskSpaceNeeded / (diskFree.sectors_per_cluster * diskFree.bytes_per_sector);

	m_GameInfo.DiskSpaceAvailable = diskFree.avail_clusters * diskFree.sectors_per_cluster * diskFree.bytes_per_sector;

	if (diskFree.avail_clusters < neededClusters)
	{
		//Not enough disk space
		return false;
	}
	return true;
}

bool GameManager::CheckMemory()
{
	MEMORYSTATUSEX status;
	GlobalMemoryStatusEx(&status);//Get Ram/Virtual Ram info

	if (status.ullTotalPhys < m_GameInfo.RamNeeded || status.ullAvailVirtual < m_GameInfo.VirtualRamNeeded)
	{
		return false;
	}
	m_GameInfo.VirtualRamAvailable = status.ullAvailVirtual;

	//Allocate a block of vRam
	char* buff = sNew char[m_GameInfo.VirtualRamNeeded];

	if (buff)//If the allocation worked wipe the block
		delete buff;
	else
		return false;//Not enough continuous mem

	return true;
}

DWORD GameManager::CalculateCPUSpeed()
{
	DWORD bufsize = sizeof(DWORD);
	DWORD dwMHz = 0;
	DWORD type = REG_DWORD;
	HKEY hKey;

	//Open the key of the proc speed
	long lError = RegOpenKeyEx(HKEY_LOCAL_MACHINE, TEXT("HARDWARE\\DESCRIPTION\\System\\CentralProcessor\\0"), 0, KEY_READ, &hKey);

	if (lError == ERROR_SUCCESS)
		RegQueryValueEx(hKey, TEXT("~MHz"), NULL, &type, (LPBYTE)&m_GameInfo.CPUSpeed, &bufsize);
	return m_GameInfo.CPUSpeed;
}

void GameManager::GetScreenInfo()
{
	m_screenInfo.MonitorHandle = MonitorFromWindow(Window->GetHandle(), MONITOR_DEFAULTTONEAREST);//GetHandle of the monitor
	m_screenInfo.MonitorInfo.cbSize = sizeof(MONITORINFOEX);

	GetMonitorInfo(m_screenInfo.MonitorHandle, &m_screenInfo.MonitorInfo);//GetInfo on the monitor

	//Screen resolution
	m_screenInfo.ScreenSize.x = m_screenInfo.MonitorInfo.rcMonitor.right - m_screenInfo.MonitorInfo.rcMonitor.left;
	m_screenInfo.ScreenSize.y = m_screenInfo.MonitorInfo.rcMonitor.bottom - m_screenInfo.MonitorInfo.rcMonitor.top;

	//Work Area Resolution
	m_screenInfo.WorkAreaSize.x = m_screenInfo.MonitorInfo.rcWork.right - m_screenInfo.MonitorInfo.rcWork.left;
	m_screenInfo.WorkAreaSize.y = m_screenInfo.MonitorInfo.rcWork.bottom - m_screenInfo.MonitorInfo.rcWork.top;
}


GameManager::~GameManager()
{
	m_instance = nullptr;
}


GameManager* Game = nullptr;