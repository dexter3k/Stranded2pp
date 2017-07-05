#pragma once

#include <iostream>
#include <string>
#include <vector>

#include "common/CmdLineArgs.h"
#include "common/Modification.h"
#include "engine/Engine.h"
#include "graphics/Graphics.h"
#include "input/Input.h"
#include "network/Network.h"
#include "sound/Sound.h"
#include "window/Window.h"

class Stranded
{
public:
	Stranded(std::vector<std::string> const & arguments);

	void run();
	void stopLoop();
private:
	void printWelcomeMessage();
private:
	common::CmdLineArgs cmdLineArgs;

	Modification modification;

	Window window;

	Input input;

	gfx::Graphics graphics;

	Network network;

	Sound sound;

	Engine engine;

	bool shouldStop;
};
