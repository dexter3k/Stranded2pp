#pragma once

#include "Node.h"

#include "common/math/Matrix4.h"

namespace gfx
{

namespace scene
{

class Camera : public Node
{
	typedef Node super;
public:
	Camera(Node* parent, Scene* scene, int id = -1,
		const math::Vector3f& position = math::Vector3f(0.0f, 0.0f, 0.0f),
		const math::Vector3f& rotation = math::Vector3f(0.0f, 0.0f, 0.0f));
public:
	~Camera();

	void render();
private:
	void updateMatrices();
private:
	float near;
	float far;
	float fieldOfView;

	math::Matrix4 projection;
	math::Matrix4 view;
};

} // namespace scene

} // namespace gfx
