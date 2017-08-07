#pragma once

#include <string>

#include "GuiElement.h"

#include "graphics/FontType.h"

namespace gfx
{

namespace gui
{

enum TextAlignment
{
	AlignLeft,
	AlignCenter,
	AlignRight
};

class GuiText : public GuiElement
{
	typedef GuiElement super;
public:
	GuiText(Gui & gui, GuiElement * parent, math::Vector2i position,
		std::string const & text, FontType font, TextAlignment alignment);

	void draw() override;
private:
	std::string text;
	//FontType font;
	//TextAlignment alignment;
};

} // namespace gui

} // namespace gfx
