#pragma once

#include "Screen.h"

#include "input/RawInputHandler.h"

#include "graphics/Color.h"

class Input;

namespace gfx
{

namespace gui
{

class GuiBackgroundImage;

class IntroScreen : public Screen
{
	typedef Screen super;

	class InputHandler : public RawInputHandler
	{
		typedef RawInputHandler super;
	public:
		InputHandler(Input& input, IntroScreen& introScreen);

		bool onKeyPressed(uint8_t key, bool alt, bool control, bool shift,
			bool super) override;
		bool onMouseButtonPressed(uint8_t button, int x, int y) override;
	private:
		IntroScreen& introScreen;
	};
	friend class InputHandler;
public:
	IntroScreen(Gui& gui, Input& input);
	~IntroScreen();

	void create() override;
	void destroy() override;

	void update(double deltaTime) override;
private:
	void skipIntro();
private:
	static const std::string logoTextureName;
private:
	std::shared_ptr<InputHandler> inputHandler;

	const double maxShowTime;
	const double fadeStart;
	Color fadeColor;

	GuiBackgroundImage* introImage;

	double showTime;
};

} // namespace gui

} // namespace gfx
