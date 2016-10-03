#include "Terrain.h"

#include <iostream>

#include "Scene.h"

namespace gfx
{

namespace scene
{

Terrain::Terrain(unsigned terrainSize, const std::vector<float>& heightMap,
		const std::vector<gfx::Color>& colorMap, Texture* firstDetailTexture,
		Texture* secondDetailTexture, Node* parent, Scene* scene, int id,
		const math::Vector3f& position, const math::Vector3f& rotation,
		const math::Vector3f& scale) :
	super(parent, scene, id, position, rotation, scale),
	terrainSize(terrainSize),
	firstDetailTexture(firstDetailTexture),
	secondDetailTexture(secondDetailTexture),
	terrainMaterial(),
	vertices((terrainSize + 1) * (terrainSize + 1)),
	indices(6 * (terrainSize * terrainSize))
{
	assert(terrainSize < 16);

	std::cout << terrainSize << std::endl;
	std::cout << heightMap.size() << std::endl;
	assert(heightMap.size() >= ((terrainSize + 1) * (terrainSize + 1)));
	assert(colorMap.size() >= ((terrainSize + 1) * (terrainSize + 1)));
}

Terrain::~Terrain()
{}

void Terrain::onRegisterNode()
{
	if (isVisible)
	{
		scene->registerNodeForRendering(this, Scene::RenderPassSolid);
	}

	super::onRegisterNode();
}

void Terrain::render()
{
	std::cout << "Render!" << std::endl;
}

void Terrain::createTerrain(const std::vector<float>& heightMap,
	const std::vector<gfx::Color>& colorMap)
{

}

} // namespace scene

} // namespace gfx
