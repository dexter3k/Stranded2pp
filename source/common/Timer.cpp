#include "Timer.h"

Timer::Timer() :
	timer(),
	pauseStart(0.0f),
	overallPauseTime(0.0f),
	isStarted(false),
	isPaused(false)
{}

Timer::~Timer()
{}

float Timer::getElapsedTime() const
{
	if (!isStarted)
	{
		return 0.0f;
	}

	if (isPaused)
	{
		return pauseStart;
	}

	return timer.getElapsedTime().asSeconds() - overallPauseTime;
}

void Timer::start()
{
	isStarted = true;

	timer.restart();
}

float Timer::restart()
{
	float runTime = stop();

	start();

	return runTime;
}

float Timer::stop()
{
	float runTime = timer.getElapsedTime().asSeconds() - overallPauseTime;

	isStarted = false;
	pauseStart = 0.0f;
	overallPauseTime = 0.0f;

	return runTime;
}

float Timer::pause()
{
	pauseStart = getElapsedTime();

	isPaused = true;

	return pauseStart;
}

float Timer::unpause()
{
	isPaused = false;

	float pauseTime = getElapsedTime() - pauseStart;
	overallPauseTime += pauseTime;

	return pauseTime;
}
