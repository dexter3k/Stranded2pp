#include "GuiElement.h"

namespace gfx
{

namespace gui
{

GuiElement::GuiElement(GuiElement* parent, Gui* gui, int id,
		const math::Vector2i& position) :
	parent(parent),
	children(),
	gui(gui),
	id(id),
	name(""),
	isVisible(true),
	position(position),
	absolutePosition(position)
{
	assert(gui != nullptr);

	if (parent != nullptr)
	{
		absolutePosition = parent->getAbsolutePosition() + position;
	}
}

GuiElement::~GuiElement()
{
	if (parent != nullptr)
	{
		parent->removeChild(this);
	}
}

void GuiElement::onAnimate(float deltaTime)
{
	if (isVisible)
	{
		updateAbsolutePosition();

		for (auto&& child : children)
		{
			child->onAnimate(deltaTime);
		}
	}
}

void GuiElement::onDraw()
{
	if (isVisible)
	{
		updateAbsolutePosition();

		for (auto&& child : children)
		{
			child->onDraw();
		}
	}
}

void GuiElement::addChild(GuiElement* child)
{
	assert(child != nullptr);

	if (child->parent != nullptr)
	{
		child->parent->removeChild(child);
	}

	child->parent = this;

	children.push_back(child);
}

const std::list<GuiElement*>& GuiElement::getChildren() const
{
	return children;
}

bool GuiElement::removeChild(GuiElement* childToRemove)
{
	assert(childToRemove != nullptr);

	auto end = children.end();
	for (auto it = children.begin(); it != end; ++it)
	{
		if ((*it) == childToRemove)
		{
			assert((*it)->parent == this);

			(*it)->parent = nullptr;

			children.erase(it);

			return true;
		}
	}

	return false;
}

int GuiElement::getId() const
{
	return id;
}

void GuiElement::setId(int id)
{
	this->id = id;
}

const std::string& GuiElement::getName() const
{
	return name;
}

void GuiElement::setName(const std::string& name)
{
	this->name = name;
}

GuiElement* GuiElement::getParent() const
{
	return parent;
}

void GuiElement::setParent(GuiElement* newParent)
{
	if (parent == newParent)
	{
		return;
	}

	if (parent != nullptr)
	{
		parent->removeChild(this);
	}
	
	if (newParent != nullptr)
	{
		newParent->addChild(this);
	}
}

bool GuiElement::getVisible() const
{
	return isVisible;
}

void GuiElement::setVisible(bool isVisible)
{
	this->isVisible = isVisible;
}

bool GuiElement::getTrulyVisible() const
{
	if (parent != nullptr)
	{
		return getVisible() && parent->getVisible();
	}

	return getVisible();
}

const math::Vector2i& GuiElement::getPosition() const
{
	return position;
}

void GuiElement::setPosition(const math::Vector2i& position)
{
	this->position = position;
}

const math::Vector2i& GuiElement::getAbsolutePosition() const
{
	return absolutePosition;
}

void GuiElement::updateAbsolutePosition()
{
	if (parent != nullptr)
	{
		absolutePosition = parent->getAbsolutePosition() + getPosition();
	}

	absolutePosition = getPosition();
}

} // namespace gui

} // namespace gfx
