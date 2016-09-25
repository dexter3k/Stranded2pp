#pragma once

#include <iostream>

#include <SFML/System.hpp>
#include <SFML/System/Clock.hpp>


// TODO: ASCII art that clearly explains how this class works


class Timer
{
public:
	Timer();
	~Timer();

	float getElapsedTime() const;

	void start();
	float restart();
	float stop();

	float pause();
	float unpause();
private:
	sf::Clock timer;

	float pauseStart;
	float overallPauseTime;

	bool isStarted;
	bool isPaused;
};
