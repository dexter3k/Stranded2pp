#pragma once

#include <list>
#include <string>

#include "math/Matrix4.h"
#include "math/Vector3.h"

namespace gfx
{

namespace scene
{

class Scene;

class Node
{
public:
	Node(Scene & scene, Node * parent,
		math::Vector3f position = math::Vector3f(0.0f),
		math::Vector3f rotation = math::Vector3f(0.0f),
		math::Vector3f scale = math::Vector3f(1.0f));
	virtual ~Node();

	virtual void onRegisterNode();
	virtual void onAnimate(float deltaTime);
	virtual void render() {};

	void addChild(Node * child);
	bool removeChild(Node * child);
	std::list<Node *> const & getChildren() const { return children; };

	Node * getParent() const { return parent; };
	void setParent(Node * newParent);

	bool getVisible() const { return isVisible; };
	void setVisible(bool isVisible) { this->isVisible = isVisible; };

	bool getTrulyVisible() const;

	math::Vector3f getPosition() const { return position; };
	void setPosition(math::Vector3f position) { this->position = position; };

	math::Vector3f getRotation() const { return rotation; };
	void setRotation(math::Vector3f rotation) { this->rotation = rotation; };

	math::Vector3f getScale() const { return scale; };
	void setScale(math::Vector3f scale) { this->scale = scale; };

	math::Matrix4 getTransformation() const;

	math::Matrix4 const & getAbsoluteTransformation() const { return absoluteTransformation; };
	math::Vector3f getAbsolutePosition() const { return absoluteTransformation.getTranslation(); };
	void updateAbsoluteTransformation();
private:
	Node * parent;
	std::list<Node *> children;

	math::Matrix4 absoluteTransformation;
	math::Vector3f position;
	math::Vector3f rotation;
	math::Vector3f scale;

	bool isVisible;
protected:
	Scene & scene;
};

} // namespace scene

} // namespace gfx
