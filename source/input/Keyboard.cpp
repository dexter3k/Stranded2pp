#include "Keyboard.h"

namespace kb
{
	// This function (hopefully) takes O(1) time
	uint8_t sfmlToBlitz(sf::Keyboard::Key key)
	{
		switch (key) {
		case sf::Keyboard::Unknown:		return kb::Unknown;
		case sf::Keyboard::A:			return kb::A;
		case sf::Keyboard::B:			return kb::B;
		case sf::Keyboard::C:			return kb::C;
		case sf::Keyboard::D:			return kb::D;
		case sf::Keyboard::E:			return kb::E;
		case sf::Keyboard::F:			return kb::F;
		case sf::Keyboard::G:			return kb::G;
		case sf::Keyboard::H:			return kb::H;
		case sf::Keyboard::I:			return kb::I;
		case sf::Keyboard::J:			return kb::J;
		case sf::Keyboard::K:			return kb::K;
		case sf::Keyboard::L:			return kb::L;
		case sf::Keyboard::M:			return kb::M;
		case sf::Keyboard::N:			return kb::N;
		case sf::Keyboard::O:			return kb::O;
		case sf::Keyboard::P:			return kb::P;
		case sf::Keyboard::Q:			return kb::Q;
		case sf::Keyboard::R:			return kb::R;
		case sf::Keyboard::S:			return kb::S;
		case sf::Keyboard::T:			return kb::T;
		case sf::Keyboard::U:			return kb::U;
		case sf::Keyboard::V:			return kb::V;
		case sf::Keyboard::W:			return kb::W;
		case sf::Keyboard::X:			return kb::X;
		case sf::Keyboard::Y:			return kb::Y;
		case sf::Keyboard::Z:			return kb::Z;
		case sf::Keyboard::Num0:		return kb::Num0;
		case sf::Keyboard::Num1:		return kb::Num1;
		case sf::Keyboard::Num2:		return kb::Num2;
		case sf::Keyboard::Num3:		return kb::Num3;
		case sf::Keyboard::Num4:		return kb::Num4;
		case sf::Keyboard::Num5:		return kb::Num5;
		case sf::Keyboard::Num6:		return kb::Num6;
		case sf::Keyboard::Num7:		return kb::Num7;
		case sf::Keyboard::Num8:		return kb::Num8;
		case sf::Keyboard::Num9:		return kb::Num9;
		case sf::Keyboard::Escape:		return kb::Escape;
		case sf::Keyboard::LControl:	return kb::LeftControl;
		case sf::Keyboard::LShift:		return kb::LeftShift;
		case sf::Keyboard::LAlt:		return kb::LeftAlt;
		case sf::Keyboard::LSystem:		return kb::LeftSuper;
		case sf::Keyboard::RControl:	return kb::RightControl;
		case sf::Keyboard::RShift:		return kb::RightShift;
		case sf::Keyboard::RAlt:		return kb::AltGr;
		case sf::Keyboard::RSystem:		return kb::RightSuper;
		case sf::Keyboard::Menu:		return kb::Menu;
		case sf::Keyboard::LBracket:	return kb::LeftBracket;
		case sf::Keyboard::RBracket:	return kb::RightBracket;
		case sf::Keyboard::SemiColon:	return kb::Semicolon;
		case sf::Keyboard::Comma:		return kb::Comma;
		case sf::Keyboard::Period:		return kb::Period;
		case sf::Keyboard::Quote:		return kb::Quote;
		case sf::Keyboard::Slash:		return kb::Slash;
		case sf::Keyboard::BackSlash:	return kb::BackSlash;
		case sf::Keyboard::Tilde:		return kb::Grave;
		case sf::Keyboard::Equal:		return kb::Equal;
		case sf::Keyboard::Dash:		return kb::Dash;
		case sf::Keyboard::Space:		return kb::Space;
		case sf::Keyboard::Return:		return kb::Enter;
		case sf::Keyboard::BackSpace:	return kb::Backspace;
		case sf::Keyboard::Tab:			return kb::Tab;
		case sf::Keyboard::PageUp:		return kb::PageUp;
		case sf::Keyboard::PageDown:	return kb::PageDown;
		case sf::Keyboard::End:			return kb::End;
		case sf::Keyboard::Home:		return kb::Home;
		case sf::Keyboard::Insert:		return kb::Insert;
		case sf::Keyboard::Delete:		return kb::Delete;
		case sf::Keyboard::Add:			return kb::NumpadPlus;
		case sf::Keyboard::Subtract:	return kb::NumpadMinus;
		case sf::Keyboard::Multiply:	return kb::NumpadMultiply;
		case sf::Keyboard::Divide:		return kb::NumpadDivide;
		case sf::Keyboard::Left:		return kb::Left;
		case sf::Keyboard::Right:		return kb::Right;
		case sf::Keyboard::Up:			return kb::Up;
		case sf::Keyboard::Down:		return kb::Down;
		case sf::Keyboard::Numpad0:		return kb::Numpad0;
		case sf::Keyboard::Numpad1:		return kb::Numpad1;
		case sf::Keyboard::Numpad2:		return kb::Numpad2;
		case sf::Keyboard::Numpad3:		return kb::Numpad3;
		case sf::Keyboard::Numpad4:		return kb::Numpad4;
		case sf::Keyboard::Numpad5:		return kb::Numpad5;
		case sf::Keyboard::Numpad6:		return kb::Numpad6;
		case sf::Keyboard::Numpad7:		return kb::Numpad7;
		case sf::Keyboard::Numpad8:		return kb::Numpad8;
		case sf::Keyboard::Numpad9:		return kb::Numpad9;
		case sf::Keyboard::F1:			return kb::F1;
		case sf::Keyboard::F2:			return kb::F2;
		case sf::Keyboard::F3:			return kb::F3;
		case sf::Keyboard::F4:			return kb::F4;
		case sf::Keyboard::F5:			return kb::F5;
		case sf::Keyboard::F6:			return kb::F6;
		case sf::Keyboard::F7:			return kb::F7;
		case sf::Keyboard::F8:			return kb::F8;
		case sf::Keyboard::F9:			return kb::F9;
		case sf::Keyboard::F10:			return kb::F10;
		case sf::Keyboard::F11:			return kb::F11;
		case sf::Keyboard::F12:			return kb::F12;
		case sf::Keyboard::F13:			return kb::F13;
		case sf::Keyboard::F14:			return kb::F14;
		case sf::Keyboard::F15:			return kb::F15;
		case sf::Keyboard::Pause:		return kb::Pause;
		default:						return kb::Unknown;
		}

		return kb::Unknown;
	}
} // namespace kb
