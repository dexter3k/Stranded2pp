#pragma once

#include <iostream>
#include <memory>
#include <string>
#include <vector>

#include "common/CmdLineArgs.h"
#include "common/Modification.h"
#include "engine/Engine.h"
#include "graphics/Graphics.h"
#include "input/Input.h"
#include "input/RawInputHandler.h"
#include "network/Network.h"
#include "sound/Sound.h"
#include "window/Window.h"

class Stranded
{
	class QuitEventHandler : public RawInputHandler
	{
		typedef RawInputHandler super;
	public:
		QuitEventHandler(Input* input, Stranded& stranded) :
			super(input),
			stranded(stranded)
		{}

		bool onClosed() override
		{
			stranded.stop();

			return false;
		}
	private:
		Stranded & stranded;
	};
	friend class QuitEventHandler;
public:
	Stranded(std::vector<std::string> const & arguments);

	void run();
private:
	void stop();

	void printWelcomeMessage();
private:
	common::CmdLineArgs cmdLineArgs;

	Modification modification;

	Window window;

	Input input;
	std::shared_ptr<QuitEventHandler> quitEventHandler;

	gfx::Graphics graphics;

	Network network;

	Sound sound;

	Engine engine;

	bool shouldStop;
};
