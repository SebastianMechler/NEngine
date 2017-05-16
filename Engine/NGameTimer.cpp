#include "NGameTimer.h"

#include <Windows.h>

namespace Nully
{
	NGameTimer::NGameTimer()
		: m_baseTime(0)
		, m_frequency(0)
		, m_deltaTime(0)
		, m_currentDeltaTime(0.0f)
		, m_pauseTimeStart(0)
		, m_pauseTime(0.0f)
	{
		QueryPerformanceFrequency((LARGE_INTEGER*)&m_frequency);
	}

	float NGameTimer::TotalTime() const
	{
		__int64 currentTime = 0;
		QueryPerformanceCounter((LARGE_INTEGER*)&currentTime);

		float totalTime = (float)((double)(currentTime - m_baseTime) / (double)m_frequency);

		// power-mode may cause negative values or moving on other processor
		if (totalTime < 0.0f)
		{
			totalTime = 0.0f;
		}

		return totalTime;
	}

	float NGameTimer::DeltaTime() const
	{
		return m_currentDeltaTime;
	}

	void NGameTimer::Reset()
	{
		__int64 currentTime = 0;
		QueryPerformanceCounter((LARGE_INTEGER*)&currentTime);

		m_baseTime = currentTime;
		m_deltaTime = currentTime;
		m_pauseTime = 0.0f;
	}

	void NGameTimer::Tick()
	{
		__int64 currentTime = 0;
		QueryPerformanceCounter((LARGE_INTEGER*)&currentTime);

		m_currentDeltaTime = (float)((double)(currentTime - m_deltaTime) / (double)m_frequency);

		// pause adjustments
		m_currentDeltaTime -= m_pauseTime;

		// power-mode may cause negative values or moving on other processor
		if (m_currentDeltaTime < 0.0f)
		{
			m_currentDeltaTime = 0.0f;
		}

		// prepare for next tick
		m_deltaTime = currentTime;

		// reset pause time
		m_pauseTime = 0.0f;
	}

	void NGameTimer::Pause()
	{
		QueryPerformanceCounter((LARGE_INTEGER*)&m_pauseTimeStart);
	}

	void NGameTimer::Unpause()
	{
		__int64 currentTime = 0;
		QueryPerformanceCounter((LARGE_INTEGER*)&currentTime);

		m_pauseTime = (float)((double)(currentTime - m_pauseTimeStart) / (double)m_frequency);
	}
}
