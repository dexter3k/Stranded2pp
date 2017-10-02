#include "Controller.h"

namespace controller
{

Controller::Controller(Engine & engine) :
	engine(engine)
{}

bool Controller::processEvent(Event)
{
	return false;
}

} // namespace controller
