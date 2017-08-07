#pragma once

#include <cstdint>

#include <SFML/Window/Mouse.hpp>

namespace mouse
{
	enum Button
	{
		Unknown = 0,
		Left,
		Right,
		Middle,
		Button4,
		Button5
	};

	enum Wheel
	{
		WheelUp = 0,
		WheelDown
	};

	uint8_t sfmlToBlitz(sf::Mouse::Button button);
} // namespace mouse
