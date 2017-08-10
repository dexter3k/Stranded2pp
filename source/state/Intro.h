#pragma once

#include "State.h"

#include "graphics/gui/GuiElement.h"
#include "graphics/gui/GuiBackgroundImage.h"

namespace state
{

class Intro : public State
{
	typedef State super;
public:
	Intro(Stranded & game);

	void show() override;
	void hide() override;

	bool processEvent(Event event) override;
	void update(double deltaTime) override;
private:
	void loadInterface();
	void skipIntro();

	static std::string const introImageName;
	static double const fadingStepPerSecond;
	static double const startValue;
	static double const fadeinMax;
	static double const fadeoutMin;

	gfx::gui::GuiElement * rootElement;
	gfx::gui::GuiBackgroundImage * introImage;

	double a;
	bool fadein;
};

} // namespace state
