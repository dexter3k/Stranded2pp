#pragma once

#include <memory>
#include <string>
#include <vector>
#include <map>

#include "LoadingScreen.h"
#include "gui/Gui.h"
#include "input/Event.h"
#include "mod/Lightcycle.h"
#include "scene/Scene.h"

class Modification;
class Object;

namespace gfx
{

	class Color;
	class Model;

namespace device
{
	class Device;
}

namespace scene
{	
	class InfinitePlane;
	class Skybox;
	class Terrain;
	class Entity;
}


class Texture;

class Graphics
{
public:
	Graphics(Modification const & modification);
	~Graphics();

	bool processEvent(Event event);
	void update(double deltaTime);

	void drawAll();

	gui::Gui & getGui() { return gui; };
	LoadingScreen & getLoadingScreen() { return loadingScreen; };

	void setSkybox(std::string const & name);
	void setTerrain(unsigned terrainSize, std::vector<float> const & heightMap,
		unsigned colorMapSize, std::vector<gfx::Color> const & colorMap,
		std::vector<uint8_t> const & grassMap);

	scene::Entity * loadObjectModelAndAddToScene(Object * object);
	Model * loadObjectModel(std::string const & name);
private:
	bool init();

	void setWaterLevel(float level);
	void setGroundLevel(float level);
	void setGroundColor(const Color& color);

	bool preloadTextures();
private:
	enum SkyboxSides
	{
		SkyboxUp = 0,
		SkyboxDown = 1,
		SkyboxLeft = 2,
		SkyboxRight = 3,
		SkyboxFront = 4,
		SkyboxBack = 5
	};

	static const std::string skyboxBasePath;
	static const std::vector<std::string> skyboxPostfixes;
	static const std::vector<std::string> preloadList;
private:
	std::unique_ptr<device::Device> device;

	gui::Gui gui;
	scene::Scene scene;

	std::string basePath;

	std::vector<std::string> preloadedTextures;

	scene::Terrain* terrainNode;

	Texture * currentSkyboxTextures[6];
	scene::Skybox * currentSkyboxNode;
	std::string currentSkyboxName;

	scene::InfinitePlane * waterPlane;
	scene::InfinitePlane * groundPlane;

	LoadingScreen loadingScreen;

	std::array<gfx::Color, 24> lightcycle;

	std::map<std::string, Model *>      models;
	std::map<unsigned, scene::Entity *> entities;
};

} // namespace gfx
