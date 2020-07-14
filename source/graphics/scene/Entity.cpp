#include "Entity.h"

#include <iostream>

#include "Scene.h"
#include "../device/Device.h"

namespace gfx
{

namespace scene
{

Entity::Entity(Scene & scene, Node * parent, Model * model,
		math::Vector3f position, math::Vector3f rotation, math::Vector3f scale) :
	super(scene, parent, position, rotation, scale),
    solid(true),
    model(model)
{}

void Entity::onRegisterNode()
{
    if (model != nullptr && getVisible()) {
        if (solid) {
            scene.registerNodeForRendering(this, Scene::RenderPassSolid);
        } else {
            scene.registerNodeForRendering(this, Scene::RenderPassTransparent);
        }
    }

    super::onRegisterNode();
}

void Entity::render() {
    device::Device* device = scene.getDevice();
    // Camera* camera = scene.getActiveCamera();

    if (device == nullptr) {
        return;
    }

    device->setTransform(device::Device::Model, getAbsoluteTransformation());
}

} // namespace scene

} // namespace gfx
