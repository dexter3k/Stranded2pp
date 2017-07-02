#pragma once

#include <SFML/System/Clock.hpp>

class Timer
{
public:
	Timer();

	double getElapsedTime() const;

	void start();
	double restart();
	double stop();

	double pause();
	double unpause();
private:
	sf::Clock timer;

	double pauseStart;
	double overallPauseTime;

	bool isStarted;
	bool isPaused;
};
