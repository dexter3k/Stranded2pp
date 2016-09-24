#include "Graphics.h"

#include "device/Device.h"
#include "device/OpenGLDevice.h"
#include "scene/Scene.h"

#include "common/Modification.h"
#include "input/Input.h"

namespace gfx
{

Graphics::Graphics(Input& input) :
	input(input),
	device(new device::OpenGLDevice()),
	scene(new scene::Scene(*this, device.get()))
{}

Graphics::~Graphics()
{}

bool Graphics::init(const Modification& modification)
{
	if (!device->init())
	{
		return false;
	}

	scene->addCamera(nullptr, math::Vector3f(0.0f, 0.0f, 0.0f),
		math::Vector3f(10.0f, 15.0f, 0.0f));

	return true;
}

void Graphics::update(float deltaTime)
{}

void Graphics::drawAll()
{
	device->beginScene();

	scene->drawAll();

	device->endScene();
}

} // namespace gfx
