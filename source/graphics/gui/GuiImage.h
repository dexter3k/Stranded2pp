#pragma once

#include "GuiElement.h"

namespace gfx
{

class Texture;

namespace gui
{

class GuiImage : public GuiElement
{
	typedef GuiElement super;
public:
	GuiImage(Gui & gui, GuiElement * parent, std::string const & imageName,
		math::Vector2i position, bool centered);
	~GuiImage();

	void draw() override;
private:
	std::string const textureName;
	Texture * texture;

	bool centered;
};

} // namespace gui

} // namespace gfx
