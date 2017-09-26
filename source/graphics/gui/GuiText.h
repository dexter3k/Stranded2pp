#pragma once

#include "GuiElement.h"

#include "graphics/FontType.h"
#include "graphics/TextPadding.h"

namespace gfx
{

namespace gui
{

class GuiText : public GuiElement
{
	typedef GuiElement super;
public:
	GuiText(Gui & gui, GuiElement * parent, math::Vector2i position,
		std::string const & text, FontType font, TextHorizontalPadding horizontalPadding,
		TextVerticalPadding verticalPadding);

	void draw() override;
private:
	std::string const text;
	FontType const font;
	TextHorizontalPadding const horizontalPadding;
	TextVerticalPadding const verticalPadding;
};

} // namespace gui

} // namespace gfx
