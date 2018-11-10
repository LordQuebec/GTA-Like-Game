#pragma once

#include <Windows.h>
#include <direct.h>
#include <string>

#include "../../Debug/Debug.h"
#include "../../GameObject/GameObject.h"
#include "../../OpenGL/OpenGL.h"
#include "../../Window/Window.h"
#include "../Time Manager/TimeManager.h"

class GameManager
{
private:
	GameManager();
	static GameManager* m_instance;

	bool CheckExistance();//Check if the game is already running
	bool CheckHardDriveSpace();//Check if we have enough HardDrive space
	bool CheckMemory();//Check if we have enough Ram/Virtual Memory

	DWORD CalculateCPUSpeed();//Find the CPU speed

	void GetScreenInfo();

	bool m_quit = false;
	MSG m_msg = MSG();
	GLuint m_shaderProgramID = NULL;


	struct
	{
		std::wstring GameName;//Name of the process/Window
		
		//In Bytes
		DWORDLONG DiskSpaceNeeded;
		DWORDLONG DiskSpaceAvailable;

		DWORDLONG RamNeeded;

		DWORDLONG VirtualRamNeeded;
		DWORDLONG VirtualRamAvailable;

		DWORD CPUSpeed;//In MHz
	}m_GameInfo;

	struct
	{
		HMONITOR MonitorHandle;
		MONITORINFOEX MonitorInfo;

		glm::vec2 ScreenSize;
		glm::vec2 WorkAreaSize;
	}m_screenInfo;


public:

	static GameManager* CreateInstance();
	static GameManager* GetInstance() { return m_instance; }

	void GameInfo(const std::wstring AppName, DWORDLONG DiskSpaceNeeded, DWORDLONG RamNeeded, DWORDLONG VirtualMemoryNeeded);

	int InitializeGame(UINT targetFPS, HINSTANCE hInstance, WNDPROC winProc, int nCmdShow);
	WPARAM MainLoop();

	std::wstring GetGameName()const { return m_GameInfo.GameName; }
	DWORD GetCPUSpeed()const { return m_GameInfo.CPUSpeed; }

	glm::vec2& GetScreenResolution() { return m_screenInfo.ScreenSize; }
	glm::vec2& GetWorkAreaResolution() { return m_screenInfo.WorkAreaSize; }

	void Quit(const int ExitCode);

	~GameManager();
};


extern GameManager* Game;