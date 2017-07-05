#pragma once

#include "Node.h"

#include "math/Frustum.h"
#include "math/Matrix4.h"

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
	~Camera();

	void render();

	float getNearValue() const;
	float getFarValue() const;

	const math::Frustum& getViewFrustum() const;
private:
	void updateMatrices();
private:
	float near;
	float far;
	float fieldOfView;
	float aspect;

	math::Matrix4 projection;
	math::Matrix4 view;

	math::Frustum viewFrustum;
};

} // namespace scene

} // namespace gfx
