#pragma once

#include "input/Event.h"

class Engine;

namespace controller
{

enum Type
{
	MainMenu
};

class Controller
{
public:
	Controller(Engine & engine);
	virtual ~Controller() = default;

	virtual bool processEvent(Event event) = 0;
protected:
	Engine & engine;
};

} // namespace controller
