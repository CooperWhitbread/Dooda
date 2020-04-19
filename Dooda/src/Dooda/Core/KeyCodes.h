#pragma once

namespace Dooda
{
	typedef enum class KeyCode : uint16_t
	{
		// From glfw3.h
		Space = 32,
		Apostrophe = 39, /* ' */
		Comma = 44, /* , */
		Minus = 45, /* - */
		Period = 46, /* . */
		Slash = 47, /* / */

		D0 = 48, /* 0 */
		D1 = 49, /* 1 */
		D2 = 50, /* 2 */
		D3 = 51, /* 3 */
		D4 = 52, /* 4 */
		D5 = 53, /* 5 */
		D6 = 54, /* 6 */
		D7 = 55, /* 7 */
		D8 = 56, /* 8 */
		D9 = 57, /* 9 */

		Semicolon = 59, /* ; */
		Equal = 61, /* = */

		A = 65,
		B = 66,
		C = 67,
		D = 68,
		E = 69,
		F = 70,
		G = 71,
		H = 72,
		I = 73,
		J = 74,
		K = 75,
		L = 76,
		M = 77,
		N = 78,
		O = 79,
		P = 80,
		Q = 81,
		R = 82,
		S = 83,
		T = 84,
		U = 85,
		V = 86,
		W = 87,
		X = 88,
		Y = 89,
		Z = 90,

		LeftBracket = 91,  /* [ */
		Backslash = 92,  /* \ */
		RightBracket = 93,  /* ] */
		GraveAccent = 96,  /* ` */

		World1 = 161, /* non-US #1 */
		World2 = 162, /* non-US #2 */

		/* Function keys */
		Escape = 256,
		Enter = 257,
		Tab = 258,
		Backspace = 259,
		Insert = 260,
		Delete = 261,
		Right = 262,
		Left = 263,
		Down = 264,
		Up = 265,
		PageUp = 266,
		PageDown = 267,
		Home = 268,
		End = 269,
		CapsLock = 280,
		ScrollLock = 281,
		NumLock = 282,
		PrintScreen = 283,
		Pause = 284,
		F1 = 290,
		F2 = 291,
		F3 = 292,
		F4 = 293,
		F5 = 294,
		F6 = 295,
		F7 = 296,
		F8 = 297,
		F9 = 298,
		F10 = 299,
		F11 = 300,
		F12 = 301,
		F13 = 302,
		F14 = 303,
		F15 = 304,
		F16 = 305,
		F17 = 306,
		F18 = 307,
		F19 = 308,
		F20 = 309,
		F21 = 310,
		F22 = 311,
		F23 = 312,
		F24 = 313,
		F25 = 314,

		/* Keypad */
		KP0 = 320,
		KP1 = 321,
		KP2 = 322,
		KP3 = 323,
		KP4 = 324,
		KP5 = 325,
		KP6 = 326,
		KP7 = 327,
		KP8 = 328,
		KP9 = 329,
		KPDecimal = 330,
		KPDivide = 331,
		KPMultiply = 332,
		KPSubtract = 333,
		KPAdd = 334,
		KPEnter = 335,
		KPEqual = 336,

		LeftShift = 340,
		LeftControl = 341,
		LeftAlt = 342,
		LeftSuper = 343,
		RightShift = 344,
		RightControl = 345,
		RightAlt = 346,
		RightSuper = 347,
		Menu = 348
	} Key;

	inline std::ostream& operator<<(std::ostream& os, KeyCode keyCode)
	{
		os << static_cast<int32_t>(keyCode);
		return os;
	}

}

#define DD_KEY_SPACE			::Dooda::Key::Space
#define DD_KEY_APOSTROPHE		::Dooda::Key::Apostrophe	/* ' */
#define DD_KEY_COMMA			::Dooda::Key::Comma			/* , */
#define DD_KEY_MINUS			::Dooda::Key::Minus			/* - */
#define DD_KEY_PERIOD			::Dooda::Key::Period		/* . */
#define DD_KEY_SLASH			::Dooda::Key::Slash			/* / */
#define DD_KEY_0				::Dooda::Key::D0
#define DD_KEY_1				::Dooda::Key::D1
#define DD_KEY_2				::Dooda::Key::D2
#define DD_KEY_3				::Dooda::Key::D3
#define DD_KEY_4				::Dooda::Key::D4
#define DD_KEY_5				::Dooda::Key::D5
#define DD_KEY_6				::Dooda::Key::D6
#define DD_KEY_7				::Dooda::Key::D7
#define DD_KEY_8				::Dooda::Key::D8
#define DD_KEY_9				::Dooda::Key::D9
#define DD_KEY_SEMICOLON		::Dooda::Key::Semicolon		/* ; */
#define DD_KEY_EQUAL			::Dooda::Key::Equal			/* = */
#define DD_KEY_A				::Dooda::Key::A
#define DD_KEY_B				::Dooda::Key::B
#define DD_KEY_C				::Dooda::Key::C
#define DD_KEY_D				::Dooda::Key::D
#define DD_KEY_E				::Dooda::Key::E
#define DD_KEY_F				::Dooda::Key::F
#define DD_KEY_G				::Dooda::Key::G
#define DD_KEY_H				::Dooda::Key::H
#define DD_KEY_I				::Dooda::Key::I
#define DD_KEY_J				::Dooda::Key::J
#define DD_KEY_K				::Dooda::Key::K
#define DD_KEY_L				::Dooda::Key::L
#define DD_KEY_M				::Dooda::Key::M
#define DD_KEY_N				::Dooda::Key::N
#define DD_KEY_O				::Dooda::Key::O
#define DD_KEY_P				::Dooda::Key::P
#define DD_KEY_Q				::Dooda::Key::Q
#define DD_KEY_R				::Dooda::Key::R
#define DD_KEY_S				::Dooda::Key::S
#define DD_KEY_T				::Dooda::Key::T
#define DD_KEY_U				::Dooda::Key::U
#define DD_KEY_V				::Dooda::Key::V
#define DD_KEY_W				::Dooda::Key::W
#define DD_KEY_X				::Dooda::Key::X
#define DD_KEY_Y				::Dooda::Key::Y
#define DD_KEY_Z				::Dooda::Key::Z
#define DD_KEY_LEFT_BRACKET		::Dooda::Key::LeftBracket   /* [ */
#define DD_KEY_BACKSLASH		::Dooda::Key::Backslash		/* \ */
#define DD_KEY_RIGHT_BRACKET	::Dooda::Key::RightBracket	/* ] */
#define DD_KEY_GRAVE_ACCENT		::Dooda::Key::GraveAccent	/* ` */
#define DD_KEY_WORLD_1			::Dooda::Key::World1		/* non-US #1 */
#define DD_KEY_WORLD_2			::Dooda::Key::World2		/* non-US #2 */

/* Function keys */
#define DD_KEY_ESCAPE			::Dooda::Key::Escape
#define DD_KEY_ENTER			::Dooda::Key::Enter
#define DD_KEY_TAB				::Dooda::Key::Tab
#define DD_KEY_BACKSPACE		::Dooda::Key::Backspace
#define DD_KEY_INSERT			::Dooda::Key::Insert
#define DD_KEY_DELETE			::Dooda::Key::Delete
#define DD_KEY_RIGHT			::Dooda::Key::Right
#define DD_KEY_LEFT				::Dooda::Key::Left
#define DD_KEY_DOWN				::Dooda::Key::Down
#define DD_KEY_UP				::Dooda::Key::Up
#define DD_KEY_PAGE_UP			::Dooda::Key::PageUp
#define DD_KEY_PAGE_DOWN		::Dooda::Key::PageDown
#define DD_KEY_HOME				::Dooda::Key::Home
#define DD_KEY_END				::Dooda::Key::End
#define DD_KEY_CAPS_LOCK		::Dooda::Key::CapsLock
#define DD_KEY_SCROLL_LOCK		::Dooda::Key::ScrollLock
#define DD_KEY_NUM_LOCK			::Dooda::Key::NumLock
#define DD_KEY_PRINT_SCREEN		::Dooda::Key::PrintScreen
#define DD_KEY_PAUSE			::Dooda::Key::Pause
#define DD_KEY_F1				::Dooda::Key::F1
#define DD_KEY_F2				::Dooda::Key::F2
#define DD_KEY_F3				::Dooda::Key::F3
#define DD_KEY_F4				::Dooda::Key::F4
#define DD_KEY_F5				::Dooda::Key::F5
#define DD_KEY_F6				::Dooda::Key::F6
#define DD_KEY_F7				::Dooda::Key::F7
#define DD_KEY_F8				::Dooda::Key::F8
#define DD_KEY_F9				::Dooda::Key::F9
#define DD_KEY_F10				::Dooda::Key::F10
#define DD_KEY_F11				::Dooda::Key::F11
#define DD_KEY_F12				::Dooda::Key::F12
#define DD_KEY_F13				::Dooda::Key::F13
#define DD_KEY_F14				::Dooda::Key::F14
#define DD_KEY_F15				::Dooda::Key::F15
#define DD_KEY_F16				::Dooda::Key::F16
#define DD_KEY_F17				::Dooda::Key::F17
#define DD_KEY_F18				::Dooda::Key::F18
#define DD_KEY_F19				::Dooda::Key::F19
#define DD_KEY_F20				::Dooda::Key::F20
#define DD_KEY_F21				::Dooda::Key::F21
#define DD_KEY_F22				::Dooda::Key::F22
#define DD_KEY_F23				::Dooda::Key::F23
#define DD_KEY_F24				::Dooda::Key::F24
#define DD_KEY_F25				::Dooda::Key::F25

/* Keypad */
#define DD_KEY_KP_0				::Dooda::Key::KP0
#define DD_KEY_KP_1				::Dooda::Key::KP1
#define DD_KEY_KP_2				::Dooda::Key::KP2
#define DD_KEY_KP_3				::Dooda::Key::KP3
#define DD_KEY_KP_4				::Dooda::Key::KP4
#define DD_KEY_KP_5				::Dooda::Key::KP5
#define DD_KEY_KP_6				::Dooda::Key::KP6
#define DD_KEY_KP_7				::Dooda::Key::KP7
#define DD_KEY_KP_8				::Dooda::Key::KP8
#define DD_KEY_KP_9				::Dooda::Key::KP9
#define DD_KEY_KP_DECIMAL		::Dooda::Key::KPDecimal
#define DD_KEY_KP_DIVIDE		::Dooda::Key::KPDivide
#define DD_KEY_KP_MULTIPLY		::Dooda::Key::KPMultiply
#define DD_KEY_KP_SUBTRACT		::Dooda::Key::KPSubtract
#define DD_KEY_KP_ADD			::Dooda::Key::KPAdd
#define DD_KEY_KP_ENTER			::Dooda::Key::KPEnter
#define DD_KEY_KP_EQUAL			::Dooda::Key::KPEqual

#define DD_KEY_LEFT_SHIFT		::Dooda::Key::LeftShift
#define DD_KEY_LEFT_CONTROL		::Dooda::Key::LeftControl
#define DD_KEY_LEFT_ALT			::Dooda::Key::LeftAlt
#define DD_KEY_LEFT_SUPER		::Dooda::Key::LeftSuper
#define DD_KEY_RIGHT_SHIFT		::Dooda::Key::RightShift
#define DD_KEY_RIGHT_CONTROL	::Dooda::Key::RightControl
#define DD_KEY_RIGHT_ALT		::Dooda::Key::RightAlt
#define DD_KEY_RIGHT_SUPER		::Dooda::Key::RightSuper
#define DD_KEY_MENU				::Dooda::Key::Menu