#include "State.h"

#include <cassert>

namespace state
{

State::State(Stranded & game) :
	game(game),
	hidden(true)
{}

State::~State()
{
	assert(hidden);
}

void State::show()
{
	hidden = false;
}

void State::hide()
{
	hidden = true;
}

bool State::processEvent(Event /* event */)
{
	return false;
}

void State::update(double /* deltaTime */)
{}

} // namespace state
