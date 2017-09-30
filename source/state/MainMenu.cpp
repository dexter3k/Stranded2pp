#include "MainMenu.h"

#include <iostream>

#include "Stranded.h"
#include "graphics/gui/Gui.h"
#include "input/Mouse.h"

namespace state
{

std::string const MainMenu::menuMap = "maps/menu/menu.s2";
std::string const MainMenu::logoImage = "sys/gfx/title.bmp";

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

bool MainMenu::processEvent(Event event)
{
	if (event.type == Event::MouseButtonPressed
		&& event.mouseButtonPressed.button == mouse::Right)
	{
		// Do explosion
		return true;
	}
	
	return false;
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

	unsigned const screenWidth = 800;
	unsigned const screenHeight = 600;
	unsigned const windowPosition = 215;
	unsigned const buttonSpacing = 50;
	std::string const versionString = game.getVersionString();

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


	// *** MAIN MENU ***

	// Buttons
	unsigned buttonY = 5;
	if (true) {
		gui.createButton(
			math::Vector2i(5, buttonY),
			strings.getMenuString(strings::Adventure),
			gfx::NormalFont,
			[this]() {
				std::cout << "Adventure button pressed" << std::endl;
				game.setState(IntroState); // for tests
			},
			mainMenu);
		buttonY += buttonSpacing;
	}
	if (true) {
		gui.createButton(
			math::Vector2i(5, buttonY),
			strings.getMenuString(strings::RandomIsland),
			gfx::NormalFont,
			[this]() {
				mainMenu->hide();
				randomMenu->show();
			},
			mainMenu);
		buttonY += buttonSpacing;
	}
	if (true) {
		gui.createButton(
			math::Vector2i(5, buttonY),
			strings.getMenuString(strings::SingleIsland),
			gfx::NormalFont,
			[this]() {
				mainMenu->hide();
				customMenu->show();
			},
			mainMenu);
		buttonY += buttonSpacing;
	}
	if (true) {
		gui.createButton(
			math::Vector2i(5, buttonY),
			strings.getMenuString(strings::Load),
			gfx::NormalFont,
			[this]() {
				mainMenu->hide();
				loadGameMenu->show();
			},
			mainMenu);
		buttonY += buttonSpacing;
	}
	if (true) {
		gui.createButton(
			math::Vector2i(5, buttonY),
			strings.getMenuString(strings::Multiplayer),
			gfx::NormalFont,
			[this]() {
				mainMenu->hide();
				multiplayerMenu->show();
			},
			mainMenu);
	}

	gui.createButton(
		math::Vector2i(5, screenHeight / 2 - buttonSpacing / 2),
		strings.getMenuString(strings::Options),
		gfx::NormalFont,
		[this]() {
			mainMenu->hide();
			optionsMenu->show();
		},
		mainMenu);

	if (true) {
		gui.createButton(
			math::Vector2i(5, screenHeight / 2 + buttonSpacing / 2),
			strings.getMenuString(strings::Editor),
			gfx::NormalFont,
			[this]() {
				std::cout << "Editor button pressed" << std::endl;
				game.setState(IntroState); // for tests
			},
			mainMenu);
	}
	if (true) {
		gui.createButton(
			math::Vector2i(5, screenHeight / 2 + buttonSpacing + buttonSpacing / 2),
			strings.getMenuString(strings::Credits),
			gfx::NormalFont,
			[this]() {
				mainMenu->hide();
				creditsMenu->show();
			},
			mainMenu);
	}

	gui.createButton(
		math::Vector2i(5, screenHeight - buttonSpacing),
		strings.getMenuString(strings::Quit),
		gfx::NormalFont,
		[this]() {
			std::cout << "Quit button pressed" << std::endl;
			game.stopLoop(); // todo
		},
		mainMenu);

	// Logo image
	gui.createImage(
		logoImage,
		math::Vector2i(200 + (screenWidth - 200) / 2, 200),
		true, // centered
		mainMenu);

	// Version info
	gui.createText(
		math::Vector2i(screenWidth - 3, screenHeight - 17),
		versionString,
		gfx::TinyFont,
		gfx::TextPadRight,
		gfx::TextPadUp,
		mainMenu);


	// *** RANDOM GAME ***


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
		windowPosition,
		"Test",
		randomMenu);


	// *** SINGLEPLAYER (CUSTOM GAME) ***


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
		windowPosition,
		"Test",
		customMenu);


	// *** LOAD GAME ****


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
		windowPosition,
		"Test",
		loadGameMenu);


	// *** MULTIPLAYER ***


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
		windowPosition,
		"Test",
		multiplayerMenu);


	// *** OPTIONS ***


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
		windowPosition,
		"Test",
		optionsMenu);


	// *** CREDITS ***


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
