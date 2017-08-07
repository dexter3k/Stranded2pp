#pragma once

#include <cstdint>

struct ClosedEvent
{
	/* Empty! */
};

struct ResizedEvent
{
	unsigned newWidth;
	unsigned newHeight;
};

struct FocusLostEvent
{
	/* Empty! */
};

struct FocusGainedEvent
{
	/* Empty! */
};

struct TextEnteredEvent
{
	uint32_t symbol;
};

struct KeyPressedEvent
{
	uint8_t key;
	bool shift;
	bool control;
	bool alt;
	bool super;
};

struct KeyReleasedEvent
{
	uint8_t key;
	bool shift;
	bool control;
	bool alt;
	bool super;
};

struct MouseWheelScrolledEvent
{
	double delta;
	int x;
	int y;
};

struct MouseButtonPressedEvent
{
	uint8_t button;
	int x;
	int y;
};

struct MouseButtonReleasedEvent
{
	uint8_t button;
	int x;
	int y;
};

struct MouseMovedEvent
{
	int x;
	int y;
};

struct Event
{
	enum Type
	{
		Closed,
		Resized,
		FocusLost,
		FocusGained,
		TextEntered,
		KeyPressed,
		KeyReleased,
		MouseWheelScrolled,
		MouseButtonPressed,
		MouseButtonReleased,
		MouseMoved
	} type;

	union
	{
		ClosedEvent closed;
		ResizedEvent resized;
		FocusLostEvent focusLost;
		FocusGainedEvent focusGained;
		TextEnteredEvent textEntered;
		KeyPressedEvent keyPressed;
		KeyReleasedEvent keyReleased;
		MouseWheelScrolledEvent mouseWheelScrolled;
		MouseButtonPressedEvent mouseButtonPressed;
		MouseButtonReleasedEvent mouseButtonReleased;
		MouseMovedEvent mouseMoved;
	};
};
