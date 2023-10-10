/** \file winTimer */
#pragma once

#include<Windows.h>
#include "core/timer.h"

namespace Engine
{
	/** \class WinTimer 
	* Windows specific timer which uses queryPerformanceCount 
	*/

	class WinTimer : public Timer
	{
		virtual void start() override 
		{
			QueryPerformanceFrequency(&m_frequency);
			QueryPerformanceCounter(&m_startTime);
		};

		virtual inline void reset() override { QueryPerformanceCounter(&m_startTime); };
		
		virtual float getTimeElapsed() override
		{
			QueryPerformanceCounter(&m_endTime);
			float result = (m_endTime.QuadPart - m_startTime.QuadPart) * 1000.0 / m_frequency.QuadPart;
			result /= 1000.f;
			return result;
		}
	private:
		LARGE_INTEGER m_startTime; //!< Start time for timer
		LARGE_INTEGER m_endTime; //!< End time for timer
		LARGE_INTEGER m_frequency; //!< Ticks per second of this CPU
	};
}