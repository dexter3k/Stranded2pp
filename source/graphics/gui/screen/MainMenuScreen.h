#pragma once

#include "Screen.h"

class Input;

namespace gfx
{

namespace gui
{

class GuiButton;

class MainMenuScreen : public Screen
{
	typedef Screen super;
public:
	MainMenuScreen(Gui& gui, Input& input);
	~MainMenuScreen();

	void create() override;
	void destroy() override;

	void update(double deltaTime) override;
private:
	// Currently only used for debugging
	GuiButton* testButton;
};

} // namespace gui

} // namespace gfx
