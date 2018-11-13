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

	const SHORT LEFT_BIT = 1 << 15;

public:
	static InputManager* CreateInstance();
	static InputManager* GetInstance() { return m_instance; }

	bool GetKey();
	bool GetKeyDown();
	bool GetKeyUp();

	bool GetInput(const std::string& InputName)const;
	bool GetInputDown(const std::string& InputName)const;
	bool GetInputUp(const std::string& InputName)const;

	bool LoadInputs(const std::string & p_path);

	~InputManager() { m_instance = nullptr; }
};

extern InputManager* Input;