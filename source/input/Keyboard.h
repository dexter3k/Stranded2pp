#pragma once

#include <cstdint>

#include <SFML/Window/Keyboard.hpp>

namespace kb
{
	// Blitz3D keyboard layout
	enum Key
	{
		Unknown = 0,
		Escape,
		Num1,
		Num2,
		Num3,
		Num4,
		Num5,
		Num6,
		Num7,
		Num8,
		Num9,
		Num0,
		Dash,
		Equal,
		Backspace,
		Tab,
		Q,
		W,
		E,
		R,
		T,
		Y,
		U,
		I,
		O,
		P,
		LeftBracket,
		RightBracket,
		Enter,
		LeftControl,
		A,
		S,
		D,
		F,
		G,
		H,
		J,
		K,
		L,
		Semicolon,
		Quote,
		Grave,
		LeftShift,
		BackSlash,
		Z,
		X,
		C,
		V,
		B,
		N,
		M,
		Comma,
		Period,
		Slash,
		RightShift,
		NumpadMultiply,
		LeftAlt,
		Space,
		CapsLock,
		F1,
		F2,
		F3,
		F4,
		F5,
		F6,
		F7,
		F8,
		F9,
		F10,
		Pause,
		ScrollLock,
		Numpad7,
		Numpad8,
		Numpad9,
		NumpadMinus,
		Numpad4,
		Numpad5,
		Numpad6,
		NumpadPlus,
		Numpad1,
		Numpad2,
		Numpad3,
		Numpad0,
		NumpadDecimal,
		/* ... */
		F11 = 87,
		F12,
		/* ... */
		F13 = 100,
		F14,
		F15,
		/* ... */
		NumpadEnter = 156,
		RightControl,
		/* ... */
		NumpadDivide = 181,
		/* ... */
		AltGr = 184,
		/* ... */
		Home = 199,
		Up,
		PageUp,
		/* ... */
		Left = 203,
		/* ... */
		Right = 205,
		/* ... */
		End = 207,
		Down,
		PageDown,
		Insert,
		Delete,
		/* ... */
		LeftSuper = 219,
		RightSuper,
		Menu
	};

	uint8_t sfmlToBlitz(const sf::Keyboard::Key& key);
} // namespace kb
