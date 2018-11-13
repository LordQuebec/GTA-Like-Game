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


bool InputManager::GetInput(const std::string &p_inputName)const
{
	return GetAsyncKeyState(m_inputs.at(p_inputName)) & LEFT_BIT;//0x8000;
}



InputManager* Input = InputManager::CreateInstance();