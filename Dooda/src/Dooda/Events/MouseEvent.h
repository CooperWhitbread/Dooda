#pragma once

#include "Dooda/Events/Event.h"
#include "Dooda/Core/MouseCodes.h"

namespace Dooda {

	class MouseMovedEvent : public Event
	{
	public:
		MouseMovedEvent(const float x, const float y)
			: d_MouseX(x), d_MouseY(y) 
		{
		}

		EVENT_CLASS_TYPE(MouseMoved)
		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)

	public: //Getters
		inline float GetX() const { return d_MouseX; }
		inline float GetY() const { return d_MouseY; }

		std::string GetToString() const override
		{
			std::stringstream ss;
			ss << "MouseMovedEvent: " << d_MouseX << ", " << d_MouseY;
			return ss.str();
		}

	private: //Variables
		float d_MouseX, d_MouseY;

	};

	class MouseScrolledEvent : public Event
	{
	public:
		MouseScrolledEvent(const float xOffset, const float yOffset)
			: d_XOffset(xOffset), d_YOffset(yOffset) 
		{
		}
		
		EVENT_CLASS_TYPE(MouseScrolled)
		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)

	public: //Getters
		inline float GetXOffset() const { return d_XOffset; }
		inline float GetYOffset() const { return d_YOffset; }

		std::string GetToString() const override
		{
			std::stringstream ss;
			ss << "MouseScrolledEvent: " << GetXOffset() << ", " << GetYOffset();
			return ss.str();
		}
		
	private: //Variables
		float d_XOffset, d_YOffset;
	};

	class MouseButtonEvent : public Event
	{
	protected:
		MouseButtonEvent(const MouseCode button)
			: d_Button(button)
		{
		}

		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)

	public: //Getters
		MouseCode GetMouseButton() const { return d_Button; }

	protected://Variables
		MouseCode d_Button;
	};

	class MouseButtonPressedEvent : public MouseButtonEvent
	{
	public:
		MouseButtonPressedEvent(const MouseCode button)
			: MouseButtonEvent(button) 
		{
		}

		EVENT_CLASS_TYPE(MouseButtonPressed)

	public: //Getters
		std::string GetToString() const override
		{
			std::stringstream ss;
			ss << "MouseButtonPressedEvent: " << d_Button;
			return ss.str();
		}
	};

	class MouseButtonReleasedEvent : public MouseButtonEvent
	{
	public:
		MouseButtonReleasedEvent(const MouseCode button)
			: MouseButtonEvent(button) 
		{
		}

		EVENT_CLASS_TYPE(MouseButtonReleased)

	public: //Getters
		std::string GetToString() const override
		{
			std::stringstream ss;
			ss << "MouseButtonReleasedEvent: " << d_Button;
			return ss.str();
		}
	};

}