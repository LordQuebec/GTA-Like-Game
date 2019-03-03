#include "main.h"

int CALLBACK WinMain(
	_In_ HINSTANCE hInstance,
	_In_ HINSTANCE hPrevInstance,
	_In_ LPSTR	   lpCmdLine,
	_In_ int	   nCmdShow)
{

	Game = GameManager::CreateInstance();

	int exitCode = 0;

	//std::wstring GameName = L"nGTA";
	//std::wstring horn = L"\U0001F918";

	int launchParams[6];

	//Load base info
	//Disk Ram vRam, target, winsize
	LoadLaunchConfig(launchParams);

	Game->GameInfo(L"nGTA\U0001F918", launchParams[0], launchParams[1], launchParams[2]);
	exitCode = Game->InitializeGame(launchParams[3], launchParams[4], launchParams[5], hInstance, WndProc, nCmdShow);

	if (exitCode)//If the initialization failed
		return exitCode;//Quit

	exitCode = static_cast<int>(Game->MainLoop());

	sDelete(Game);
	
	_CrtDumpMemoryLeaks();

	return exitCode;
}


LRESULT CALLBACK WndProc(
	_In_ HWND hwnd,
	_In_ UINT uMsg,
	_In_ WPARAM wParam,
	_In_ LPARAM lParam
)
{
	switch (uMsg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	WindowHandling
	ForwardKeys
	
	case WM_SYSCOMMAND:
		if (wParam == SC_CLOSE)
		{
			PostQuitMessage(0);//wParam;//TODO: Handle Forced Exit
			return NULL;
		}
		break;
		
	default:
		return DefWindowProc(hwnd, uMsg, wParam, lParam);
		break;
	}
	
	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}


void LoadLaunchConfig(int p_values[])
{
	std::string line = "";
	std::vector<std::string> params;

	std::ifstream fStream("Ressources/Config/LaunchConfig.txt", std::ios::in);

	if (fStream.is_open())
	{
		for (int i = 0; i < 6; ++i)
		{
			getline(fStream, line);
			Tool::SplitStringWords(line, params);

			p_values[i] = std::stoi(params[1]);
			params.clear();
		}
	}
}