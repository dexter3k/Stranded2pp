#include "Input.h"

#include "window/Window.h"

Input::Input(const std::shared_ptr<Window>& window) :
	window(window)
{}

Input::~Input()
{}

bool Input::init()
{
	return true;
}
