#include "Screen.h"

#include <cassert>

#include "../Gui.h"

namespace gfx
{

namespace gui
{

Screen::Screen(Gui& gui) :
	gui(gui),
	isCreated(false)
{}

Screen::~Screen()
{
	assert(!isCreated);
}

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

void Screen::update(double)
{}

} // namespace gui

} // namespace gfx
