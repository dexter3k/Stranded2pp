#include "Graphics.h"

#include "device/Device.h"
#include "device/OpenGLDevice.h"
#include "scene/Scene.h"

#include "common/Modification.h"
#include "input/Input.h"

#include "scene/Camera.h"
#include "scene/InfinitePlane.h"
#include "scene/Skybox.h"
#include "scene/Terrain.h"

#include "gui/Gui.h"


namespace gfx
{

const std::string Graphics::skyboxBasePath = "skies/";

const std::vector<std::string> Graphics::skyboxPostfixes = {
	"_up.jpg",
	"_dn.jpg",
	"_lf.jpg",
	"_rt.jpg",
	"_fr.jpg",
	"_bk.jpg"
};

const std::vector<std::string> Graphics::preloadList = {
	"sys/gfx/bigbutton.bmp",
	"sys/gfx/bigbutton_over.bmp",
	"sys/gfx/iconbutton.bmp",
	"sys/gfx/iconbutton_over.bmp",
	"sys/gfx/check.bmp",
	"sys/gfx/check_over.bmp",
	"sys/gfx/check_sel.bmp",
	"sys/gfx/opt.bmp",
	"sys/gfx/opt_over.bmp",
	"sys/gfx/opt_sel.bmp",
	"sys/gfx/slider.bmp",
	"sys/gfx/slider_over.bmp",
	"sys/gfx/slider_sel.bmp",
	"sys/gfx/slider_sec.bmp",
	"sys/gfx/input_left.bmp",
	"sys/gfx/input_left_over.bmp",
	"sys/gfx/input_middle.bmp",
	"sys/gfx/input_middle_over.bmp",
	"sys/gfx/input_right.bmp",
	"sys/gfx/input_right_over.bmp",
	"sys/gfx/scroll.bmp",
	"sys/gfx/scroll_over.bmp",
	"sys/gfx/scroll_bar_top.bmp",
	"sys/gfx/scroll_bar_middle.bmp",
	"sys/gfx/scroll_bar_bottom.bmp",
	"sys/gfx/edscrollspace.bmp",
	"sys/gfx/icons.bmp",
	"sys/gfx/defaulticon.bmp",
	"sys/gfx/border_corn.bmp",
	"sys/gfx/border_hori.bmp",
	"sys/gfx/border_vert.bmp",
	"sys/gfx/cursor.bmp",
	"sys/gfx/cursor_height.bmp",
	"sys/gfx/cursor_move.bmp",
	"sys/gfx/cursor_paint.bmp",
	"sys/gfx/cursor_rotate.bmp",
	"sys/gfx/cursor_text.bmp",
	"sys/gfx/cursor_crosshair.bmp",
	"sys/gfx/woodback.bmp",
	"sys/gfx/woodback_dark.bmp",
	"sys/gfx/paperback.bmp",
	"sys/gfx/progress_small.bmp",
	"sys/gfx/progress_hunger.bmp",
	"sys/gfx/progress_thirst.bmp",
	"sys/gfx/progress_exhaustion.bmp",
	"sys/gfx/if_barback.bmp",
	"sys/gfx/if_itemback.bmp",
	"sys/gfx/if_itemshade.bmp",
	"sys/gfx/if_values.bmp",
	"sys/gfx/if_weapon.bmp",
	"sys/gfx/if_compass.bmp",
	"sys/gfx/state.bmp",
	"sys/gfx/states.bmp",
	"sys/gfx/arrows.bmp",
	"sys/gfx/title.bmp",
	"sys/gfx/editor_x.bmp",
	"sys/gfx/editor_y.bmp",
	"sys/gfx/editor_z.bmp",
	"sys/gfx/editor_sel.bmp",
	"sys/gfx/tutor.bmp",
	"sys/gfx/terrainstructure.bmp",
	"sys/gfx/structure.bmp",
	"sys/gfx/terraindirt.bmp",
	"sys/gfx/rain_a.bmp",
	"sys/gfx/snow_a.bmp",
	"sys/gfx/logo.bmp",
	"gfx/grasspread_a.png",
	"gfx/water.jpg",
	"sprites/flare0_a.bmp",
	"sprites/flare1_a.bmp",
	"sprites/flare2_a.bmp",
	"sprites/bubbles0_a.bmp",
	"sprites/bubbles1_a.bmp",
	"sprites/roundwave0_a.bmp",
	"sprites/wave0_a.bmp",
	"sprites/smoke0_a.bmp",
	"sprites/smoke1_a.bmp",
	"sprites/spark0_a.bmp",
	"sprites/splatter0_a.bmp",
	"sprites/splatter1_a.bmp",
	"sprites/splatter2_a.bmp",
	"sprites/woodfrag0_a.bmp",
	"sprites/woodfrag1_a.bmp",
	"sprites/woodfrag2_a.bmp",
	"sprites/woodfrag3_a.bmp",
	"sprites/woodfrag4_a.bmp",
	"sprites/starflare_a.bmp",
	"sprites/puddle0_a.bmp",
	"sprites/shockwave_a.bmp",
	"sprites/splash0_a.bmp",
	"sprites/attack1_a.bmp",
	"sprites/attack2_a.bmp",
	"sprites/flames0_a.png",
	"sprites/moon_a.png",
};

Graphics::Graphics(Input& input) :
	input(input),
	device(new device::OpenGLDevice()),
	scene(new scene::Scene(*this, device.get())),
	gui(new gui::Gui(input, device.get())),
	terrainNode(nullptr),
	preloadedTextures(),
	basePath(""),
	currentSkyboxTextures(),
	currentSkyboxNode(nullptr),
	currentSkyboxName("sky"),
	waterPlane(nullptr),
	groundPlane(nullptr)
{}

Graphics::~Graphics()
{
	for (const auto& texture : preloadedTextures)
	{
		device->releaseTexture(texture);
	}

	preloadedTextures.clear();

	// Unload ground plane texture
	if (groundPlane != nullptr)
	{
		device->releaseTexture(basePath + "sys/gfx/terraindirt.bmp");
	}

	// Unload water plane texture
	if (waterPlane != nullptr)
	{
		device->releaseTexture(basePath + "gfx/water.jpg");
	}

	// Unload skybox textures
	for (unsigned i = 0; i < 6; ++i)
	{
		if (currentSkyboxTextures[i] != nullptr)
		{
			device->releaseTexture(
				basePath + skyboxBasePath + currentSkyboxName +
					skyboxPostfixes[i]);
		}
	}
}

bool Graphics::init(const Modification& modification)
{
	basePath = modification.getPath();

	if (!device->init())
	{
		return false;
	}

	if (!preloadTextures())
	{
		return false;
	}

	if (!scene->init(modification))
	{
		return false;
	}

	if (!gui->init(modification))
	{
		return false;
	}

	scene->addCamera(nullptr, math::Vector3f(0.0f, 10.0f, 30.0f),
		math::Vector3f(0.0f, 0.0f, 0.0f));

	waterPlane = scene->addInfinitePlane(
		device->grabTexture(basePath + "gfx/water.jpg"), Color(80, 255, 240),
		3.125f);
	{
		auto& material = waterPlane->getMaterial();
		material.depthFunction = Material::Always;
		material.zWriteEnabled = true;
		material.textureLayers[0].bilinearFilter = true;
		material.materialType = Material::Solid;
	}

	setWaterLevel(1.0f / 64.0f);

	groundPlane = scene->addInfinitePlane(
		device->grabTexture(basePath + "sys/gfx/terraindirt.bmp"),
		Color(255, 255, 255), 2.0f);
	{
		auto& material = groundPlane->getMaterial();
		material.depthFunction = Material::Disabled;
		material.zWriteEnabled = false;
		material.textureLayers[0].bilinearFilter = true;
		material.materialType = Material::ColorDetailMap;
	}

	groundPlane->drawAsSkybox(true);

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

void Graphics::setSkybox(const std::string& name)
{
	if (currentSkyboxNode != nullptr)
	{
		if (groundPlane != nullptr)
		{
			groundPlane->setParent(nullptr);
		}

		scene->removeNode(currentSkyboxNode);
		currentSkyboxNode = nullptr;
	}

	if (currentSkyboxName != name)
	{
		for (unsigned i = 0; i < 6; ++i)
		{
			if (currentSkyboxTextures[i] != nullptr)
			{
				device->releaseTexture(
					basePath + skyboxBasePath + currentSkyboxName +
						skyboxPostfixes[i]);
			}
		}

		currentSkyboxName = name;

		for (unsigned i = 0; i < 6; ++i)
		{
			currentSkyboxTextures[i] = device->loadTextureFromFile(
				basePath + skyboxBasePath + currentSkyboxName +
					skyboxPostfixes[i]);
		}
	}

	currentSkyboxNode = scene->addSkybox(
		currentSkyboxTextures[0],
		currentSkyboxTextures[1],
		currentSkyboxTextures[2],
		currentSkyboxTextures[3],
		currentSkyboxTextures[4],
		currentSkyboxTextures[5]);

	if (groundPlane != nullptr)
	{
		groundPlane->setParent(currentSkyboxNode);
	}
}

void Graphics::setTerrain(unsigned terrainSize,
	const std::vector<float>& heightMap, unsigned colorMapSize,
	const std::vector<gfx::Color>& colorMap,
	const std::vector<uint8_t>& grassMap)
{
	if (terrainNode != nullptr)
	{
		scene->removeNode(terrainNode);
		terrainNode = nullptr;
	}

	terrainNode = scene->addTerrain(terrainSize, heightMap, colorMapSize,
		colorMap);

	// TODO
	setGroundLevel(heightMap[0] * 50.0f - 25.0f);
	setGroundColor(colorMap[0]);
}

void Graphics::setWaterLevel(float level)
{
	if (waterPlane != nullptr)
	{
		waterPlane->setPosition(math::Vector3f(0.0f, level, 0.0f));
	}
}

void Graphics::setGroundLevel(float level)
{
	if (groundPlane != nullptr)
	{
		groundPlane->setPosition(math::Vector3f(0.0f, level, 0.0f));
	}
}

void Graphics::setGroundColor(const Color& color)
{
	if (groundPlane != nullptr)
	{
		groundPlane->setColor(color);
	}
}

bool Graphics::preloadTextures()
{
	for (const auto& filename : preloadList)
	{
		Texture* texture = device->loadTextureFromFile(basePath + filename,
			false, true);
		if (texture == nullptr)
		{
			return false;
		}

		preloadedTextures.push_back(basePath + filename);
	}

	for (unsigned i = 0; i < 6; ++i)
	{
		currentSkyboxTextures[i] = device->loadTextureFromFile(
			basePath + skyboxBasePath + currentSkyboxName + skyboxPostfixes[i]);
	}

	return true;
}

} // namespace gfx
