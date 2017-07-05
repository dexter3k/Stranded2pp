#pragma once

#include "GuiElement.h"

#include "math/Rect.h"
#include "math/Vector2.h"

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

	void onDraw() override;
	bool onMouseButtonPressed(uint8_t button, int x, int y) override;
	bool onMouseMoved(int x, int y) override;
private:
	Texture* textures[2];

	math::Recti sourceRectangle;

	bool isHovered;
};

} // namespace gui

} // namespace gfx
