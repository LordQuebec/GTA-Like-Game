#pragma once

#include "Manager\Game Manager\GameManager.h"

#include <Windows.h>
#include <tchar.h>


//Main Win32 function
int CALLBACK WinMain(
	_In_ HINSTANCE,
	_In_ HINSTANCE,
	_In_ LPSTR,
	_In_ int
);

//Precess Win32 Messages
LRESULT CALLBACK WndProc(
	_In_ HWND,
	_In_ UINT,
	_In_ WPARAM,
	_In_ LPARAM
);