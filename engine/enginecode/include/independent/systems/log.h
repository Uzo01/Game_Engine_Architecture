/**\file log.h */
#pragma once

#include "systems/system.h"
#include <spdlog/spdlog.h>
#include <memory>
#include <spdlog/fmt/ostr.h>
#include <glm/gtc/quaternion.hpp>
#include <glm/glm.hpp>

namespace Engine
{
	class Log : public System
	{
	public:
		virtual void start(SystemSignal init = SystemSignal::None, ...); //!< Start the logger
		virtual void stop(SystemSignal close = SystemSignal::None, ...); //!< Stop the logger
template<class ...Args>
static void debug(Args&&... args);
template<class ...Args>
static void error(Args&&... args);
template<class ...Args>
static void info(Args&&... args);
template<class ...Args>
static void trace(Args&&... args);
template<class ...Args>
static void warn(Args&&... args);
template<class ...Args>
static void release(Args&&... args);

	private:
		static std::shared_ptr<spdlog::logger> s_consleLogger; //!< Console logger
	};
	template<class ...Args>
	static void Log::debug(Args&&... args)
	{
#ifdef NG_DEBUG
		s_consleLogger->debug(std::forward<Args>(args)...);
#endif // !NG_DEBUG

		
	}
	template<class ...Args>
	static void Log::error(Args&&... args)
	{
#ifdef NG_DEBUG
		s_consleLogger->error(std::forward<Args>(args)...);
#endif // !NG_DEBUG
	}
	template<class ...Args>
	static void Log::info(Args&&... args)
	{
#ifdef NG_DEBUG
		s_consleLogger->info(std::forward<Args>(args)...);
#endif // !NG_DEBUG
	}
	template<class ...Args>
	static void Log::trace(Args&&... args)
	{
#ifdef NG_DEBUG
		s_consleLogger->trace(std::forward<Args>(args)...);
#endif // !NG_DEBUG
	}
	template<class ...Args>
	static void Log::warn(Args&&... args)
	{
#ifdef NG_DEBUG
		s_consleLogger->warn(std::forward<Args>(args)...);
#endif // !NG_DEBUG
	}
	template<class ...Args>
	static void Log::release(Args&&... args)
	{

		s_consleLogger->trace(std::forward<Args>(args)...);

	}
}