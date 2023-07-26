/** \file WinTimer*/
#pragma once
#include <Windows.h>
#include "include/independent/core/timer.h"

namespace Engine
{
	/** \class WinTimer
	*  Windows specific timer which use queryPerfomanceCount
	*/

	class WinTimer : public Timer
	{
	public:
		virtual void start() override
		{
			QueryPerformanceFrequency(&m_frequency);
			QueryPerformanceCounter(&m_startTimer);
		};
		virtual inline void reset()override { QueryPerformanceCounter(&m_startTimer); };

		virtual float getElapsedTime() override
		{
			QueryPerformanceCounter(&m_endTime);
			float result = (m_endTime.QuadPart - m_startTimer.QuadPart) * 1000.0 / m_frequency.QuadPart;
			result /= 1000.f;
			return result;
		}
	private:
		LARGE_INTEGER m_startTimer;
		LARGE_INTEGER m_endTime;
		LARGE_INTEGER m_frequency;

	};
}