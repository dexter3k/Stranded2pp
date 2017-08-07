#pragma once

#include "State.h"

#include "graphics/gui/GuiElement.h"

namespace state
{

class Intro : public State
{
	typedef State super;
public:
	Intro(Stranded & game);

	void show() override;
	void hide() override;
private:
	void loadInterface();

	gfx::gui::GuiElement * rootElement;
};

} // namespace state
