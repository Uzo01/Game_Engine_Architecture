/** \file entryPoint.h
*/
#pragma once

#include "core/application.h"

extern Engine::Application* Engine::startApplication();

int main(int argc, char** argv)
{
	auto application = Engine::startApplication();//!< Through engine start application
	application->run();//!< run application
	delete application;//!< delete application

	return 0;
}

