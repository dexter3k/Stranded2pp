#include "Node.h"

#include <cassert>
#include <iostream>

#include "Scene.h"

namespace gfx
{

namespace scene
{

Node::Node(Scene & scene, Node * parent, math::Vector3f position,
		math::Vector3f rotation, math::Vector3f scale) :
	parent(nullptr),
	children(),
	absoluteTransformation(),
	position(position),
	rotation(rotation),
	scale(scale),
	isVisible(true),
	scene(scene)
{
	if (isVisible) {
		setParent(parent);
		updateAbsoluteTransformation();
	}
}

Node::~Node()
{
	while (!children.empty()) {
		scene.removeNode(children.front());
	}

	if (parent != nullptr) {
		parent->removeChild(this);
	}
}

void Node::onRegisterNode()
{
	if (isVisible) {
		for (auto node : children) {
			node->onRegisterNode();
		}
	}
}

void Node::onAnimate(float deltaTime)
{
	if (isVisible) {
		updateAbsoluteTransformation();

		for (auto node : children) {
			node->onAnimate(deltaTime);
		}
	}
}

void Node::addChild(Node * child)
{
	assert(child != nullptr);

	if (child->parent != nullptr) {
		child->parent->removeChild(child);
	}

	child->parent = this;

	children.push_back(child);
}

bool Node::removeChild(Node * childToRemove)
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

	assert(false);

	return false;
}

void Node::setParent(Node * newParent)
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

bool Node::getTrulyVisible() const
{
	if (parent != nullptr) {
		return getVisible() && parent->getTrulyVisible();
	}

	return getVisible();
}

math::Matrix4 Node::getTransformation() const
{
	math::Matrix4 transformationMatrix;
	transformationMatrix.setRotationDegrees(rotation);
	transformationMatrix.setTranslation(position);

	if (!scale.isEqualToRelative(math::Vector3f(1.0f, 1.0f, 1.0f))) {
		math::Matrix4 scaleMatrix;
		scaleMatrix.setScale(scale);

		transformationMatrix *= scaleMatrix;
	}

	return transformationMatrix;
}

void Node::updateAbsoluteTransformation()
{
	absoluteTransformation = getTransformation();

	if (parent != nullptr) {
		absoluteTransformation *= parent->getAbsoluteTransformation();
	}
}

} // namespace scene

} // namespace gfx
