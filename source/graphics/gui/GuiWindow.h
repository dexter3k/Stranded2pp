#pragma once

#include <string>

#include "GuiElement.h"

namespace gfx
{

class Texture;

namespace gui
{

class GuiWindow : public GuiElement
{
	typedef GuiElement super;
public:
	GuiWindow(Gui & gui, GuiElement * parent, math::Vector2i position);
	~GuiWindow();

	void draw() override;
private:
	static std::string const backgroundImage;
protected:
	static unsigned const width;
	static unsigned const height;
private:
	Texture * backgroundTexture;
};

} // namespace gui

} // namespace gfx
