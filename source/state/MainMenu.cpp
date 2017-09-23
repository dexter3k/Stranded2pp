#include "MainMenu.h"

#include <iostream>

#include "Stranded.h"
#include "graphics/gui/Gui.h"

namespace state
{

std::string const MainMenu::menuMap = "maps/menu/menu.s2";

MainMenu::MainMenu(Stranded & game) :
	super(game),
	menuRoot(nullptr),
	mainMenu(nullptr),
	randomMenu(nullptr),
	customMenu(nullptr),
	loadGameMenu(nullptr),
	multiplayerMenu(nullptr),
	optionsMenu(nullptr),
	creditsMenu(nullptr),
	quitMenu(nullptr)
{
	loadInterface();
}

void MainMenu::show()
{
	super::show();

	loadGame();
	mainMenu->show();
}

void MainMenu::hide()
{
	mainMenu->hide();

	super::hide();
}

void MainMenu::loadGame()
{
	auto & engine = game.getEngine();

	engine.loadGame(menuMap/*, MainMenuController*/);
}

void MainMenu::loadInterface()
{
	assert(menuRoot == nullptr);

	auto & gfx = game.getGraphics();
	auto & gui = gfx.getGui();

	menuRoot = gui.createEmptyElement();

	mainMenu = gui.createEmptyElement(menuRoot);
	randomMenu = gui.createEmptyElement(menuRoot);
	customMenu = gui.createEmptyElement(menuRoot);
	loadGameMenu = gui.createEmptyElement(menuRoot);
	multiplayerMenu = gui.createEmptyElement(menuRoot);
	optionsMenu = gui.createEmptyElement(menuRoot);
	creditsMenu = gui.createEmptyElement(menuRoot);
	quitMenu = gui.createEmptyElement(menuRoot);

	mainMenu->hide();
	randomMenu->hide();
	customMenu->hide();
	loadGameMenu->hide();
	multiplayerMenu->hide();
	optionsMenu->hide();
	creditsMenu->hide();
	quitMenu->hide();

	gui.createButton(
		math::Vector2i(5, 5),
		"Adventure",
		gfx::NormalFont,
		[this]() {
			std::cout << "Adventure button pressed" << std::endl;
			game.setState(IntroState); // for tests
		},
		mainMenu);
	gui.createButton(
		math::Vector2i(5, 55),
		"Random",
		gfx::NormalFont,
		[]() {
			std::cout << "Random button pressed" << std::endl;
		},
		mainMenu);
	gui.createButton(
		math::Vector2i(5, 105),
		"Singleplayer",
		gfx::NormalFont,
		[]() {
			std::cout << "Singleplayer button pressed" << std::endl;
		},
		mainMenu);
	gui.createButton(
		math::Vector2i(5, 155),
		"Load savegame",
		gfx::NormalFont,
		[]() {
			std::cout << "Load savegame button pressed" << std::endl;
		},
		mainMenu);
	gui.createButton(
		math::Vector2i(5, 205),
		"Multiplayer",
		gfx::NormalFont,
		[]() {
			std::cout << "Multiplayer button pressed" << std::endl;
		},
		mainMenu);

	gui.createButton(
		math::Vector2i(5, 300 - 25),
		"Settings",
		gfx::NormalFont,
		[]() {
			std::cout << "Settings button pressed" << std::endl;
		},
		mainMenu);
	gui.createButton(
		math::Vector2i(5, 300 + 25),
		"Editor",
		gfx::NormalFont,
		[]() {
			std::cout << "Editor button pressed" << std::endl;
		},
		mainMenu);
	gui.createButton(
		math::Vector2i(5, 300 + 75),
		"Credits",
		gfx::NormalFont,
		[]() {
			std::cout << "Credits button pressed" << std::endl;
		},
		mainMenu);

	gui.createButton(
		math::Vector2i(5, 600 - 50),
		"Quit",
		gfx::NormalFont,
		[this]() {
			std::cout << "Quit button pressed" << std::endl;
			game.stopLoop(); // todo
		},
		mainMenu);

	gui.createWindow(
		215,
		"Test",
		mainMenu);
}

}
