#include "NFrameTimer.h"

#include <cmath>

#include "NTime.h"
namespace Nully
{
	void NFrameTimer::Initialize(uint32_t a_capFPS)
	{
		capFrames = a_capFPS;
		frameTime = 1.0f / capFrames;
		NTime::GetInstance().Reset();

		frameTimer.Reset();
		deltaTimer.Reset();
	}

	void NFrameTimer::Update()
	{
		// Update timers for deltaTime
		deltaTimer.Tick();

		frameTimer.Tick();
		frameTimer.Pause();
		if (frameTimer.DeltaTime() < frameTime)
		{
			float currentTime = NTime::GetInstance().TotalTime();

			float sleep = abs(frameTime - frameTimer.DeltaTime());

			while (NTime::GetInstance().TotalTime() - currentTime < sleep)
			{
				// wait
			}
		}
		//std::cout << "DeltaTime: " << deltaTimer.DeltaTime() << std::endl;

		NTime::GetInstance().Tick();
		frameTimer.Unpause();
	}

	NFrameTimer::NFrameTimer()
	{

	}
}
