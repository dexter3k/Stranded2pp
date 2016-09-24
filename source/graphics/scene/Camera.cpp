#include "Camera.h"

#include <cassert>
#include <iostream>

#include "Scene.h"
#include "../device/Device.h"

namespace gfx
{

namespace scene
{

Camera::Camera(Node* parent, Scene* scene, int id,
		const math::Vector3f& position, const math::Vector3f& rotation) :
	super(parent, scene, id, position, rotation),
	near(1.0f),
	far(1000.0f),
	fieldOfView(75.0f),
	projection(),
	view()
{
	device::Device* device = scene->getDevice();

	//auto renderTargetSize = device->getRenderTargetSize();
	auto renderTargetSize = math::Vector2u(800, 600);
	float aspect =static_cast<float>(renderTargetSize.x) /
		static_cast<float>(renderTargetSize.y);

	projection.buildProjectionMatrixPerspective(fieldOfView, aspect, near, far);
}

Camera::~Camera()
{}

void Camera::render()
{
	updateMatrices();

	device::Device* device = scene->getDevice();
	
	if (device != nullptr)
	{
		device->setTransform(device::Device::Projection, projection);
		device->setTransform(device::Device::View, view);
	}
}

void Camera::updateMatrices()
{
	math::Vector3f position = getAbsolutePosition();
	math::Vector3f rotation = getAbsoluteTransformation().getRotationDegrees();

	// Instead of finding inverse of the camera’s transformation matrix
	view.setRotationDegrees(-rotation);
	view.setTranslation(-position);
}

} // namespace scene

} // namespace gfx
