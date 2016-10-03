#pragma once

#include <list>
#include <string>

#include "common/math/Matrix4.h"
#include "common/math/Vector3.h"

namespace gfx
{

namespace scene
{

class Scene;

class Node
{
public:
	Node(Node* parent, Scene* scene, int id = -1,
		const math::Vector3f& position = math::Vector3f(0.0f),
		const math::Vector3f& rotation = math::Vector3f(0.0f),
		const math::Vector3f& scale = math::Vector3f(1.0f));
	virtual ~Node();

	virtual void onRegisterNode();

	virtual void onAnimate(float deltaTime);

	virtual void addChild(Node* child);
	virtual const std::list<Node*>& getChildren() const;
	virtual bool removeChild(Node* child);

	virtual int getId() const;
	virtual void setId(int newId);

	virtual const std::string& getName() const;
	virtual void setName(const std::string& newName);

	virtual Node* getParent() const;
	virtual void setParent(Node* newParent);

	virtual bool getVisible() const;
	virtual void setVisible(bool isVisible);

	virtual bool getTrulyVisible() const;

	virtual const math::Vector3f& getPosition() const;
	virtual void setPosition(const math::Vector3f& position);

	virtual const math::Vector3f& getRotation() const;
	virtual void setRotation(const math::Vector3f& rotation);

	virtual const math::Vector3f& getScale() const;
	virtual void setScale(const math::Vector3f& scale);

	virtual math::Matrix4 getTransformation() const;

	virtual math::Matrix4 getAbsoluteTransformation() const;
	virtual math::Vector3f getAbsolutePosition() const;

	virtual void updateAbsoluteTransformation();

	virtual void render();
protected:
	Node* parent;
	std::list<Node*> children;

	Scene* scene;

	int id;
	std::string name;

	bool isVisible;

	math::Matrix4 absoluteTransformation;

	math::Vector3f position;
	math::Vector3f rotation;
	math::Vector3f scale;
};

} // namespace scene

} // namespace gfx
