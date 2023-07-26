/** \file timer.h*/
#pragma once

#include <chrono>
#include "systems/system.h"


namespace Engine
{
	/**
	\Class timer - interface for timer
	*/
	class Timer 
	{
	public:
		virtual void start() = 0; //!< Start the system timer
		virtual void reset() = 0; //!< Resets timer amd give elapsed time in seconds 
		virtual float getElapsedTime() = 0; //!< get time elapsed since start or reset
	};
	/**
	\Class timer - Chrono for timer
	*/
	class ChronoTimer : public Timer
	{
	public:
		virtual inline void start () { m_start = std::chrono::high_resolution_clock::now(); } //!< Start the system timer
		virtual inline void reset() {m_start = std::chrono::high_resolution_clock::now();} //!< Resets timer amd give elapsed time in seconds 
		virtual float getElapsedTime() override
		{
			m_stop = std::chrono::high_resolution_clock::now();
			std::chrono::duration<float, std::milli> elapsed = m_stop - m_start;
			return elapsed.count() / 1000.f;
		}
	private:
		std::chrono::high_resolution_clock::time_point m_start; //!< Start time for timer 
		std::chrono::high_resolution_clock::time_point m_stop; //!<  Stoop time for timer
		

	};
}