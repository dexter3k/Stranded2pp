#include "Intro.h"

#include <algorithm>

#include "Stranded.h"
#include "graphics/gui/Gui.h"

namespace state
{

std::string const Intro::introImageName = "sys/gfx/logo.bmp";
double const Intro::fadingStepPerSecond = 1.25;
double const Intro::startValue = -0.3;
double const Intro::fadeinMax = 2.5;
double const Intro::fadeoutMin = -0.5;

Intro::Intro(Stranded & game) :
	super(game),
	rootElement(nullptr),
	introImage(nullptr),
	a(0.0),
	fadein(true)
{
	loadInterface();
}

void Intro::show()
{
	super::show();

	a = startValue;
	fadein = true;

	rootElement->show();
}

void Intro::hide()
{
	rootElement->hide();

	super::hide();
}

bool Intro::processEvent(Event event)
{
	switch (event.type) {
	case Event::KeyPressed:
		if (event.keyPressed.key == kb::S) {
			fadein = true;
			a = 1.5;
			return true;
		}

		// fallthrough
	case Event::MouseButtonPressed:
		skipIntro();

		return true;
	default:
		return false;
	}
}

void Intro::update(double deltaTime)
{
	super::update(deltaTime);

	if (fadein) {
		a += deltaTime * fadingStepPerSecond;
		if (a > fadeinMax)
			fadein = false;
	} else {
		a -= deltaTime * fadingStepPerSecond;
	}

	double alpha = std::max(0.0, std::min(1.0, a));

	assert(introImage != nullptr);
	introImage->setMaskColor(gfx::Color(0, 0, 0, 255 - 255 * alpha));

	if (!fadein && a < fadeoutMin)
		skipIntro();
}

void Intro::loadInterface()
{
	assert(rootElement == nullptr);

	auto & gfx = game.getGraphics();
	auto & gui = gfx.getGui();

	rootElement = gui.createEmptyElement();
	rootElement->hide();

	introImage = gui.createBackgroundImage(introImageName, gfx::Color(0, 0, 0), gfx::Color(0, 0, 0, 0), rootElement);
}

void Intro::skipIntro()
{
	game.setState(MainMenuState);
}

} // namespace state
