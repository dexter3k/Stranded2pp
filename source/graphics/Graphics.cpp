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

	scene->addCamera(nullptr, math::Vector3f(0.0f, 50.f, 50.0f),
		math::Vector3f(45.0f, 0.0f, 0.0f));
	
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

	std::vector<float> heightMap(129 * 129, 0.0f);
	for (unsigned x = 0; x < 129; ++x)
	{
		for (unsigned y = 0; y < 129; ++y)
		{
			heightMap[x + y * 129] = std::sin(5.0f * static_cast<float>(x / 129.0f)) * std::cos(5.0f * static_cast<float>(y / 129.0f)) * 3.0f;
		}
	}
	std::vector<gfx::Color> colorMap(128 * 128, Color(0, 255, 0));
	
	colorMap[0] = Color(255, 0, 0);
	//for (unsigned i = 0; i < 128; ++i)
	//{
	//	colorMap[i + i * 128] = Color(255, 0, 0);
	//}
	for (unsigned x = 0; x < 128; ++x)
	{
		for (unsigned y = 0; y < 128; ++y)
		{
			colorMap[x + y * 128].setRed(255 * (std::sin(5.0f * static_cast<float>(x / 128.0f)) * std::cos(5.0f * static_cast<float>(y / 128.0f)) * 3.0f));
		}
	}
	scene->addTerrain(128, heightMap, colorMap,
		device->loadTextureFromFile(
			modification.getPath() + "sys/gfx/terraindirt.bmp"),
			//modification.getPath() + "sys/gfx/tutor.bmp"),
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

} // namespace gfx
