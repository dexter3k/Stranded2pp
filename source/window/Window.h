#pragma once

class Window
{
public:
	Window();
	~Window();

	bool init();

	// Ignore config value and force start in windowed mode?
	void startInWindowedMode(bool value);
private:
	bool shouldStartInWindowedMode;
};
