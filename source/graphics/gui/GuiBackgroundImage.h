#pragma once

#include "GuiElement.h"

#include "graphics/Color.h"
#include "math/Rect.h"

namespace gfx
{

class Texture;

namespace gui
{

class GuiBackgroundImage : public GuiElement
{
	typedef GuiElement super;
public:
	GuiBackgroundImage(Gui & gui, GuiElement * parent, std::string const & imageName, Color backgroundColor,
		Color maskColor);
	~GuiBackgroundImage() override;

	void draw() override;

	void setMaskColor(Color color);
private:
	std::string textureName;
	Texture * texture;

	Color backgroundColor;
	Color maskColor;
};

} // namespace gui

} // namespace gfx
