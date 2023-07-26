/** \file GLFWWindowImpl.h */
#pragma once

#include "core/window.h"
#include <GLFW/glfw3.h>

namespace Engine
{
	/** \class GLFWWindowImpl
	* Implementation of a window using GLFW
	*/

	class GLFWWindowImpl : public Window
	{
	public:
		GLFWWindowImpl(const WindowProperties& properties);
		virtual void init(const WindowProperties& properties) override; //!< initialise the window 
		virtual void close() override; //!< close the window 
		virtual void onUpdate(float timestep) override;
		virtual void setVSync(bool VSysnc) override;
		virtual inline unsigned int getWidth() const override { return m_props.width; }
		virtual inline unsigned int getHeight() const override { return m_props.height; }
		virtual inline void* getNativeWindow() const override { return m_native; }
		virtual inline bool isFullScreenMode() const override { return m_props.isFullScreen; }
		virtual inline bool isVSync() const override { return m_props.isVSync; }

	private:
		WindowProperties m_props; //!< Properties
		GLFWwindow* m_native; //!< Native GLFW window
		float m_aspectRatio; //!< Aspect ration
	};
}