#pragma once

#include <fstream>
#include <map>

#include "../../Debug/Debug.h"
#include "../../Tool/Tool.h"

class InputManager
{
private:
	InputManager();
	static InputManager* m_instance;

	std::map<std::string, int> m_inputs;
	std::vector<int> m_keyDown;
	std::vector<int> m_keyUp;

	const SHORT LEFT_BIT = 1 << 15;
	const LPARAM PREVIOUS_KEY_STATE = 1 << 30;

public:
	static InputManager* CreateInstance();
	static InputManager* GetInstance() { return m_instance; }

	bool GetKey(const int Key)const;
	bool GetKeyDown(const int Key)const;
	bool GetKeyUp(const int Key)const;

	bool GetInput(const std::string& InputName)const;
	bool GetInputDown(const std::string& InputName)const;
	bool GetInputUp(const std::string& InputName)const;

	void SendKeyDown(WPARAM Key, LPARAM info);
	void SendKeyUp(WPARAM Key);

	void ClearKeys() { m_keyDown.clear(); m_keyUp.clear(); }

	bool LoadInputs(const std::string & p_path);

	~InputManager() { m_instance = nullptr; }
};

extern InputManager* Input;

#define ForwardKeyDown do{Input->SendKeyDown(wParam, lParam);}while(0)
#define ForwardKeyUp do{Input->SendKeyUp(wParam);}while(0)

#define ForwardKeys case WM_KEYDOWN: ForwardKeyDown; break; case WM_KEYUP: ForwardKeyUp; break;