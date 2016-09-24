#include "Node.h"

#include <cassert>

namespace gfx
{

namespace scene
{

Node::Node(Node* parent, Scene* scene, int id, const math::Vector3f& position,
		const math::Vector3f& rotation, const math::Vector3f& scale) :
	parent(nullptr),
	children(),
	scene(scene),
	id(id),
	name(""),
	isVisible(true),
	absoluteTransformation(),
	position(position),
	rotation(rotation),
	scale(scale)
{
	assert(scene != nullptr);

	setParent(parent);
}

Node::~Node()
{}

void Node::onAnimate(float deltaTime)
{
	if (isVisible)
	{
		updateAbsolutePosition();

		for (auto& node : children)
		{
			node->onAnimate(deltaTime);
		}
	}
}

void Node::addChild(Node* child)
{
	assert(child != nullptr);

	if (child->parent == nullptr)
	{
		child->parent = this;
	}
	else
	{
		child->parent->removeChild(child);
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
			assert((*it)->parent == this);
			(*it)->parent = nullptr;

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
		parent->removeChild(this);
	}

	if (newParent != nullptr)
	{
		newParent->addChild(this);
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

math::Matrix4 Node::getTransformation() const
{
	math::Matrix4 transformationMatrix;
	transformationMatrix.setRotationDegrees(rotation);
	transformationMatrix.setTranslation(position);

	if (!scale.isEqualToRelative(math::Vector3f(1.0f, 1.0f, 1.0f)))
	{
		math::Matrix4 scaleMatrix;
		scaleMatrix.setScale(scale);

		transformationMatrix *= scaleMatrix;
	}

	return transformationMatrix;
}

math::Matrix4 Node::getAbsoluteTransformation() const
{
	return absoluteTransformation;
}

math::Vector3f Node::getAbsolutePosition() const
{
	return absoluteTransformation.getTranslation();
}

// TODO: rename to transformation
void Node::updateAbsolutePosition()
{
	if (parent != nullptr)
	{
		absoluteTransformation = parent->getAbsoluteTransformation() *
			getTransformation();
	}
	else
	{
		absoluteTransformation = getTransformation();
	}
}

} // namespace scene

} // namespace gfx
