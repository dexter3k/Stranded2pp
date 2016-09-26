#pragma once

#include "GuiElement.h"

#include "common/math/Rect.h"
#include "common/math/Vector2.h"

namespace gfx
{

class Texture;

namespace gui
{

class GuiButton : public GuiElement
{
	typedef GuiElement super;
public:
	GuiButton(Texture* normalTexture, Texture* hoverTexture,
		const math::Vector2i& position, const math::Recti& sourceRectangle,
		GuiElement* parent, Gui* gui, int id = -1);
	~GuiButton();

	void draw();
private:
	Texture* textures[2];

	math::Vector2i position;
	math::Recti sourceRectangle;

	bool isHovered;
};

} // namespace gui

} // namespace gfx
