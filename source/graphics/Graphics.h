#pragma once

#include <memory>
#include <vector>
#include <string>

class Input;
class Modification;

namespace gfx
{

	class Color;

namespace gui
{
	class Gui;
}

namespace device
{

	class Device;

} // namespace device


namespace scene
{

	class Scene;
	class Skybox;
	class Terrain;

} // namespace scene

class Texture;

class Graphics
{
public:
	Graphics(Input& input);
	~Graphics();

	bool init(const Modification& modification);
	void update(float deltaTime);

	void drawAll();

	gui::Gui& getGui();

	void setSkybox(const std::string& name);
	void setTerrain(unsigned terrainSize, const std::vector<float>& heightMap,
		unsigned colorMapSize, const std::vector<gfx::Color>& colorMap,
		const std::vector<uint8_t>& grassMap);
private:
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
	Input& input;

	std::shared_ptr<device::Device> device;
	std::shared_ptr<scene::Scene> scene;
	std::shared_ptr<gui::Gui> gui;

	scene::Terrain* terrainNode;

	std::vector<std::string> preloadedTextures;

	std::string basePath;

	Texture* currentSkyboxTextures[6];
	scene::Skybox* currentSkyboxNode;
	std::string currentSkyboxName;
};

} // namespace gfx
