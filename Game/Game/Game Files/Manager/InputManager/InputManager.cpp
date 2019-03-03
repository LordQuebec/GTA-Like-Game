#include "InputManager.h"


InputManager* InputManager::m_instance = nullptr;

InputManager::InputManager()
{

}


InputManager* InputManager::CreateInstance()
{
	if (!m_instance)
		m_instance = sNew InputManager();
	return m_instance;
}


bool InputManager::LoadInputs(const std::string& p_path)
{
	std::string line = "";//Line of text from the stream
	std::vector<std::string> params;
	int keyCode = 0;

	std::ifstream fileStream(p_path, std::ios::in);

	//Read the input file
	if (fileStream.is_open())
	{
		while (getline(fileStream, line))
		{
			Tool::SplitStringWords(line, params);
			keyCode = std::stoi(params[1]);
			m_inputs.insert(std::pair<std::string, int>(params[0], keyCode));
			params.clear();
		}
		fileStream.close();


		return true;
	}
	return false;

	m_inputs.insert(std::pair<std::string, int>("", 0));
}



bool InputManager::GetKey(const int p_key)const
{
	return GetAsyncKeyState(p_key); &LEFT_BIT;
}

bool InputManager::GetKeyDown(const int p_key)const
{
	return std::find(m_keyDown.begin(), m_keyDown.end(), p_key) != m_keyDown.end();
}

bool InputManager::GetKeyUp(const int p_key)const
{
	return std::find(m_keyUp.begin(), m_keyUp.end(), p_key) != m_keyUp.end();
}


bool InputManager::GetInput(const std::string &p_inputName)const
{
	return GetAsyncKeyState(m_inputs.at(p_inputName)) & LEFT_BIT;//0x8000;
}

bool InputManager::GetInputDown(const std::string& p_inputName)const
{
	return std::find(m_keyDown.begin(), m_keyDown.end(), m_inputs.at(p_inputName)) != m_keyDown.end();
}

bool InputManager::GetInputUp(const std::string& p_inputName)const
{
	return std::find(m_keyUp.begin(), m_keyUp.end(), m_inputs.at(p_inputName)) != m_keyUp.end();
}




void InputManager::SendKeyDown(WPARAM p_key, LPARAM p_info)
{
	if (!(p_info & PREVIOUS_KEY_STATE))//If the key was not already up
		m_keyDown.push_back(p_key);
}

void InputManager::SendKeyUp(WPARAM p_key)
{
	m_keyUp.push_back(p_key);
}



InputManager* Input = InputManager::CreateInstance();