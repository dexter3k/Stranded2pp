#include "Graphics.h"

#include <vector>

#include "device/Device.h"
#include "device/OpenGLDevice.h"
#include "scene/Scene.h"

#include "common/Modification.h"
#include "input/Input.h"

#include "scene/Camera.h"
#include "scene/Terrain.h"

#include "gui/Gui.h"


namespace gfx
{

Graphics::Graphics(Input& input) :
	input(input),
	device(new device::OpenGLDevice()),
	scene(new scene::Scene(*this, device.get())),
	gui(new gui::Gui(input, device.get())),
	terrainNode(nullptr)
{}

Graphics::~Graphics()
{}

bool Graphics::init(const Modification& modification)
{
	if (!device->init())
	{
		return false;
	}

	if (!gui->init(modification))
	{
		return false;
	}

	scene->addCamera(nullptr, math::Vector3f(0.0f, 15.f, 15.0f),
		math::Vector3f(35.0f, 0.0f, 0.0f));
	
	//scene->addSkybox(
	//	device->loadTextureFromFile(
	//		modification.getPath() + "skies/sky_up.jpg"),
	//	device->loadTextureFromFile(
	//		modification.getPath() + "skies/sky_dn.jpg"),
	//	device->loadTextureFromFile(
	//		modification.getPath() + "skies/sky_lf.jpg"),
	//	device->loadTextureFromFile(
	//		modification.getPath() + "skies/sky_rt.jpg"),
	//	device->loadTextureFromFile(
	//		modification.getPath() + "skies/sky_fr.jpg"),
	//	device->loadTextureFromFile(
	//		modification.getPath() + "skies/sky_bk.jpg"), nullptr);

	return true;
}

void Graphics::update(float deltaTime)
{
	auto camera = scene->getActiveCamera();
	if (camera != nullptr)
	{
		auto rotation = camera->getRotation();
		//rotation.y -= 1.0f;
		camera->setRotation(rotation);

		auto position = camera->getPosition();
	}

	gui->update(deltaTime);
}

void Graphics::drawAll()
{
	device->beginScene();

	scene->drawAll();

	gui->drawAll();

	device->endScene();
}

gui::Gui& Graphics::getGui()
{
	return *gui;
}

void Graphics::setTerrain(unsigned terrainSize,
	const std::vector<float>& heightMap, unsigned colorMapSize,
	const std::vector<gfx::Color>& colorMap,
	const std::vector<uint8_t>& grassMap)
{
	terrainNode = scene->addTerrain(terrainSize, heightMap, colorMapSize,
		colorMap);
}

} // namespace gfx
