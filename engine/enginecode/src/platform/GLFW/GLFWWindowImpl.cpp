/* \ file GLFWWindowImpl.cpp */
#include "engine_pch.h"
#include "platform/GLFWSystem/GLFWWindowImpl.h"
#include "platform/GLFWSystem/OpenGl_GLFWGraphicsContext.h"
#include "systems/log.h"


namespace Engine
{
#ifdef NG_PLATFORM_WINDOWS
	Window* Window::create(const WindowProperties& properties)
{
		return new GLFWWindowImpl(properties);
}
#endif

	GLFWWindowImpl::GLFWWindowImpl(const WindowProperties& properties)
	{
		init(properties);
	}
	void GLFWWindowImpl::init(const WindowProperties& properties)
	{
		m_props = properties;

		m_aspectRatio = static_cast<float>(m_props.width) / static_cast<float>(m_props.height);
		if (m_props.isFullScreen)
		{
			Log::error("Fullscreen not yet implemented");
		}
		else
		{
			m_native = glfwCreateWindow(m_props.width, m_props.height, m_props.title, nullptr, nullptr);
		}

		m_graphicsContext.reset(new OpenGl_GLFWGraphicsContext(m_native));

		m_graphicsContext->init();

		glfwSetWindowUserPointer(m_native, &m_handler);

		glfwSetWindowCloseCallback(m_native, 
			[](GLFWwindow* window)
			{
				auto handler = (EventHandler*)glfwGetWindowUserPointer(window);
				auto& callback = handler->getOnCloseCallback();

				WindowCloseEvents wce;
				callback(wce);
			}
		);
	}
	void GLFWWindowImpl::close()
	{
		glfwDestroyWindow(m_native);
	}
	void GLFWWindowImpl::onUpdate(float timestep)
	{
		glfwPollEvents();
		m_graphicsContext->swapBuffer();
	}
	void GLFWWindowImpl::setVSync(bool VSync)
	{
		if (VSync)
		{
			glfwSwapInterval(1);
		}
		else
		{
			m_props.isVSync = VSync;
			if (m_props.isVSync) { glfwSwapInterval(1); }
			else {glfwSwapInterval(0); }
		}
		
	}
}


