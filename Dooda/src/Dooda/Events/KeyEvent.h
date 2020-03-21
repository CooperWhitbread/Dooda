#pragma once

#include "Dooda/Events/Event.h"

namespace Dooda {

	class KeyEvent : public Event
	{
	protected:
		KeyEvent(int keycode)
			: d_KeyCode(keycode) 
		{
		}

		EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput)

	public: //Getters
		inline int GetKeyCode() const { return d_KeyCode; }


	protected: //Variables
		int d_KeyCode;
	};

	class KeyPressedEvent : public KeyEvent
	{
	public:
		KeyPressedEvent(int keycode, int repeatCount)
			: KeyEvent(keycode), d_RepeatCount(repeatCount) 
		{
		}

		EVENT_CLASS_TYPE(KeyPressed)

	public: //Getters
		inline int GetRepeatCount() const { return d_RepeatCount; }

		std::string GetToString() const override
		{
			std::stringstream ss;
			ss << "KeyPressedEvent: " << d_KeyCode << " (" << d_RepeatCount << " repeats)";
			return ss.str();
		}

	private: //Variables
		int d_RepeatCount;
	};

	class KeyReleasedEvent : public KeyEvent
	{
	public:
		KeyReleasedEvent(int keycode)
			: KeyEvent(keycode) 
		{
		}

		EVENT_CLASS_TYPE(KeyReleased)

	public: //Getters
		std::string GetToString() const override
		{
			std::stringstream ss;
			ss << "KeyReleasedEvent: " << d_KeyCode;
			return ss.str();
		}

	};

	class KeyTypedEvent : public KeyEvent
	{
	public:
		KeyTypedEvent(int keycode)
			: KeyEvent(keycode) 
		{
		}

		EVENT_CLASS_TYPE(KeyTyped)
		
	public: //Getters
		std::string GetToString() const override
		{
			std::stringstream ss;
			ss << "KeyTypedEvent: " << d_KeyCode;
			return ss.str();
		}

	};
}