#include "RawInputHandler.h"

#include <cassert>

#include "Input.h"

RawInputHandler::RawInputHandler(Input* input) :
	input(input),
	isRegistered(false)
{}

RawInputHandler::~RawInputHandler()
{
	if (isRegistered)
	{
		input->removeRawInputHandler(this);
	}
}

void RawInputHandler::init()
{
	input->addRawInputHandler(this);

	isRegistered = true;
}

void RawInputHandler::remove()
{
	if (isRegistered)
	{	
		input->removeRawInputHandler(this);
	
		isRegistered = false;
	}
}

bool RawInputHandler::onClosed()
{
	return false;
}

bool RawInputHandler::onResized(unsigned, unsigned)
{
	return false;
}

bool RawInputHandler::onLostFocus()
{
	return false;
}

bool RawInputHandler::onGainedFocus()
{
	return false;
}

bool RawInputHandler::onTextEntered(uint32_t)
{
	return false;
}

bool RawInputHandler::onKeyPressed(uint8_t, bool, bool, bool, bool)
{
	return false;
}

bool RawInputHandler::onKeyReleased(uint8_t, bool, bool, bool, bool)
{
	return false;
}

bool RawInputHandler::onMouseWheelScrolled(float, int, int)
{
	return false;
}

bool RawInputHandler::onMouseButtonPressed(uint8_t, int, int)
{
	return false;
}

bool RawInputHandler::onMouseButtonReleased(uint8_t, int, int)
{
	return false;
}

bool RawInputHandler::onMouseMoved(int, int)
{
	return false;
}

bool RawInputHandler::onMouseEntered()
{
	return false;
}

bool RawInputHandler::onMouseLeft()
{
	return false;
}
