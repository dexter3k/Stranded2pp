#include "Timer.h"

Timer::Timer() :
	timer(),
	pauseStart(0.0f),
	overallPauseTime(0.0f),
	isStarted(false),
	isPaused(false)
{}

double Timer::getElapsedTime() const
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

double Timer::restart()
{
	double runTime = stop();

	start();

	return runTime;
}

double Timer::stop()
{
	double runTime = timer.getElapsedTime().asSeconds() - overallPauseTime;

	isStarted = false;
	pauseStart = 0.0f;
	overallPauseTime = 0.0f;

	return runTime;
}

double Timer::pause()
{
	pauseStart = getElapsedTime();

	isPaused = true;

	return pauseStart;
}

double Timer::unpause()
{
	isPaused = false;

	double pauseTime = getElapsedTime() - pauseStart;
	overallPauseTime += pauseTime;

	return pauseTime;
}
