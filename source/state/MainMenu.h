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

	bool processEvent(Event event);
private:
	void loadGame();
	void loadInterface();
private:
	static std::string const menuMap;
	static std::string const logoImage;
private:
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
