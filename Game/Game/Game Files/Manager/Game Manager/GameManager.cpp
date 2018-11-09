#include "GameManager.h"

GameManager* GameManager::m_instance = nullptr;

GameManager::GameManager()
{}


GameManager* GameManager::CreateInstance()
{
	if (!m_instance)
		m_instance = sNew GameManager();
	return m_instance;
}


void GameManager::Quit(const int p_exitCode)
{
	m_quit = false;
	PostQuitMessage(p_exitCode);//Send Quit Message To Win32
}

GameManager::~GameManager()
{
	m_instance = nullptr;
}