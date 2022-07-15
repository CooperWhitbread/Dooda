#pragma once

#include "Dooda/Events/Event.h"
#include "Dooda/Core/KeyCodes.h"

namespace Dooda {

	class KeyEvent : public Event
	{
	protected:
		KeyEvent(const KeyCode keycode)
			: d_KeyCode(keycode) 
		{
		}

		EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput | EventCategoryMouseButton)

	public: //Getters
		inline KeyCode GetKeyCode() const { return d_KeyCode; }


	protected: //Variables
		KeyCode d_KeyCode;
	};

	class KeyPressedEvent : public KeyEvent
	{
	public:
		KeyPressedEvent(const KeyCode keycode, bool isRepeat = false)
			: KeyEvent(keycode), d_IsRepeat(isRepeat)
		{
		}

		EVENT_CLASS_TYPE(KeyPressed)

	public: //Getters
		inline bool IsRepeat() const { return d_IsRepeat; }

		std::string GetToString() const override
		{
			std::stringstream ss;
			ss << "KeyPressedEvent: " << d_KeyCode << " (repeat = " << d_IsRepeat << ")";
			return ss.str();
		}

	private: //Variables
		bool d_IsRepeat;
	};

	class KeyReleasedEvent : public KeyEvent
	{
	public:
		KeyReleasedEvent(const KeyCode keycode)
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
		KeyTypedEvent(const KeyCode keycode)
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
