/** \file window.h*/
#pragma once
#include "events/eventHandler.h"
#include "include/platform/GLFWSystem/OpenGl_GLFWGraphicsContext.h"
namespace Engine
{
	/** \class window
	* Astract windows base class. All implemented windows should code th this interface.
	*/

	struct WindowProperties
	{
		char* title;
		uint32_t width;
		uint32_t height;
		bool isFullScreen;
		bool isVSync;

		WindowProperties(char* p_title = "My Window", uint32_t p_width = 800, uint32_t p_height = 600, bool p_fullscreen = false) : title(p_title), width(p_width), height(p_height), isFullScreen(p_fullscreen) {};

	};
	class Window
	{
	public:
		virtual void init(const WindowProperties& properties) = 0; //!< initialise the window
		virtual void close() = 0; //!< Close window
		virtual ~Window() {}; //!< Window construtor
		virtual void onUpdate(float timestep) = 0; //!< update window
		virtual void setVSync(bool VSync) = 0;
		virtual unsigned int getWidth() const = 0; //!< Get window width
		virtual unsigned int getHeight() const = 0; //!< Get window height
		virtual void* getNativeWindow() const = 0; //!< Get Native window 
		virtual bool isFullScreenMode() const = 0; //!< Check fullscreen mode
		virtual bool isVSync() const = 0; //!<

		inline EventHandler& getEventHandler() { return m_handler; }

		static Window* create(const WindowProperties& properties = WindowProperties());
	protected:
		EventHandler m_handler;
		std::shared_ptr<OpenGl_GLFWGraphicsContext> m_graphicsContext;//!< shared pointer to grahics context
	};
}
