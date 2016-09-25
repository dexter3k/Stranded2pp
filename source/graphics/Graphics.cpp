#include "Graphics.h"

#include "device/Device.h"
#include "device/OpenGLDevice.h"
#include "scene/Scene.h"

#include "common/Modification.h"
#include "input/Input.h"

#include "scene/Camera.h"


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
		math::Vector3f(0.0f, 0.0f, 0.0f));
	scene->addSkybox(
		device->loadTextureFromFile(
			modification.getPath() + "skies/sky_up.jpg"),
		device->loadTextureFromFile(
			modification.getPath() + "skies/sky_dn.jpg"),
		device->loadTextureFromFile(
			modification.getPath() + "skies/sky_lf.jpg"),
		device->loadTextureFromFile(
			modification.getPath() + "skies/sky_rt.jpg"),
		device->loadTextureFromFile(
			modification.getPath() + "skies/sky_fr.jpg"),
		device->loadTextureFromFile(
			modification.getPath() + "skies/sky_bk.jpg"), nullptr);

	return true;
}

void Graphics::update(float deltaTime)
{
	auto camera = scene->getActiveCamera();
	if (camera != nullptr)
	{
		auto rotation = camera->getRotation();
		rotation.y += 5.0f;
		camera->setRotation(rotation);
	}
}

void Graphics::drawAll()
{
	device->beginScene();

	scene->drawAll();

	device->endScene();
}

} // namespace gfx
