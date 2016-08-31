#include "Engine.h"

Engine::Engine(const std::shared_ptr<Input>& input,
		const std::shared_ptr<Graphics>& graphics,
		const std::shared_ptr<Gui>& gui,
		const std::shared_ptr<Network>& network,
		const std::shared_ptr<Sound>& sound) :
	input(input),
	graphics(graphics),
	gui(gui),
	network(network),
	sound(sound)
{}

Engine::~Engine()
{}

bool Engine::init()
{
	return true;
}
