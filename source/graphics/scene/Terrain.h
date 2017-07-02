#pragma once

#include <vector>

#include "Node.h"

#include "../Color.h"
#include "../MeshBuffer.h"
#include "../Texture.h"
#include "../Material.h"
#include "../Vertex3D.h"

#include "common/math/Vector2.h"

namespace gfx
{

namespace scene
{

class Terrain : public Node
{
	typedef Node super;
public:
	Terrain(unsigned terrainSize, const std::vector<float>& heightMap,
		unsigned colorMapSize, const std::vector<gfx::Color>& colorMap,
		Node* parent, Scene* scene, int id = -1,
		const math::Vector2f& scale = math::Vector2f(0.0f, 0.0f));
	~Terrain();

	void onRegisterNode() override;

	void render() override;
private:
	void createTerrain(const std::vector<float>& heightMap);
	void createColorMapTexture(unsigned colorMapSize,
		const std::vector<gfx::Color>& colorMap);
	void createDetailTexture();

	void preRenderIndicesRecalculation();
private:
	unsigned terrainSize;

	Texture* colorMapTexture;
	//Texture* detailTexture;

	Material terrainMaterial;

	// Buffer with original terrain data
	MeshBuffer dataBuffer;

	// Buffer with modified terrain (i.e. with LOD applied)
	MeshBuffer renderBuffer;
};

} // namespace scene

} // namespace gfx
