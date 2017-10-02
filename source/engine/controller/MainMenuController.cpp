#include "MainMenuController.h"

namespace controller
{

MainMenuController::MainMenuController(Engine & engine) :
	super(engine)
{}

bool MainMenuController::processEvent(Event)
{
	return false;
}

} // namespace controller
