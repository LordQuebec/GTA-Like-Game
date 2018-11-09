#pragma once

#include <Windows.h>
#include <string>

#include "../../Debug/Debug.h"

class GameManager
{
private:
	GameManager();

	bool CheckExistance();//Check if the game is already running
	bool CheckHardDriveSpace();//Check if we have enough HardDrive space
	bool CheckMemory();//Check if we have enough Ram/Virtual Memory

	DWORD CalculateCPUSpeed();//Find the CPU speed

	void GetScreenInfo();

	static GameManager* m_instance;
	
	//Window* m_mainWindow;

	bool m_quit = false;
	MSG m_msg = MSG();
	//GLuint m_shaderProgramID = NULL;


	struct
	{
		std::string GameName;//Name of the process/Window
		
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
		HMONITOR m_monitorHandle;
		MONITORINFOEX m_monitorInfo;

		//glm
	}m_screenInfo;


public:

	static GameManager* CreateInstance();
	static GameManager* GetInstance() { return m_instance; }

	void GameInfo(const std::string AppName, DWORDLONG DiskSpaceNeeded, DWORDLONG RamNeeded, DWORDLONG VirtualMemoryNeeded);

	int InitializeGame(std::string &windowConfigPath, HINSTANCE hInstance, WNDPROC winProc);
	WPARAM MainLoop(MSG &msgw);

	std::string GetGameName()const { return m_GameInfo.GameName; }
	DWORD GetCPUSpeed()const { return m_GameInfo.CPUSpeed; }

	void Quit(const int ExitCode);

	//Window* GetMainWindowPointer() { return m_mainWindow; }

	~GameManager();
};