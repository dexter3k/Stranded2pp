#include "InfinitePlane.h"

#include <iostream>

#include "Camera.h"
#include "Scene.h"
#include "../IndexSize.h"
#include "../device/Device.h"

#include "common/math/Frustum.h"
#include "common/math/Line.h"
#include "common/math/Matrix4.h"
#include "common/math/Plane.h"
#include "common/math/Vector3.h"

namespace gfx
{

namespace scene
{

InfinitePlane::InfinitePlane(Texture* texture, Node* parent, Scene* scene,
		const Color& planeColor, float textureScale,
		const math::Vector3f& position, int id) :
	super(parent, scene, id, position),
	indices{0, 2, 1, 0, 3, 2},
	vertices(),
	material(),
	color(planeColor),
	textureScale(textureScale),
	drawnAsSkybox(false)
{
	material.textureLayers[0].texture = texture;
}

InfinitePlane::~InfinitePlane()
{}

void InfinitePlane::setColor(const Color& color)
{
	this->color = color;
}

Material& InfinitePlane::getMaterial()
{
	return material;
}

void InfinitePlane::drawAsSkybox(bool value)
{
	drawnAsSkybox = value;
}

void InfinitePlane::onRegisterNode()
{
	if (isVisible)
	{
		// Rendered at the same time as skyboxes
		scene->registerNodeForRendering(this,
			drawnAsSkybox ? Scene::RenderPassSkybox : Scene::RenderPassSolid);
	}

	super::onRegisterNode();
}

void InfinitePlane::render()
{
	device::Device* device = scene->getDevice();
	Camera* camera = scene->getActiveCamera();
	if (camera == nullptr || device == nullptr)
	{
		return;
	}

	if (!buildVertices())
	{
		return;
	}

	math::Matrix4 transform;
	transform.setTranslation(position);
	device->setTransform(device::Device::Model, transform);

	device->setMaterial(material);
	device->drawIndexedPrimitiveList(vertices, 4, indices, 2,
		Vertex3D::Standard, Index16Bit);
}

bool InfinitePlane::buildVertices()
{
	device::Device* device = scene->getDevice();
	Camera* camera = scene->getActiveCamera();
	if (camera == nullptr || device == nullptr)
	{
		return false;
	}

	const math::Frustum& frustum = camera->getViewFrustum();

	math::Vector3f eye = frustum.getPoint(math::Frustum::Eye);
	eye -= position;
	if (eye.y <= 0.0f)
	{
		// We are below plane - no rendering needed
		return false;
	}

	math::Vector3f in_verts[4] = {
		frustum.getPoint(math::Frustum::FarTopLeft) - position,
		frustum.getPoint(math::Frustum::FarTopRight) - position,
		frustum.getPoint(math::Frustum::FarBottomRight) - position,
		frustum.getPoint(math::Frustum::FarBottomLeft) - position
	};

	math::Vector3f out_verts[5];

	math::Plane plane(math::Vector3f(0.0f, 1.0f, 0.0f), 0.0f);

	unsigned out_count = 0;

	for (unsigned i = 0; i < 4; ++i)
	{
		const math::Vector3f& vert = in_verts[i];
		const math::Vector3f& prev_vert = in_verts[(i - 1) & 3];

		if (vert.y > 0.0f)
		{
			if (prev_vert.y <= 0.0f)
			{
				float t = prev_vert.y / (prev_vert.y - vert.y);
				out_verts[out_count++] = (vert - prev_vert) * t + prev_vert;
			}
		}
		else
		{
			if (prev_vert.y > 0.0f)
			{
				float t = prev_vert.y / (prev_vert.y - vert.y);
				out_verts[out_count++] = (vert - prev_vert) * t + prev_vert;
			}

			out_verts[out_count++] = plane.getIntersectionPoint(
				math::Line(eye, vert - eye));
		}
	}

	if (out_count > 2 && out_count < 6)
	{
		for (unsigned i = 0; i < out_count; ++i)
		{
			const math::Vector3f& vert = out_verts[i];

			vertices[i] = Vertex3D(vert, plane.n, color,
				math::Vector2f(vert.x / textureScale, vert.z / textureScale));
		}
	}

	return true;
}

} // namespace scene

} // namespace gfx
