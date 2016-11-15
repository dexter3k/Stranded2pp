#pragma once

#include <memory>
#include <string>
#include <vector>
#include <iostream>

#include "input/RawInputHandler.h"

class Engine;
class Input;
class Modification;
class Network;
class Sound;
class Window;

namespace gfx
{

	class Graphics;

} // namespace gfx

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
		Stranded& stranded;
	};
	friend class QuitEventHandler;
public:
	Stranded();
	~Stranded();

	bool init(const std::vector<std::string>& arguments);
	void run();
private:
	void stop();

	bool parseArguments(const std::vector<std::string>& arguments);

	void printWelcomeMessage();
private:
	static const std::string defaultModificationName;

	std::shared_ptr<Modification> modification;

	std::shared_ptr<Window>		window;

	std::shared_ptr<Input>		input;
	std::shared_ptr<QuitEventHandler> quitEventHandler;

	std::shared_ptr<gfx::Graphics>	graphics;

	std::shared_ptr<Network>	network;

	std::shared_ptr<Sound>		sound;

	std::shared_ptr<Engine>		engine;

	bool isRunning;
};
