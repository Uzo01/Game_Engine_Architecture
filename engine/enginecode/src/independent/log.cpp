/** \file log.cpp */
#include "engine_pch.h"
#include "systems/log.h"
#include <engine.h>
namespace Engine {
	 std::shared_ptr<spdlog::logger> Log::s_consleLogger = nullptr;
	// std::shared_ptr<spdlog::logger> Log::s_fileLogger = nullptr;

	void Log::start(SystemSignal init, ...)
	{
		spdlog::set_pattern("%^[%T]: %v%$");
		spdlog::set_level(spdlog::level::trace);

		s_consleLogger = spdlog::stderr_color_mt("Console");
		/*

		char filepath[256] = "log/";
		char time[128];

		std::time_t t = std::time(nullptr);
		std::strftime(time, sizeof(time), "%d_%m_%y_%I_%M_%S", std::localtime(&t));
		strcat_s(filepath, time);
		strcat_s(filepath, "txt");
		s_fileLogger = spdlog::basic_logger_mt("file", "log.txt");*/
	}

	void Log::stop(SystemSignal close, ...)
	{
		s_consleLogger->info("Stopping consloe logger");
		s_consleLogger.reset();
	}

}

