#include "Node.h"

#include <cassert>

namespace gfx
{

namespace scene
{

Node::Node(Node* parent, Scene* scene, int id, const math::Vector3f& position,
		const math::Vector3f& rotation, const math::Vector3f& scale) :
	parent(parent),
	children(),
	scene(scene),
	id(id),
	name(""),
	isVisible(true),
	position(position),
	rotation(rotation),
	scale(scale)
{
	assert(parent != nullptr);
	assert(scene != nullptr);
}

Node::~Node()
{}

void Node::addChild(Node* child)
{
	assert(child != nullptr);

	if (child->getParent() == this)
	{
		return;
	}

	children.push_back(child);
}

const std::list<Node*>& Node::getChildren() const
{
	return children;
}

bool Node::removeChild(Node* childToRemove)
{
	assert(childToRemove != nullptr);

	auto end = children.end();
	for (auto it = children.begin(); it != end; ++it)
	{
		if ((*it) == childToRemove)
		{
			if ((*it)->getParent() == this)
			{
				(*it)->setParent(nullptr);
			}

			children.erase(it);

			return true;
		}
	}

	return false;
}

int Node::getId() const
{
	return id;
}

void Node::setId(int newId)
{
	id = newId;
}

const std::string& Node::getName() const
{
	return name;
}

void Node::setName(const std::string& newName)
{
	name = newName;
}

Node* Node::getParent() const
{
	return parent;
}

void Node::setParent(Node* newParent)
{
	if (parent == newParent)
	{
		return;
	}

	if (parent != nullptr)
	{
		Node* oldParent = parent;
		parent = newParent;

		oldParent->removeChild(this);
	}
	else
	{
		parent = newParent;
	}

	parent = newParent;

	if (parent != nullptr)
	{
		parent->addChild(this);
	}
}

bool Node::getVisible() const
{
	return isVisible;
}

void Node::setVisible(bool isVisible)
{
	this->isVisible = isVisible;
}

bool Node::getTrulyVisible() const
{
	if (parent != nullptr)
	{
		return getVisible() && parent->getTrulyVisible();
	}

	return getVisible();
}

const math::Vector3f& Node::getPosition() const
{
	return position;
}

void Node::setPosition(const math::Vector3f& position)
{
	this->position = position;
}

const math::Vector3f& Node::getRotation() const
{
	return rotation;
}

void Node::setRotation(const math::Vector3f& rotation)
{
	this->rotation = rotation;
}

const math::Vector3f& Node::getScale() const
{
	return scale;
}

void Node::setScale(const math::Vector3f& scale)
{
	this->scale = scale;
}

} // namespace scene

} // namespace gfx
