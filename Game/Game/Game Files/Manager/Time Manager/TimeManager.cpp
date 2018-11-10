#include "TimeManager.h"

TimeManager* TimeManager::m_instance = nullptr;


TimeManager* TimeManager::CreateInstance()
{
	if (!m_instance)
		m_instance = sNew TimeManager();
	return m_instance;
}

TimeManager::TimeManager()
	:GameObject(this, "TimeManager"), m_targetFps(60), m_maxElapsedTime(1000/static_cast<float>(60)), m_elapsedTime(0), m_currentFPS(60), m_smootherdFPS(60)
{
	m_index = GetLastInstance();

	for (auto previousFPS : m_previousFPS)
		previousFPS = 60;

	QueryPerformanceFrequency(&m_frequency);
	QueryPerformanceCounter(&m_time);

	m_lastFrame = static_cast<float>(m_time.QuadPart);
}

float TimeManager::CalculateElapsedTime()
{
	QueryPerformanceCounter(&m_time);
	return m_elapsedTime = static_cast<float>((m_currentFrame = static_cast<float>(m_time.QuadPart)) - m_lastFrame) / m_frequency.QuadPart;
}

float TimeManager::GetSleepTime()
{
	return m_maxElapsedTime > CalculateElapsedTime() ? m_maxElapsedTime - m_elapsedTime : 0.00001f;
}

void TimeManager::SetTargetFPS(const unsigned int p_fps)
{
	m_maxElapsedTime = 1000 / static_cast<float>(m_targetFps = p_fps);
}


void TimeManager::FrameStartUpdate()
{
	CalculateElapsedTime();
	m_currentFPS = (m_currentFPS + 1) % (NUMBER_OF_PREFIOUS_FPS - 1);
	m_previousFPS[m_currentFPS] = 1.0f / m_elapsedTime;

	m_lastFrame = m_currentFrame;

	m_smootherdFPS = 0;
	for (auto previousFPS : m_previousFPS)
		m_smootherdFPS += previousFPS;
	m_smootherdFPS /= NUMBER_OF_PREFIOUS_FPS;
}

TimeManager* Time = nullptr;