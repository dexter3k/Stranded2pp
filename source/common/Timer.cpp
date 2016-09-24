#include "Timer.h"

Timer::Timer() :
	timer()
{}

Timer::~Timer()
{}

float Timer::getElapsedTime() const
{
	return timer.getElapsedTime().asSeconds();
}

float Timer::restart()
{
	return timer.restart().asSeconds();
}
