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

	auto & strings = game.getStrings();
	auto & gfx = game.getGraphics();
	auto & gui = gfx.getGui();

	//unsigned screenWidth = 800;
	unsigned screenHeight = 600;

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

	// Main screen
	gui.createButton(
		math::Vector2i(5, 5),
		strings.getMenuString(strings::Adventure),
		gfx::NormalFont,
		[this]() {
			std::cout << "Adventure button pressed" << std::endl;
			game.setState(IntroState); // for tests
		},
		mainMenu);
	gui.createButton(
		math::Vector2i(5, 55),
		strings.getMenuString(strings::RandomIsland),
		gfx::NormalFont,
		[this]() {
			mainMenu->hide();
			randomMenu->show();
		},
		mainMenu);
	gui.createButton(
		math::Vector2i(5, 105),
		strings.getMenuString(strings::SingleIsland),
		gfx::NormalFont,
		[this]() {
			mainMenu->hide();
			customMenu->show();
		},
		mainMenu);
	gui.createButton(
		math::Vector2i(5, 155),
		strings.getMenuString(strings::Load),
		gfx::NormalFont,
		[this]() {
			mainMenu->hide();
			loadGameMenu->show();
		},
		mainMenu);
	gui.createButton(
		math::Vector2i(5, 205),
		strings.getMenuString(strings::Multiplayer),
		gfx::NormalFont,
		[this]() {
			mainMenu->hide();
			multiplayerMenu->show();
		},
		mainMenu);

	gui.createButton(
		math::Vector2i(5, screenHeight / 2 - 25),
		strings.getMenuString(strings::Options),
		gfx::NormalFont,
		[this]() {
			mainMenu->hide();
			optionsMenu->show();
		},
		mainMenu);
	gui.createButton(
		math::Vector2i(5, screenHeight / 2 + 25),
		strings.getMenuString(strings::Editor),
		gfx::NormalFont,
		[this]() {
			std::cout << "Editor button pressed" << std::endl;
			game.setState(IntroState); // for tests
		},
		mainMenu);
	gui.createButton(
		math::Vector2i(5, screenHeight / 2 + 75),
		strings.getMenuString(strings::Credits),
		gfx::NormalFont,
		[this]() {
			mainMenu->hide();
			creditsMenu->show();
		},
		mainMenu);

	gui.createButton(
		math::Vector2i(5, screenHeight - 50),
		strings.getMenuString(strings::Quit),
		gfx::NormalFont,
		[this]() {
			std::cout << "Quit button pressed" << std::endl;
			game.stopLoop(); // todo
		},
		mainMenu);

	// Random game
	gui.createButton(
		math::Vector2i(5, screenHeight - 50),
		strings.getMenuString(strings::Back),
		gfx::NormalFont,
		[this]() {
			randomMenu->hide();
			mainMenu->show();
		},
		randomMenu);
	gui.createWindow(
		215,
		"Test",
		randomMenu);

	// Singleplayer
	gui.createButton(
		math::Vector2i(5, screenHeight - 50),
		strings.getMenuString(strings::Back),
		gfx::NormalFont,
		[this]() {
			customMenu->hide();
			mainMenu->show();
		},
		customMenu);
	gui.createWindow(
		215,
		"Test",
		customMenu);

	// Load
	gui.createButton(
		math::Vector2i(5, screenHeight - 50),
		strings.getMenuString(strings::Back),
		gfx::NormalFont,
		[this]() {
			loadGameMenu->hide();
			mainMenu->show();
		},
		loadGameMenu);
	gui.createWindow(
		215,
		"Test",
		loadGameMenu);

	// Multiplayer
	gui.createButton(
		math::Vector2i(5, screenHeight - 50),
		strings.getMenuString(strings::Back),
		gfx::NormalFont,
		[this]() {
			multiplayerMenu->hide();
			mainMenu->show();
		},
		multiplayerMenu);
	gui.createWindow(
		215,
		"Test",
		multiplayerMenu);

	// Options
	gui.createButton(
		math::Vector2i(5, screenHeight - 50),
		"Back (todo)",
		gfx::NormalFont,
		[this]() {
			optionsMenu->hide();
			mainMenu->show();
		},
		optionsMenu);
	gui.createWindow(
		215,
		"Test",
		optionsMenu);

	// Credits
	gui.createButton(
		math::Vector2i(5, screenHeight - 50),
		strings.getMenuString(strings::Back),
		gfx::NormalFont,
		[this]() {
			creditsMenu->hide();
			mainMenu->show();
		},
		creditsMenu);
}

}
