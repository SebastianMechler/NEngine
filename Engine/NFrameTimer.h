#pragma once

#include "NTypes.h"
#include "NGameTimer.h"

namespace Nully
{
	class NFrameTimer
	{
	public:
		void Initialize(uint32_t a_capFPS = 60);
		void Update();

		NFrameTimer();

	private:
		NGameTimer deltaTimer;
		NGameTimer frameTimer;

		uint32_t capFrames;
		float frameTime;
	};
}