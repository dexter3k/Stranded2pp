#pragma once

#include <functional>

#include "GuiElement.h"

#include "graphics/FontType.h"
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
	GuiButton(Gui & gui, GuiElement * parent, math::Vector2i position,
		std::string const & text, FontType font, std::function<void(void)> onPressed);
	~GuiButton();

	void draw() override;

	bool onMouseButtonPressed(uint8_t button, int x, int y) override;
	bool onMouseMoved(int x, int y) override;
private:
	static unsigned const width;
	static unsigned const height;

	static std::string const textureName;
	static std::string const textureHoveredName;
private:
	Texture * texture;
	Texture * textureHovered;

	std::string text;

	bool isHovered;

	std::function<void(void)> onPressed;
};

} // namespace gui

} // namespace gfx
