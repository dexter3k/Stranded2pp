#include "Intro.h"

#include "Stranded.h"
#include "graphics/gui/Gui.h"

namespace state
{

Intro::Intro(Stranded & game) :
	super(game),
	rootElement(nullptr)
{
	loadInterface();
}

void Intro::show()
{
	super::show();

	rootElement->show();
}

void Intro::hide()
{
	rootElement->hide();

	super::hide();
}

void Intro::loadInterface()
{
	assert(rootElement == nullptr);

	auto & gfx = game.getGraphics();
	auto & gui = gfx.getGui();

	rootElement = gui.createEmptyElement();
	rootElement->hide();
}

} // namespace state

// #include "IntroScreen.h"

// #include <cstdint>

// #include "graphics/gui/Gui.h"
// #include "graphics/gui/GuiBackgroundImage.h"

// namespace gfx
// {

// namespace gui
// {

// std::string const IntroScreen::logoTextureName = "sys/gfx/logo.bmp";

// IntroScreen::IntroScreen(Gui & gui) :
// 	super(gui),
// 	maxShowTime(3.0),
// 	fadeStart(maxShowTime * 0.8),
// 	fadeColor(0, 0, 0),
// 	introImage(nullptr),
// 	showTime(0.0),
// 	introEnded(false)
// {}

// void IntroScreen::create()
// {
// 	super::create();

// 	showTime = 0.0;

// 	introImage = gui.addBackgroundImage(logoTextureName);
// }

// void IntroScreen::destroy()
// {
// 	if (introImage != nullptr) {
// 		gui.deleteGuiElement(introImage);
// 		introImage = nullptr;
// 	}

// 	super::destroy();
// }

// bool IntroScreen::update(double deltaTime)
// {
// 	showTime += deltaTime;

// 	if (showTime > maxShowTime) {
// 		showTime = maxShowTime;
// 		introEnded = true;
// 	}

// 	if (showTime > fadeStart) {
// 		double fadeLength = maxShowTime - fadeStart;
// 		double fade = (showTime - fadeStart) / fadeLength;

// 		fadeColor.setAlpha(static_cast<uint8_t>(255.0 * fade));
// 		introImage->setMaskColor(fadeColor);
// 	}

// 	return !introEnded;
// }

// } // namespace gui

// } // namespace gfx
