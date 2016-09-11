#pragma once

#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "Keyboard.h"
#include "Mouse.h"


class Modification;
class RawInputHandler;
class Window;

class Input
{
	friend class RawInputHandler;
public:
	Input(Window& window);
	~Input();

	bool init(const Modification& modification);
	void update(float deltaTime);

	std::string getMouseButtonName(uint8_t button) const;
	std::string getMouseWheelUpName() const;
	std::string getMouseWheelDownName() const;
	std::string getKeyName(uint8_t key) const;

	// Raw (directly from Window) input events
	void onRawEventClosed();
	void onRawEventResized(unsigned newWidth, unsigned newHeight);
	void onRawEventLostFocus();
	void onRawEventGainedFocus();
	void onRawEventTextEntered(uint32_t symbol);
	void onRawEventKeyPressed(uint8_t key, bool alt, bool control, bool shift,
		bool super);
	void onRawEventKeyReleased(uint8_t key, bool alt, bool control, bool shift,
		bool super);
	void onRawEventMouseWheelScrolled(float delta, int x, int y);
	void onRawEventMouseButtonPressed(uint8_t button, int x, int y);
	void onRawEventMouseButtonReleased(uint8_t button, int x, int y);
	void onRawEventMouseMoved(int x, int y);
	void onRawEventMouseEntered();
	void onRawEventMouseLeft();
private:
	static const std::string keyNameInfoPath;
	static const std::string defaultName;
private:
	void addRawInputHandler(RawInputHandler* rawInputHandler);
	void removeRawInputHandler(RawInputHandler* rawInputHandler);

	bool loadKeyNames(const std::string& modificationPath);
private:
	Window&	window;

	std::vector<std::string> mouseButtonNames;
	std::string mouseWheelUpName;
	std::string mouseWheelDownName;
	std::vector<std::string> keyNames;

	std::vector<RawInputHandler*> rawInputHandlers;
};
