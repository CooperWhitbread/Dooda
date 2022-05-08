#pragma once

#include <functional>

#include "Dooda/Debug/Instrumentor.h"

namespace Dooda
{
	// Events in Dooda are currently blocking, meaning when an event occurs it
	// immediately gets dispatched and must be dealt with right then an there.
	// For the future, a better strategy might be to buffer events in an event
	// bus and process them during the "event" part of the update stage.

	enum class EventType
	{
		None = 0, //Default
		WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved, //Window events
		AppTick, AppUpdate, AppRender, //Application events
		KeyPressed, KeyReleased, KeyTyped, //Key events
		MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled //Mouse events
	};

	enum EventCategory
	{
		None = 0,
		EventCategoryApplication =	BIT(0),
		EventCategoryInput =		BIT(1),
		EventCategoryKeyboard =		BIT(2),
		EventCategoryMouse =		BIT(3),
		EventCategoryMouseButton =	BIT(4)
	};

#define EVENT_CLASS_TYPE(type) static EventType GetStaticType() { return EventType::type; }\
								virtual EventType GetEventType() const override { return GetStaticType(); }\
								virtual const char* GetName() const override { return #type; }

#define EVENT_CLASS_CATEGORY(category) virtual int GetCategoryFlags() const override { return category; }

	class Event
	{
	public: //Getters
		virtual EventType GetEventType() const = 0;
		virtual const char* GetName() const = 0;
		virtual int GetCategoryFlags() const = 0;
		virtual std::string GetToString() const { return GetName(); }

		virtual ~Event() = default;

		inline bool GetIsInCategory(EventCategory category) { return GetCategoryFlags() & category; }

	public: //Variables
		bool Handled = false;
	};

	class EventDispatcher
	{
	public:
		EventDispatcher(Event& event)
			: d_Event(event)
		{
		}

		~EventDispatcher() = default;

		template<typename T, typename F>
		bool Dispatch(const F& func)
		{
			if (d_Event.GetEventType() == T::GetStaticType())
			{
				d_Event.Handled |= func(static_cast<T&>(d_Event));
				return true;
			}
			return false;
		}

	private: //Variables
		Event& d_Event;
	};

	inline std::ostream& operator<<(std::ostream& os, const Event& e)
	{
		return os << e.GetToString();
	}

}