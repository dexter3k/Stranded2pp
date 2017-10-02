#pragma once

#include "Controller.h"

namespace controller
{

class MainMenuController : public Controller
{
	typedef Controller super;
public:
	MainMenuController(Engine & engine);

	bool processEvent(Event event) override;
};

} // namespace controller
