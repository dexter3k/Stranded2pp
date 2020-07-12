#include "Skybox.h"

#include <iostream>

#include "Camera.h"
#include "Scene.h"
#include "../Color.h"
#include "../IndexSize.h"
#include "../device/Device.h"

#include "math/Matrix4.h"
#include "math/Vector3.h"

namespace gfx
{

namespace scene
{

Skybox::Skybox(Texture* top, Texture* bottom, Texture* left, Texture* right,
		Texture* front, Texture* back, Node* parent, Scene* scene, int) :
	super(*scene, parent),
	indices{0, 1, 2, 0, 2, 3},
	vertices(),
	materials()
{
	Material material;
	material.lighting = false;
	material.depthFunction = Material::Disabled;
	material.zWriteEnabled = false;
	material.textureLayers[0].bilinearFilter = true;

	// Top
	float onepixel =
		(top != nullptr) ? (1.0f / (top->getSize().x * 1.5f)) : 0.0f;
	float t = 1.0f - onepixel;
	float o = 0.0f + onepixel;

	materials[0] = material;
	materials[0].textureLayers[0].texture = top;
	vertices[0 * 4 + 0] = Vertex3D( 1,  1, -1, 0, -1, 0, Color(255, 255, 255), o, o);
	vertices[0 * 4 + 1] = Vertex3D( 1,  1,  1, 0, -1, 0, Color(255, 255, 255), t, o);
	vertices[0 * 4 + 2] = Vertex3D(-1,  1,  1, 0, -1, 0, Color(255, 255, 255), t, t);
	vertices[0 * 4 + 3] = Vertex3D(-1,  1, -1, 0, -1, 0, Color(255, 255, 255), o, t);

	// Bottom
	onepixel =
		(bottom != nullptr) ? (1.0f / (bottom->getSize().x * 1.5f)) : 0.0f;
	t = 1.0f - onepixel;
	o = 0.0f + onepixel;

	materials[1] = material;
	materials[1].textureLayers[0].texture = bottom;
	vertices[1 * 4 + 0] = Vertex3D( 1, -1, -1, 0, 1, 0, Color(255, 255, 255), o, o);
	vertices[1 * 4 + 1] = Vertex3D(-1, -1, -1, 0, 1, 0, Color(255, 255, 255), o, o);
	vertices[1 * 4 + 2] = Vertex3D(-1, -1,  1, 0, 1, 0, Color(255, 255, 255), o, t);
	vertices[1 * 4 + 3] = Vertex3D( 1, -1,  1, 0, 1, 0, Color(255, 255, 255), o, t);

	// Left
	onepixel =
		(left != nullptr) ? (1.0f / (left->getSize().x * 1.5f)) : 0.0f;
	t = 1.0f - onepixel;
	o = 0.0f + onepixel;

	materials[2] = material;
	materials[2].textureLayers[0].texture = left;
	vertices[2 * 4 + 0] = Vertex3D( 1, -1, -1, -1, 0, 0, Color(255, 255, 255), t, t);
	vertices[2 * 4 + 1] = Vertex3D( 1, -1,  1, -1, 0, 0, Color(255, 255, 255), o, t);
	vertices[2 * 4 + 2] = Vertex3D( 1,  1,  1, -1, 0, 0, Color(255, 255, 255), o, o);
	vertices[2 * 4 + 3] = Vertex3D( 1,  1, -1, -1, 0, 0, Color(255, 255, 255), t, o);

	// Right
	onepixel =
		(right != nullptr) ? (1.0f / (right->getSize().x * 1.5f)) : 0.0f;
	t = 1.0f - onepixel;
	o = 0.0f + onepixel;

	materials[3] = material;
	materials[3].textureLayers[0].texture = right;
	vertices[3 * 4 + 0] = Vertex3D(-1, -1, -1,  1, 0, 0, Color(255, 255, 255), o, t);
	vertices[3 * 4 + 1] = Vertex3D(-1,  1, -1,  1, 0, 0, Color(255, 255, 255), o, o);
	vertices[3 * 4 + 2] = Vertex3D(-1,  1,  1,  1, 0, 0, Color(255, 255, 255), t, o);
	vertices[3 * 4 + 3] = Vertex3D(-1, -1,  1,  1, 0, 0, Color(255, 255, 255), t, t);

	// Front
	onepixel =
		(front != nullptr) ? (1.0f / (front->getSize().x * 1.5f)) : 0.0f;
	t = 1.0f - onepixel;
	o = 0.0f + onepixel;

	materials[4] = material;
	materials[4].textureLayers[0].texture = front;
	vertices[4 * 4 + 0] = Vertex3D(-1, -1,  1, 0, 0, -1, Color(255, 255, 255), o, t);
	vertices[4 * 4 + 1] = Vertex3D(-1,  1,  1, 0, 0, -1, Color(255, 255, 255), o, o);
	vertices[4 * 4 + 2] = Vertex3D( 1,  1,  1, 0, 0, -1, Color(255, 255, 255), t, o);
	vertices[4 * 4 + 3] = Vertex3D( 1, -1,  1, 0, 0, -1, Color(255, 255, 255), t, t);

	// Back
	onepixel =
		(back != nullptr) ? (1.0f / (back->getSize().x * 1.5f)) : 0.0f;
	t = 1.0f - onepixel;
	o = 0.0f + onepixel;

	materials[5] = material;
	materials[5].textureLayers[0].texture = back;
	vertices[5 * 4 + 0] = Vertex3D(-1, -1, -1, 0, 0, 1, Color(255, 255, 255), t, t);
	vertices[5 * 4 + 1] = Vertex3D( 1, -1, -1, 0, 0, 1, Color(255, 255, 255), o, t);
	vertices[5 * 4 + 2] = Vertex3D( 1,  1, -1, 0, 0, 1, Color(255, 255, 255), o, o);
	vertices[5 * 4 + 3] = Vertex3D(-1,  1, -1, 0, 0, 1, Color(255, 255, 255), t, o);
}

Skybox::~Skybox()
{}

void Skybox::onRegisterNode()
{
	if (getVisible())
	{
		scene.registerNodeForRendering(this, Scene::RenderPassSkybox);
	}

	super::onRegisterNode();
}

void Skybox::render()
{
	device::Device* device = scene.getDevice();
	Camera* camera = scene.getActiveCamera();

	if (camera == nullptr || device == nullptr)
	{
		return;
	}

	math::Matrix4 transformation = getAbsoluteTransformation();
	transformation.setTranslation(camera->getAbsolutePosition());

	float viewDistance = (camera->getNearValue() + camera->getFarValue()) * 0.5;
	math::Matrix4 scale;
	scale.setScale(math::Vector3f(viewDistance, viewDistance, viewDistance));

	device->setTransform(device::Device::Model, transformation * scale);

	for (unsigned i = 0; i < 6; ++i)
	{
		device->setMaterial(materials[i]);
		device->drawIndexedPrimitiveList(&(vertices[i * 4]), 4, indices, 2,
			Vertex3D::Standard, Index16Bit);
	}
}

} // namespace scene

} // namespace gfx
