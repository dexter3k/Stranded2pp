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
	gui(new gui::Gui(input, device.get()))
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

	scene->addCamera(nullptr, math::Vector3f(0.0f, 10.0f, 5.0f),
		math::Vector3f(-22.5f, 0.0f, 0.0f));
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

	//gui->addImage(device->loadTextureFromFile(modification.getPath() + "sys/gfx/wrenchItem.png", true), math::Recti(100, 100, 400, 400));
	//gui->addButton(device->loadTextureFromFile(modification.getPath() + "sys/gfx/bigbutton.bmp", true), device->loadTextureFromFile(modification.getPath() + "sys/gfx/bigbutton_over.bmp", true), math::Vector2i(50, 50));

	std::vector<float> heightMap(5 * 5);
	std::vector<gfx::Color> colorMap(5 * 5);
	scene->addTerrain(4, heightMap, colorMap,
		device->loadTextureFromFile(
			modification.getPath() + "sys/gfx/terraindirt.bmp"),
		device->loadTextureFromFile(
			modification.getPath() + "sys/gfx/terrainstructure.bmp"));

	return true;
}

void Graphics::update(float deltaTime)
{
	auto camera = scene->getActiveCamera();
	if (camera != nullptr)
	{
		auto rotation = camera->getRotation();
		//rotation.y += 5.0f;
		camera->setRotation(rotation);
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

} // namespace gfx
