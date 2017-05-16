#pragma once

#include "NGameTimer.h"

namespace Nully
{
	class NTime
	{
	public:
		static NTime& GetInstance();
		float DeltaTime();
		float TotalTime();
		void Tick();
		void Reset();

	private:
		NTime();
		NTime(const NTime&);
		NGameTimer m_gameTimer;
	};
}
