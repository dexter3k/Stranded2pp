#pragma once

#include "GuiElement.h"

#include "common/math/Rect.h"

namespace gfx
{

class Texture;

namespace gui
{

class GuiImage : public GuiElement
{
	typedef GuiElement super;
public:
	GuiImage(Texture* texture, const math::Recti& destinationRectangle,
		const math::Recti& sourceRectangle, GuiElement* parent, Gui* gui,
		int id = -1);
	~GuiImage();

	void onDraw() override;
private:
	Texture* texture;
	math::Recti destinationRectangle;
	math::Recti sourceRectangle;
};

} // namespace gui

} // namespace gfx
