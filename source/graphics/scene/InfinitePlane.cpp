#include "InfinitePlane.h"

#include <iostream>

#include "Camera.h"
#include "Scene.h"
#include "../IndexSize.h"
#include "../device/Device.h"

#include "common/math/Matrix4.h"
#include "common/math/Vector3.h"

namespace gfx
{

namespace scene
{

InfinitePlane::InfinitePlane(Texture* texture, Node* parent, Scene* scene,
		const math::Vector3f& position, int id) :
	super(parent, scene, id, position),
	indices{0, 1, 2, 0, 2, 3},
	vertices(),
	material()
{
	material.depthFunction = Material::Disabled;
	material.zWriteEnabled = false;
	material.textureLayers[0].texture = texture;
	material.textureLayers[0].bilinearFilter = true;
}

InfinitePlane::~InfinitePlane()
{}

void InfinitePlane::onRegisterNode()
{
	if (isVisible)
	{
		// Rendered at the same time as skyboxes
		scene->registerNodeForRendering(this, Scene::RenderPassSkybox);
	}

	super::onRegisterNode();
}

void InfinitePlane::render()
{
	return;

	device::Device* device = scene->getDevice();
	Camera* camera = scene->getActiveCamera();

	if (camera == nullptr || device == nullptr)
	{
		return;
	}

	buildVertices();

	device->setMaterial(material);
	device->drawIndexedPrimitiveList(vertices, 4, indices, 2,
		Vertex3D::Standard, Index16Bit);
}

void InfinitePlane::buildVertices()
{}

} // namespace scene

} // namespace gfx
