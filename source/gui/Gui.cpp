#include "Gui.h"

#include "input/Input.h"

Gui::Gui(const std::shared_ptr<Input>& input) :
	input(input)
{}

Gui::~Gui()
{}

bool Gui::init()
{
	return true;
}
