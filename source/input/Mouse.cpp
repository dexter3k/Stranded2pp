#include "Mouse.h"

namespace mouse
{
	uint8_t sfmlToBlitz(const sf::Mouse::Button& button)
	{
		switch (button)
		{
			case sf::Mouse::Left:		return mouse::Left;
			case sf::Mouse::Right:		return mouse::Right;
			case sf::Mouse::Middle:		return mouse::Middle;
			case sf::Mouse::XButton1:	return mouse::Button4;
			case sf::Mouse::XButton2:	return mouse::Button5;
			default:					return mouse::Unknown;
		}
	}
} // namespace mouse
