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

	Game->GameInfo(L"nGTA\U0001F918", 0, 0, 0);
	exitCode = Game->InitializeGame(60, hInstance, WndProc, nCmdShow);

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