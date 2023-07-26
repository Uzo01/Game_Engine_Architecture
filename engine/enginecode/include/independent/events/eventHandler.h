/**\file eventHandler.h*/
#pragma once

#include "event.h"
#include <functional>


namespace Engine
{
	class EventHandler
	{
	public:
		void setOnCloseCallback(const std::function<bool(WindowCloseEvents&)>& fn) { m_onCloseCallback = fn; }
		void setOnResizeCallback(const std::function<bool(WindowResizeEvent&)>& fn) { m_onResizeCallback = fn; }
		void setOnFocusCallback(const std::function<bool(WindowFocusEvent&)>& fn) { m_onFocusCallback = fn; }
		void setOnLostFocusCallback(const std::function<bool(WindowLostFocusEvent&)>& fn) { m_onLostFocusCallback = fn; }
		void setOnMovedCallback(const std::function<bool(WindowmovedEvent&)>& fn) { m_onMovedCallback = fn; }
		void setOnKeyPressedCallback(const std::function<bool(KeyPressedEvent&)>& fn) { m_onKeyPressedCallback = fn; }
		void setOnKeyReleasedCallback(const std::function<bool(KeyReleasedEvent&)>& fn) { m_onKeyReleasedCallback = fn; }
		void setOnKeyTypedCallback(const std::function<bool(KeyTypedEvent&)>& fn) { m_onKeyTypedCallback = fn; }
		void setOnMoseButtonPressedCallback(const std::function<bool(ButtonPressedEvent&)>& fn) { m_onButtonPressedCallback = fn; }
		void setOnMouseButtonReleasedCallback(const std::function<bool(ButtonReleasedEvent&)>& fn) { m_onButtonReleasedCallback = fn; }
		void setOnMouseMovedCallback(const std::function<bool(MouseMovedEvent&)>& fn) { m_onMouseMovedCallback = fn; }
		void setOnMouseScrolledCallback(const std::function<bool(MouseScrolledEvent&)>& fn) { m_onMouseScrolledCallback = fn; }
		

		std::function<bool(WindowCloseEvents&)>& getOnCloseCallback() { return m_onCloseCallback; }
		std::function<bool(WindowResizeEvent&)>& getOnResizeCallback() { return m_onResizeCallback; }
		std::function<bool(WindowFocusEvent&)>& getFocusOnCallback() { return m_onFocusCallback; }
		std::function<bool(WindowLostFocusEvent&)>& getLostFocusOnCallback() { return m_onLostFocusCallback; }
		std::function<bool(WindowmovedEvent&)>& getOnMovedCallback() { return m_onMovedCallback; }
		std::function<bool(KeyPressedEvent&)>& getOnKeyPressedCallback() { return m_onKeyPressedCallback; }
		std::function<bool(KeyReleasedEvent&)>& getOnKeyReleasedCallback() { return m_onKeyReleasedCallback; }
		std::function<bool(KeyTypedEvent&)>& getOnKeyTypedCallback() { return m_onKeyTypedCallback; }
		std::function<bool(ButtonPressedEvent&)>& getOnButtonPressedCallback() { return m_onButtonPressedCallback; }
		std::function<bool(ButtonReleasedEvent&)>& getOnButtonReleasedCallback() { return m_onButtonReleasedCallback; }
		std::function<bool(MouseMovedEvent&)>& getOnMouseMovedCallback() { return m_onMouseMovedCallback; }
		std::function<bool(MouseScrolledEvent&)>& getOnMouseScrolledCallback() { return m_onMouseScrolledCallback; }
	private:
		std::function<bool(WindowCloseEvents&)> m_onCloseCallback = std::bind(&EventHandler::defaultOnClose, this, std::placeholders::_1);
		std::function<bool(WindowResizeEvent&)> m_onResizeCallback = std::bind(&EventHandler::defaultOnResize, this, std::placeholders::_1);
		std::function<bool(WindowFocusEvent&)> m_onFocusCallback = std::bind(&EventHandler::defaultOnFocus, this, std::placeholders::_1);
		std::function<bool(WindowLostFocusEvent&)> m_onLostFocusCallback = std::bind(&EventHandler::defaultOnLostFocus, this, std::placeholders::_1);
		std::function<bool(WindowmovedEvent&)> m_onMovedCallback = std::bind(&EventHandler::defaultOnMoved, this, std::placeholders::_1);
		std::function<bool(KeyPressedEvent&)> m_onKeyPressedCallback = std::bind(&EventHandler::defaultOnKeyPressed, this, std::placeholders::_1);
		std::function<bool(KeyReleasedEvent&)> m_onKeyReleasedCallback = std::bind(&EventHandler::defaultOnKeyReleased, this, std::placeholders::_1);
		std::function<bool(KeyTypedEvent&)> m_onKeyTypedCallback = std::bind(&EventHandler::defaultOnKeyTyped, this, std::placeholders::_1);
		std::function<bool(ButtonPressedEvent&)> m_onButtonPressedCallback = std::bind(&EventHandler::defaultOnButtonPressed, this, std::placeholders::_1);
		std::function<bool(ButtonReleasedEvent&)> m_onButtonReleasedCallback = std::bind(&EventHandler::defaultOnButtonReleased, this, std::placeholders::_1);
		std::function<bool(MouseMovedEvent&)> m_onMouseMovedCallback = std::bind(&EventHandler::defaultOnMouseMoved, this, std::placeholders::_1);
		std::function<bool(MouseScrolledEvent&)> m_onMouseScrolledCallback = std::bind(&EventHandler::defaultOnMouseScrolled, this, std::placeholders::_1);

		
		bool defaultOnClose(WindowCloseEvents& e) { return false; }
		bool defaultOnResize(WindowResizeEvent& e) { return false; }
		bool defaultOnFocus(WindowFocusEvent& e) { return false; }
		bool defaultOnLostFocus(WindowLostFocusEvent& e) { return false; }
		bool defaultOnMoved(WindowmovedEvent& e) { return false; }
		bool defaultOnMouseScrolled(MouseScrolledEvent& e) { return false; }
		bool defaultOnKeyPressed(KeyPressedEvent& e) { return false; }
		bool defaultOnKeyReleased(KeyReleasedEvent& e) { return false; }
		bool defaultOnKeyTyped(KeyTypedEvent& e) { return false; }
		bool defaultOnButtonPressed(ButtonPressedEvent& e) { return false; }
		bool defaultOnButtonReleased(ButtonReleasedEvent& e) { return false; }
		bool defaultOnMouseMoved(MouseMovedEvent& e) { return false; }
	};
}