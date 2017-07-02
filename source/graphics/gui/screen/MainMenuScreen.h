#pragma once

#include "Screen.h"

#include "input/RawInputHandler.h"

class Input;

namespace gfx
{

namespace gui
{

class GuiButton;

class MainMenuScreen : public Screen
{
	typedef Screen super;

	class InputHandler : public RawInputHandler
	{
		typedef RawInputHandler super;
	public:
		InputHandler(Input& input, MainMenuScreen& mainMenuScreen);

		bool onMouseButtonPressed(uint8_t button, int x, int y) override;
	private:
		MainMenuScreen& mainMenuScreen;
	};
	friend class InputHandler;
public:
	MainMenuScreen(Gui& gui, Input& input);
	~MainMenuScreen();

	void create() override;
	void destroy() override;

	void update(double deltaTime) override;
private:
	std::shared_ptr<InputHandler> inputHandler;

	// Currently only used for debugging
	GuiButton* testButton;
};

} // namespace gui

} // namespace gfx
