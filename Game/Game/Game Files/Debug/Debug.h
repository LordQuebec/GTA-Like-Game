#pragma once

#include<Windows.h>
#include<tchar.h>
#include <string>


#define STRINGIZE(x) STRINGIZE_EXPAND(x)
#define STRINGIZE_EXPAND(x) #x
#define LINE_STRING STRINGIZE(__LINE__) //Line number converted to string for Message box

#define sDelete(var) do{delete var; var = nullptr;} while(0)

#ifdef _DEBUG


#define sNew new(_NORMAL_BLOCK, __FILE__, __LINE__)
#define ERR_MSG(str) do{OutputDebugString(_T( str "\n\nFile: " __FILE__ "\nLine: " LINE_STRING "\n")); MessageBox(NULL, _T( str "\n\nFile: " __FILE__ "\nLine: " LINE_STRING "\n"), _T("ERROR"), NULL);} while(0)

#else

#define sNew new
#define ERR_MSG(str) do{ MessageBox(NULL, _T( str "\n\nFile: " __FILE__ "\nLine: " LINE_STRING "\n" ), _T("ERROR"), NULL);} while(0)


#endif // __DEBUG
