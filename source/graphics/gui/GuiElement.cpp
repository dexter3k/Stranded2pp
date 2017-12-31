#include "GuiElement.h"

#include "Gui.h"

namespace gfx
{

namespace gui
{

GuiElement::GuiElement(Gui & gui, GuiElement * parent, math::Vector2i position) :
	parent(nullptr),
	children(),
	position(position),
	absolutePosition(position),
	hidden(false),
	gui(gui)
{
	setParent(parent);
	updateAbsolutePosition();
}

GuiElement::~GuiElement()
{
	while (!children.empty()) {
		gui.deleteGuiElement(children.front());
	}

	if (parent != nullptr) {
		parent->removeChild(this);
	}
}

void GuiElement::animate(double deltaTime)
{
	if (hidden) {
		return;
	}
	
	updateAbsolutePosition();

	for (auto child : children) {
		child->animate(deltaTime);
	}
}

void GuiElement::draw()
{
	if (!hidden) {
		for (auto child : children) {
			child->draw();
		}
	}
}

bool GuiElement::onMouseButtonPressed(uint8_t button, int x, int y)
{
	if (!hidden) {
		for (auto child : children) {
			if (child->onMouseButtonPressed(button, x, y)) {
				return true;
			}
		}
	}

	return false;
}

bool GuiElement::onMouseButtonReleased(uint8_t button, int x, int y)
{
	if (!hidden) {
		for (auto child : children) {
			if (child->onMouseButtonReleased(button, x, y))
				return true;
		}
	}

	return false;
}

bool GuiElement::onMouseMoved(int x, int y)
{
	if (!hidden) {
		for (auto child : children) {
			if (child->onMouseMoved(x, y))
				return true;
		}
	}

	return false;
}

void GuiElement::onVisibilityChange(bool isVisible)
{
	for (auto child : children) {
		child->onVisibilityChange(isVisible);
	}
}

void GuiElement::addChild(GuiElement * child)
{
	assert(child != nullptr);

	if (child->parent != nullptr) {
		child->parent->removeChild(child);
	}

	child->parent = this;

	children.push_back(child);
}

bool GuiElement::removeChild(GuiElement * childToRemove)
{
	assert(childToRemove != nullptr);

	auto const end = children.end();
	for (auto it = children.begin(); it != end; ++it) {
		if ((*it) == childToRemove) {
			assert((*it)->parent == this);

			(*it)->parent = nullptr;
			children.erase(it);

			return true;
		}
	}

	return false;
}

void GuiElement::setParent(GuiElement * newParent)
{
	if (parent == newParent) {
		return;
	}

	if (parent != nullptr) {
		parent->removeChild(this);
	}
	
	if (newParent != nullptr) {
		newParent->addChild(this);
	}
}

bool GuiElement::isTrulyVisible() const
{
	if (parent != nullptr) {
		return isVisible() && parent->isTrulyVisible();
	}

	return isVisible();
}

void GuiElement::updateAbsolutePosition()
{
	absolutePosition = getPosition();

	if (parent != nullptr) {
		absolutePosition += parent->getAbsolutePosition();
	}
}

} // namespace gui

} // namespace gfx
