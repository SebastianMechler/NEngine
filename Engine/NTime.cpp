#include "NTime.h"

namespace Nully
{
	NTime& NTime::GetInstance()
	{
		static NTime g_time;
		return g_time;
	}
	float NTime::DeltaTime()
	{
		return m_gameTimer.DeltaTime();
	}

	float NTime::TotalTime()
	{
		return m_gameTimer.TotalTime();
	}

	void NTime::Tick()
	{
		m_gameTimer.Tick();
	}

	void NTime::Reset()
	{
		m_gameTimer.Reset();
	}

	NTime::NTime()
	{

	}
}

