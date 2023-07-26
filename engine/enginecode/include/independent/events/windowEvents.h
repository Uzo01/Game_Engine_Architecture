/* \file windowEvents.h
*/
#pragma once

#include "events.h"

#include <glm/glm.hpp>

namespace Engine
{
	class WindowCloseEvents : public Event
	{
	public:
		static EventTypes getStaticType() { return EventTypes::WindowClose; }//!< Return static Key
		virtual inline EventTypes getEventTypes() const override { return EventTypes::WindowClose; }//!< Get the event type
		virtual int32_t getCategoryFlags() const override { return EventCategoryWindow; }
	};

	class WindowResizeEvent : public Event
	{
	public:
		WindowResizeEvent(int32_t  width, int32_t height) : m_width(width), m_height(height) {}
		static EventTypes getStaticType() { return EventTypes::WindowResize; }//!< Return static Key
		virtual inline EventTypes getEventTypes() const override { return EventTypes::WindowResize; }//!< Get the event type
		virtual int32_t getCategoryFlags() const override { return EventCategoryWindow; }

		virtual inline int32_t getWidth() const { return m_width; }
		virtual inline int32_t getHeight() const { return m_height; }
		inline glm::ivec2 getSize() const { return { m_width, m_height }; }

	private:
		int32_t m_width; //!< Window width after resize
		int32_t m_height; //!< Wiindow hieght after resize
	};

	class WindowFocusEvent : public Event
	{
	public:
		static EventTypes getStaticType()
		{
			return EventTypes::WindowFocus;//!< return static Key
		}
		virtual inline EventTypes getEventTypes() const override
		{
			return EventTypes::WindowFocus;
		}
		virtual int32_t getCategoryFlags() const override
		{
			return EventCategoryWindow;
		}
	};
	
	class WindowLostFocusEvent : public Event
	{
	public:

		static EventTypes getStaticType()
		{
			return EventTypes::WindowLostFocus;//!< return static Key
		}
		virtual inline EventTypes getEventTypes() const override
		{
			return EventTypes::WindowLostFocus;
		}
		virtual int32_t getCategoryFlags() const override
		{
			return EventCategoryWindow;
		}
	};

	class WindowmovedEvent : public Event
	{public:
		static EventTypes getStaticTypes() { return EventTypes::Windowmoved; }
		virtual inline EventTypes getEventTypes() { return EventTypes::Windowmoved; }
		virtual int32_t getCategoryFlags()const override { return EventCategoryWindow; }
	};

	class KeyPressedEvent : public Event
	{
	public:

		static EventTypes getStaticTypes() { return EventTypes::KeyPressed; }
		virtual inline EventTypes getEventTypes() {return EventTypes::KeyPressed;}
		virtual int32_t getCategoryFlags() const override { return EventCategoryWindow; }
	};

	class KeyReleasedEvent : public Event
	{
	public:

		static EventTypes getStaticTypes() { return EventTypes::KeyReleased; }
		virtual inline EventTypes getEventTypes() { return EventTypes::KeyReleased; }
		virtual int32_t getCategoryFlags() const override { return EventCategoryWindow; }
	};

	class KeyTypedEvent : public Event
	{
	public:

		static EventTypes getStaticTypes() { return EventTypes::KeyTyped; }
		virtual inline EventTypes getEventTypes() { return EventTypes::KeyTyped; }
		virtual int32_t getCategoryFlags() const override { return EventCategoryWindow; }
	};

	class ButtonPressedEvent : public Event
	{
	public:

		static EventTypes getStaticTypes() { return EventTypes::MoseButtonPressed; }
		virtual inline EventTypes getEventTypes() { return EventTypes::MoseButtonPressed; }
		virtual int32_t getCategoryFlags() const override { return EventCategoryWindow; }
	};
	class ButtonReleasedEvent : public Event
	{
	public:

		static EventTypes getStaticTypes() { return EventTypes::MouseButtonReleased; }
		virtual inline EventTypes getEventTypes() { return EventTypes::MouseButtonReleased; }
		virtual int32_t getCategoryFlags() const override { return EventCategoryWindow; }
	};

	class MouseMovedEvent : public Event
	{
	public:

		static EventTypes getStaticTypes() { return EventTypes::MouseMoved; }
		virtual inline EventTypes getEventTypes() { return EventTypes::MouseMoved; }
		virtual int32_t getCategoryFlags() const override { return EventCategoryWindow; }
	};

	class MouseScrolledEvent : public Event
	{
	public:

		static EventTypes getStaticTypes() { return EventTypes::MouseScrolled; }
		virtual inline EventTypes getEventTypes() { return EventTypes::MouseScrolled; }
		virtual int32_t getCategoryFlags() const override { return EventCategoryWindow; }
	};
}