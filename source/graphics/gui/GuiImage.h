#pragma once

#include "GuiElement.h"

#include "math/Rect.h"

namespace gfx
{

class Texture;

namespace gui
{

class GuiImage : public GuiElement
{
	typedef GuiElement super;
public:
	GuiImage(Gui & gui, GuiElement * parent, Texture * texture,
		math::Recti const & destinationRectangle, math::Recti const & sourceRectangle);

	void draw() override;
private:
	Texture * texture;

	math::Recti destinationRectangle;
	math::Recti sourceRectangle;
};

} // namespace gui

} // namespace gfx
