#include "GuiText.h"

#include "Gui.h"

namespace gfx
{

namespace gui
{

GuiText::GuiText(Gui & gui, GuiElement * parent, math::Vector2i position,
	std::string const & text, FontType font, TextHorizontalPadding horizontalPadding,
	TextVerticalPadding verticalPadding) :
	super(gui, parent, position),
	text(text),
	font(font),
	horizontalPadding(horizontalPadding),
	verticalPadding(verticalPadding)
{}

void GuiText::draw()
{
	if (text.empty()) {
		return;
	}

	auto & textEngine = gui.getTextEngine();

	textEngine.drawSingleLine(font, text, getPosition(), horizontalPadding,
		verticalPadding);
}

} // namespace gui

} // namespace gfx
