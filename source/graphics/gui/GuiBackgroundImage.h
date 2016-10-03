#pragma once

#include "GuiElement.h"

#include "../Color.h"
#include "common/math/Rect.h"

namespace gfx
{

class Texture;

namespace gui
{

class GuiBackgroundImage : public GuiElement
{
	typedef GuiElement super;
public:
	GuiBackgroundImage(GuiElement* parent, Gui* gui, Texture* backgroundTexture,
		const Color& backgroundColor = Color(0, 0, 0),
		const Color& maskColor = Color(0, 0, 0, 0),
		const math::Recti& sourceRectangle = math::Recti(0, 0, 0, 0),
		int id = -1);
	~GuiBackgroundImage();

	void onDraw() override;

	void setMaskColor(const Color& color);
private:
	Texture* texture;
	math::Recti destinationRectangle;
	math::Recti sourceRectangle;

	Color backgroundColor;
	Color maskColor;
};

} // namespace gui

} // namespace gfx
