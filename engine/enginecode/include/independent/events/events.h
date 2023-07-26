/* \file events.h */
#pragma once
#include <inttypes.h>

namespace Engine
{
/** \enum Even Type
* An enum for even types
*/
	enum class EventTypes
	{
		None = 0,
		WindowClose, WindowResize, WindowFocus, WindowLostFocus, Windowmoved,
		KeyPressed, KeyReleased, KeyTyped,
		MoseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
	};

	/** \enum for EventCategory
	* Enum type category flags
	*/

	enum EventCategory
	{
		None = 0,
		EventCategoryWindow = 1 << 0,          //00000001
		EventCategoryInput = 1 << 1,           //00000010
		EventCategoryKeyboard = 1 << 2,        //00000100
		EventCategoryMouse = 1 << 3,           //00001000
		EventCategoryMouseButton = 1 << 4,     //00010000
	};
	/**\ Event class
	* Base class for event
	*/
	class Event
	{
	public:
		virtual EventTypes getEventTypes() const = 0; //!< Get the event type
		virtual int32_t getCategoryFlags() const = 0; //!< Get events category flags
		inline bool handled() const { return m_handled; }//!< Is the event handled
		inline void handle(bool isHandled) {m_handled = isHandled;}
		inline bool isInCategory(EventCategory category) const { return getCategoryFlags() & category; } //!< is the event in the category
	protected:
		bool m_handled = false; //!< Has the event been handled 

	};
}