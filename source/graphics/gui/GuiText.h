#pragma once

#include <string>

#include "GuiElement.h"

#include "graphics/FontType.h"
#include "graphics/TextStyle.h"

namespace gfx
{

namespace gui
{

class GuiText : public GuiElement
{
	typedef GuiElement super;
public:
	GuiText(Gui & gui, GuiElement * parent, math::Vector2i position,
		std::string const & text, FontType font, TextStyle style);

	void draw() override;
private:
	std::string text;
	//FontType font;
	//TextStyle style;
};

} // namespace gui

} // namespace gfx
