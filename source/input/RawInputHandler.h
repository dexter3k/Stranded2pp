#pragma once

#include <memory>

class Input;

class RawInputHandler
{
public:
	RawInputHandler(Input* input);
	virtual ~RawInputHandler();

	void init();
	void remove();

	virtual bool onClosed();
	virtual bool onResized(unsigned newWidth, unsigned newHeight);
	virtual bool onLostFocus();
	virtual bool onGainedFocus();
	virtual bool onTextEntered(uint32_t symbol);
	virtual bool onKeyPressed(uint8_t key, bool alt, bool control, bool shift,
		bool super);
	virtual bool onKeyReleased(uint8_t key, bool alt, bool control, bool shift,
		bool super);
	virtual bool onMouseWheelScrolled(float delta, int x, int y);
	virtual bool onMouseButtonPressed(uint8_t button, int x, int y);
	virtual bool onMouseButtonReleased(uint8_t button, int x, int y);
	virtual bool onMouseMoved(int x, int y);
	virtual bool onMouseEntered();
	virtual bool onMouseLeft();
private:
	Input* input;

	bool isRegistered;
};
