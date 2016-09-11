#include "Screen.h"

#include <cassert>

#include "../Gui.h"

Screen::Screen(Gui& gui) :
	gui(gui),
	isCreated(false)
{}

Screen::~Screen()
{}

void Screen::create()
{
	assert(!isCreated);

	isCreated = true;
}

void Screen::destroy()
{
	assert(isCreated);

	isCreated = false;
}

void Screen::update(float deltaTime)
{

}
