#pragma once

#include "input/Event.h"

class Stranded;

namespace state
{

enum Type
{
	IntroState,
	MainMenuState,
	SingleplayerState,
	MultiplayerState,
	EditorState
};

class State
{
public:
	State(Stranded & game);
	virtual ~State();

	virtual void show();
	virtual void hide();

	virtual bool processEvent(Event event);
	virtual void update(double deltaTime);
protected:
	Stranded & game;

	bool hidden;
};

} // namespace state
