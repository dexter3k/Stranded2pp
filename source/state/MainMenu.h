#pragma once

#include "State.h"

#include "graphics/gui/GuiElement.h"

namespace state
{

class MainMenu : public State
{
	typedef State super;
public:
	MainMenu(Stranded & game);

	void show() override;
	void hide() override;
private:
	void loadGame();
	void loadInterface();

	static std::string const menuMap;

	gfx::gui::GuiElement * menuRoot;
	gfx::gui::GuiElement * mainMenu;
	gfx::gui::GuiElement * randomMenu;
	gfx::gui::GuiElement * customMenu;
	gfx::gui::GuiElement * loadGameMenu;
	gfx::gui::GuiElement * multiplayerMenu;
	gfx::gui::GuiElement * optionsMenu;
	gfx::gui::GuiElement * creditsMenu;
	gfx::gui::GuiElement * quitMenu;
};

} // namespace state
