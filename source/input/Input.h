#pragma once

#include <cstdint>
#include <queue>
#include <string>
#include <vector>

#include "Event.h"
#include "Keyboard.h"
#include "Mouse.h"

class Modification;
class Window;

class Input
{
	friend class Window;
public:
	Input(Window & window, Modification const & modification);

	void processInput(double deltaTime);

	bool getEvent(Event & event);

	std::string getMouseButtonName(uint8_t button) const;
	std::string getMouseWheelUpName() const;
	std::string getMouseWheelDownName() const;
	std::string getKeyName(uint8_t key) const;
private:
	// These onRawEvent* methods are called from Window- class
	void onRawEventClosed();
	void onRawEventResized(unsigned newWidth, unsigned newHeight);
	void onRawEventLostFocus();
	void onRawEventGainedFocus();
	void onRawEventTextEntered(uint32_t symbol);
	void onRawEventKeyPressed(uint8_t key, bool alt, bool control, bool shift, bool super);
	void onRawEventKeyReleased(uint8_t key, bool alt, bool control, bool shift, bool super);
	void onRawEventMouseWheelScrolled(double delta, int x, int y);
	void onRawEventMouseButtonPressed(uint8_t button, int x, int y);
	void onRawEventMouseButtonReleased(uint8_t button, int x, int y);
	void onRawEventMouseMoved(int x, int y);

	// Load key name mapping
	bool loadKeyNames(std::string const & modificationPath);
private:
	static const std::string keyNameInfoPath;
	static const std::string defaultName;
private:
	Window & window;

	std::queue<Event> events;

	std::vector<std::string> mouseButtonNames;
	std::string mouseWheelUpName;
	std::string mouseWheelDownName;
	std::vector<std::string> keyNames;
};
