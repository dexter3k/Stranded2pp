#include "Window.h"

Window::Window() :
	shouldStartInWindowedMode(false)
{}

Window::~Window()
{}

bool Window::init()
{
	return true;
}

void Window::startInWindowedMode(bool value)
{
	shouldStartInWindowedMode = value;
}
