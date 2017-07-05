#pragma once

#include <string>

#include "Screen.h"
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
	const double maxShowTime;
	const double fadeStart;
	Color fadeColor;

	GuiBackgroundImage* introImage;

	double showTime;
};

} // namespace gui

} // namespace gfx
