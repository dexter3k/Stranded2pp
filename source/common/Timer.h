#pragma once

#include <SFML/System/Clock.hpp>

class Timer
{
public:
	Timer();
	~Timer();

	float getElapsedTime() const;
	float restart();
private:
	sf::Clock timer;
};
