#pragma once

namespace Dooda
{
	typedef enum class MouseCode : uint16_t
	{
		// From glfw3.h
		Button0 = 0,
		Button1 = 1,
		Button2 = 2,
		Button3 = 3,
		Button4 = 4,
		Button5 = 5,
		Button6 = 6,
		Button7 = 7,

		ButtonLast = Button7,
		ButtonLeft = Button0,
		ButtonRight = Button1,
		ButtonMiddle = Button2
	} Mouse;

	inline std::ostream& operator<<(std::ostream& os, MouseCode mouseCode)
	{
		os << static_cast<int32_t>(mouseCode);
		return os;
	}
}

#define DD_MOUSE_BUTTON_0		::Dooda::Mouse::Button0
#define DD_MOUSE_BUTTON_1		::Dooda::Mouse::Button1
#define DD_MOUSE_BUTTON_2		::Dooda::Mouse::Button2
#define DD_MOUSE_BUTTON_3		::Dooda::Mouse::Button3
#define DD_MOUSE_BUTTON_4		::Dooda::Mouse::Button4
#define DD_MOUSE_BUTTON_5		::Dooda::Mouse::Button5
#define DD_MOUSE_BUTTON_6		::Dooda::Mouse::Button6
#define DD_MOUSE_BUTTON_7		::Dooda::Mouse::Button7
#define DD_MOUSE_BUTTON_LAST	::Dooda::Mouse::ButtonLast
#define DD_MOUSE_BUTTON_LEFT	::Dooda::Mouse::ButtonLeft
#define DD_MOUSE_BUTTON_RIGHT	::Dooda::Mouse::ButtonRight
#define DD_MOUSE_BUTTON_MIDDLE	::Dooda::Mouse::ButtonMiddle