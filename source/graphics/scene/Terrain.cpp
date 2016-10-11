#include "Terrain.h"

#include <iostream>

#include "Scene.h"

#include "../IndexBuffer.h"
#include "../MeshBuffer.h"
#include "../VertexBuffer.h"
#include "../device/Device.h"

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
	dataBuffer(Vertex3D::DoubleTCoords,
		terrainSize < 256 ? Index16Bit : Index32Bit),
	renderBuffer(Vertex3D::DoubleTCoords,
		terrainSize < 256 ? Index16Bit : Index32Bit)
{
	assert(terrainSize < 16);

	std::cout << terrainSize << std::endl;
	std::cout << heightMap.size() << std::endl;

	dataBuffer.setVertexBufferMappingHint(HardwareMappingNever);
	dataBuffer.setIndexBufferMappingHint(HardwareMappingNever);

	renderBuffer.setVertexBufferMappingHint(HardwareMappingStatic);
	renderBuffer.setIndexBufferMappingHint(HardwareMappingDynamic);

	createTerrain(heightMap);
	createColorMapTexture(colorMap);

	terrainMaterial.textureLayers[0].texture = firstDetailTexture;
	terrainMaterial.lighting = false;
	terrainMaterial.wireframe = false;
	terrainMaterial.backFaceCulling = false;
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
	device::Device* device = scene->getDevice();
	Camera* camera = scene->getActiveCamera();

	if (camera == nullptr || device == nullptr)
	{
		return;
	}

	preRenderIndicesRecalculation();

	device->setTransform(device::Device::Model, math::Matrix4());
	device->setMaterial(renderBuffer.getMaterial());

	device->drawMeshBuffer(&renderBuffer);
}

void Terrain::createTerrain(const std::vector<float>& heightMap)
{
	assert(heightMap.size() == ((terrainSize + 1) * (terrainSize + 1)));

	unsigned heightMapSize = terrainSize + 1;
	for (unsigned x = 0; x < heightMapSize; ++x)
	{
		for (unsigned z = 0; z < heightMapSize; ++z)
		{
			std::cout << heightMap[x + heightMapSize * z] << " ";
		}
		std::cout << std::endl;
	}

	unsigned dataSize = heightMapSize * heightMapSize;
	dataBuffer.getVertexBuffer().setUsed(dataSize);

	float tdSize = 1.0f / static_cast<float>(terrainSize);
	float fx = 0.0f;
	float fz = 0.0f;
	float fx2 = 0.0f;
	float fz2 = 0.0f;
	unsigned index = 0;

	std::cout << "fx: " << fx << std::endl;
	std::cout << "test: " << 0.0f << std::endl;

	auto dataBufferVertices =
		static_cast<Vertex3D2TCoords*>(dataBuffer.getVertices());
	for (unsigned x = 0; x < heightMapSize; ++x)
	{
		fz = 0.0f;
		fz2 = 0.0f;
		for (unsigned z = 0; z < heightMapSize; ++z)
		{
			Vertex3D2TCoords& vertex = dataBufferVertices[index++];
			vertex.normal = math::Vector3f(0.0f, 1.0f, 0.0f);
			vertex.color = Color(255, 255, 255);
			vertex.position =
				math::Vector3f(fx, heightMap[x + heightMapSize * z], fz);

			vertex.textureCoords = math::Vector2f(1.0f - fx2, fz2);

			std::cout << fx << " " << heightMap[x + heightMapSize * z] << " " << fz << std::endl;

			++fz;
			fz2 += tdSize;
		}

		++fx;
		fx2 += tdSize;
	}

	renderBuffer.getMaterial() = terrainMaterial;
	renderBuffer.getVertexBuffer().setUsed(dataSize);

	auto renderBufferVertices =
		static_cast<Vertex3D2TCoords*>(renderBuffer.getVertices());
	for (unsigned i = 0; i < dataSize; ++i)
	{
		renderBufferVertices[i] = dataBufferVertices[i];
	}
}

void Terrain::createColorMapTexture(const std::vector<gfx::Color>& colorMap)
{
	
}

void Terrain::preRenderIndicesRecalculation()
{
	unsigned vertexCount = (terrainSize + 1) * (terrainSize + 1);

	renderBuffer.getIndexBuffer().clear();

	auto& buffer = renderBuffer.getIndexBuffer();

	for (unsigned x = 0; x < terrainSize; ++x)
	{
		for (unsigned z = 0; z < terrainSize; ++z)
		{
			unsigned index = x + z * (terrainSize + 1);

			// First triangle
			buffer.pushBack(index);
			buffer.pushBack(index + terrainSize + 1);
			buffer.pushBack(index + 1);

			// Second triangle
			buffer.pushBack(index + 1);
			buffer.pushBack(index + terrainSize + 1);
			buffer.pushBack(index + terrainSize + 1 + 1);

			std::cout << index << std::endl;
		}
	}
}

} // namespace scene

} // namespace gfx
