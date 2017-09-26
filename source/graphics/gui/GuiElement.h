#pragma once

#include <list>
#include <string>

#include "math/Vector2.h"

namespace gfx
{

namespace gui
{

class Gui;

class GuiElement
{
public:
	GuiElement(Gui & gui, GuiElement * parent, math::Vector2i position = math::Vector2i(0, 0));
	virtual ~GuiElement();

	virtual void animate(double deltaTime);
	virtual void draw();

	virtual bool onMouseButtonPressed(uint8_t button, int x, int y);
	virtual bool onMouseButtonReleased(uint8_t button, int x, int y);
	virtual bool onMouseMoved(int x, int y);
	virtual void onVisibilityChange(bool isVisible);

	void addChild(GuiElement * child);
	bool removeChild(GuiElement * childToRemove);

	std::list<GuiElement *> const & getChildren() const { return children; };

	GuiElement * getParent() const { return parent; };
	void setParent(GuiElement * newParent);

	bool isVisible() const { return !hidden; };
	void hide() { hidden = true; onVisibilityChange(!hidden); };
	void show() { hidden = false; onVisibilityChange(!hidden); };

	bool isTrulyVisible() const;

	math::Vector2i getPosition() const { return position; };
	void setPosition(math::Vector2i position) { this->position = position; };

	math::Vector2i getAbsolutePosition() const { return absolutePosition; };

	void updateAbsolutePosition();
private:
	GuiElement * parent;

	std::list<GuiElement *> children;

	math::Vector2i position;
	math::Vector2i absolutePosition;

	bool hidden;
protected:
	Gui & gui;
};

} // namespace gui

} // namespace gfx
