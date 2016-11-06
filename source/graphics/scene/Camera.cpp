#include "Camera.h"

#include <cassert>
#include <iostream>

#include "Scene.h"
#include "../device/Device.h"

#include "common/math/MathUtility.h"

namespace gfx
{

namespace scene
{

Camera::Camera(Node* parent, Scene* scene, int id,
		const math::Vector3f& position, const math::Vector3f& rotation) :
	super(parent, scene, id, position, rotation),
	near(0.1f),
	far(100.0f),
	fieldOfView(75.0f),
	aspect(800.0f / 600.0f),
	projection(),
	view(),
	viewFrustum()
{
	device::Device* device = scene->getDevice();

	if (device != nullptr)
	{
		auto renderTargetSize = device->getRenderTargetSize();
		aspect =static_cast<float>(renderTargetSize.x) /
			static_cast<float>(renderTargetSize.y);
	}

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
		auto renderTargetSize = device->getRenderTargetSize();
		float aspect =static_cast<float>(renderTargetSize.x) /
			static_cast<float>(renderTargetSize.y);

		// Rebuild projection when needed
		if (!math::compareRelative(aspect, this->aspect))
		{
			this->aspect = aspect;

			projection.buildProjectionMatrixPerspective(fieldOfView, aspect,
				near, far);

			std::cout << "Rebuild" << std::endl;
		}

		device->setTransform(device::Device::Projection, projection);
		device->setTransform(device::Device::View, view);
	}

	viewFrustum.setMatrix(projection * view);
}

float Camera::getNearValue() const
{
	return near;
}

float Camera::getFarValue() const
{
	return far;
}

const math::Frustum& Camera::getViewFrustum() const
{
	return viewFrustum;
}

void Camera::updateMatrices()
{
	math::Vector3f position = getAbsolutePosition();
	math::Vector3f rotation = getAbsoluteTransformation().getRotationDegrees();

	view.buildFirstPersonCameraMatrix(position, rotation);
}

} // namespace scene

} // namespace gfx
