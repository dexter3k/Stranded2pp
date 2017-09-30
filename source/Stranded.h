#pragma once

#include <iostream>
#include <stack>
#include <string>
#include <unordered_map>
#include <vector>

#include "common/CmdLineArgs.h"
#include "common/Resources.h"
#include "common/Modification.h"
#include "common/Strings.h"
#include "engine/Engine.h"
#include "graphics/Graphics.h"
#include "input/Input.h"
#include "network/Network.h"
#include "sound/Sound.h"
#include "state/Editor.h"
#include "state/Intro.h"
#include "state/MainMenu.h"
#include "state/State.h"
#include "window/Window.h"

class Stranded
{
public:
	Stranded(std::vector<std::string> const & arguments);

	void run();
	void stopLoop();

	void setState(state::Type stateType);
	void pushState(state::Type stateType);
	void popState();

	gfx::Graphics & getGraphics() { return graphics; };
	Engine & getEngine() { return engine; };
	Strings const & getStrings() const { return strings; };

	std::string getVersionString() const { return versionString; };
private:
	void printWelcomeMessage();
private:
	static std::string const versionString;
private:
	common::CmdLineArgs cmdLineArgs;

	Modification modification;

	Resources resources;

	Strings const strings;

	Window window;

	Input input;

	gfx::Graphics graphics;

	Network network;

	Sound sound;

	Engine engine;

	state::Editor editor;
	state::Intro intro;
	state::MainMenu mainMenu;

	std::unordered_map<state::Type, state::State *> const stateMapping;

	std::stack<state::State *> currentStates;

	bool shouldStop;
};
