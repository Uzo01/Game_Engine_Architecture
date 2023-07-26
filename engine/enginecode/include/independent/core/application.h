/** \file application.h
*/
#pragma once

#include "systems/log.h"
#include "core/timer.h"
#include "events/event.h"
#include "events/windowEvents.h"
#include "events/eventHandler.h"
#include "core/window.h"
#include "camera/cameraControllerEuler.h"
#include "inputPoller.h"

namespace Engine {

	/**
	\class Application
	Fundemental class of the engine. A singleton which runs the game loop infinitely.
	Provides ...
	*/

	class Application
	{
	protected:
		Application(); //!< Constructor

		std::shared_ptr<Log> m_logSysem;//!< logging system
		std::shared_ptr<System> m_windowSystem; //!< Window system
		
		std::shared_ptr<Window> m_window; //!< window
		std::shared_ptr<Timer> m_timer; //!< Timer
		std::shared_ptr<cameraControllerEuler> m_camera;//!< Camera

		glm::vec3 lightColour, lightPos, viewPos;
		

		bool onClose(WindowCloseEvents& e); //!< Run when window is closed 
	private:
		static Application* s_instance; //!< Singleton instance of the application
		bool m_running = true; //!< Is the application running?
	
	public:
		virtual ~Application(); //!< Deconstructor
		inline static Application& getInstance() { return *s_instance; } //!< Instance getter from singleton pattern
		void run(); //!< Main loop
	
	};

	// To be defined in users code
	Application* startApplication(); //!< Function definition which provides an entry hook
}