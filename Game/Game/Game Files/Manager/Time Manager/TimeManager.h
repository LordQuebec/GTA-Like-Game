#pragma once

#include <Windows.h>

#include "../../Debug/Debug.h"
#include "../../GameObject/GameObject.h"

class TimeManager : public GameObject
{
private:
	TimeManager();
	static TimeManager* m_instance;

	LARGE_INTEGER m_frequency;
	LARGE_INTEGER m_time;

	float m_elapsedTime;
	float m_currentFrame;
	float m_lastFrame;

	unsigned int m_targetFps;
	float m_maxElapsedTime;

	int m_currentFPS;
	float m_smootherdFPS;
	static const int NUMBER_OF_PREFIOUS_FPS = 50;
	float m_previousFPS[NUMBER_OF_PREFIOUS_FPS];

protected:
	void FrameStartUpdate();

public:
	static TimeManager* CreateInstance();

	float CalculateElapsedTime();

	float DeltaTime() { return CalculateElapsedTime(); }

	float GetFPS()const { return 1.0f / m_elapsedTime; }
	float GetSmoothedFPS()const { return m_smootherdFPS; }
	unsigned int GetTargetFPS()const { return m_targetFps; }
	float GetSleepTime();

	void SetTargetFPS(const unsigned int FPS);

	~TimeManager();
};

extern TimeManager* Time;