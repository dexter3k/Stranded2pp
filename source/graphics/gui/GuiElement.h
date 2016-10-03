#pragma once

#include <list>
#include <string>

#include "common/math/Vector2.h"

namespace gfx
{

namespace gui
{

class Gui;

class GuiElement
{
public:
	GuiElement(GuiElement* parent, Gui* gui, int id = -1,
		const math::Vector2i& position = math::Vector2i(0, 0));
	virtual ~GuiElement();

	virtual void onAnimate(float deltaTime);
	virtual void onDraw();
	virtual bool onMouseButtonPressed(uint8_t button, int x, int y);
	virtual bool onMouseMoved(int x, int y);

	virtual void addChild(GuiElement* child);
	virtual const std::list<GuiElement*>& getChildren() const;
	virtual bool removeChild(GuiElement* childToRemove);

	virtual int getId() const;
	virtual void setId(int id);

	virtual const std::string& getName() const;
	virtual void setName(const std::string& name);

	virtual GuiElement* getParent() const;
	virtual void setParent(GuiElement* newParent);

	virtual bool getVisible() const;
	virtual void setVisible(bool isVisible);

	virtual bool getTrulyVisible() const;

	virtual const math::Vector2i& getPosition() const;
	virtual void setPosition(const math::Vector2i& position);

	virtual const math::Vector2i& getAbsolutePosition() const;

	virtual void updateAbsolutePosition();
protected:
	GuiElement* parent;
	std::list<GuiElement*> children;

	Gui* gui;

	int id;
	std::string name;

	bool isVisible;

	math::Vector2i position;
	math::Vector2i absolutePosition;
};

} // namespace gui

} // namespace gfx
