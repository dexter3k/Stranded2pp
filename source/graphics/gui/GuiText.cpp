#include "GuiText.h"

namespace gfx
{

namespace gui
{

GuiText::GuiText(Gui & gui, GuiElement * parent, math::Vector2i position,
		std::string const & text, FontType, TextAlignment) :
	super(gui, parent, position),
	text(text)
	//font(font),
	//alignment(alignment)
{}

void GuiText::draw()
{
	
}

} // namespace gui

} // namespace gfx
