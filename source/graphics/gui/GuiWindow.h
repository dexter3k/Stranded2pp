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
	GuiWindow(Gui & gui, GuiElement * parent, int position, std::string const & title);
	~GuiWindow();

	void draw() override;
protected:
	void drawBar(unsigned position);
private:
	static std::string const backgroundImage;
	static std::string const borderCornerImage;
	static std::string const borderVerticalImage;
	static std::string const borderHorizontalImage;
protected:
	static unsigned const width;
	static unsigned const height;
private:
	Texture * backgroundTexture;
	Texture * borderCorner;
	Texture * borderVertical;
	Texture * borderHorizontal;

	std::string title;
};

} // namespace gui

} // namespace gfx
