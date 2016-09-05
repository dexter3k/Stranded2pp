#include "RawInputHandler.h"

#include "Input.h"

RawInputHandler::RawInputHandler(const std::shared_ptr<Input>& input) :
	input(input)
{
	input->addRawInputHandler(this);
}

RawInputHandler::~RawInputHandler()
{
	input->removeRawInputHandler(this);
}

bool RawInputHandler::onClosed()
{
	return false;
}

bool RawInputHandler::onResized(unsigned newWidth, unsigned newHeight)
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

bool RawInputHandler::onTextEntered(uint32_t symbol)
{
	return false;
}

bool RawInputHandler::onKeyPressed(uint8_t key, bool alt, bool control, bool shift, bool super)
{
	return false;
}

bool RawInputHandler::onKeyReleased(uint8_t key, bool alt, bool control, bool shift, bool super)
{
	return false;
}

bool RawInputHandler::onMouseWheelScrolled(float delta, int x, int y)
{
	return false;
}

bool RawInputHandler::onMouseButtonPressed(uint8_t button, int x, int y)
{
	return false;
}

bool RawInputHandler::onMouseButtonReleased(uint8_t button, int x, int y)
{
	return false;
}

bool RawInputHandler::onMouseMoved(int x, int y)
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
