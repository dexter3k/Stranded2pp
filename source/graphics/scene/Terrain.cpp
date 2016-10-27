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
		unsigned colorMapSize, const std::vector<gfx::Color>& colorMap,
		Node* parent, Scene* scene, int id, const math::Vector2f& scale) :
	super(parent, scene, id, math::Vector3f(0.0f, 0.0f, 0.0f),
		math::Vector3f(0.0f, 0.0f, 0.0f), math::Vector3f(0.0f, 0.0f, 0.0f)),
	terrainSize(terrainSize),
	colorMapTexture(nullptr),
	detailTexture(nullptr),
	terrainMaterial(),
	dataBuffer(Vertex3D::DoubleTCoords,
		terrainSize < 256 ? Index16Bit : Index32Bit),
	renderBuffer(Vertex3D::DoubleTCoords,
		terrainSize < 256 ? Index16Bit : Index32Bit)
{
	dataBuffer.setVertexBufferMappingHint(HardwareMappingNever);
	dataBuffer.setIndexBufferMappingHint(HardwareMappingNever);

	renderBuffer.setVertexBufferMappingHint(HardwareMappingStatic);
	renderBuffer.setIndexBufferMappingHint(HardwareMappingDynamic);

	createTerrain(heightMap);
	createColorMapTexture(colorMapSize, colorMap);
	//createDetailTexture();

	terrainMaterial.materialType = Material::DetailMap;
	terrainMaterial.textureLayers[0].texture = colorMapTexture;
	terrainMaterial.textureLayers[1].texture = detailTexture;
	terrainMaterial.lighting = false;
	terrainMaterial.wireframe = false;
}

Terrain::~Terrain()
{
	if (colorMapTexture != nullptr)
	{
		device::Device* device = scene->getDevice();
		if (device != nullptr)
		{
			device->releaseTexture("terrainColorMap");
			colorMapTexture = nullptr;
		}
	}
}

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

	math::Matrix4 transform;
	transform.setScale(math::Vector3f(1.0f, 20.0f, 1.0f));
	transform.setTranslation(math::Vector3f(
		-static_cast<float>(terrainSize) / 2.0f, 0.0f,
		-static_cast<float>(terrainSize) / 2.0f));
	device->setTransform(device::Device::Model, transform);
	device->setMaterial(renderBuffer.getMaterial());
	device->setMaterial(terrainMaterial);

	device->drawMeshBuffer(&renderBuffer);
}

void Terrain::createTerrain(const std::vector<float>& heightMap)
{
	assert(heightMap.size() == ((terrainSize + 1) * (terrainSize + 1)));

	unsigned heightMapSize = terrainSize + 1;
	assert(heightMap.size() == heightMapSize * heightMapSize);

	unsigned dataSize = heightMapSize * heightMapSize;
	dataBuffer.getVertexBuffer().setUsed(dataSize);

	float tdSize = 1.0f / static_cast<float>(terrainSize);
	float fx = 0.0f;
	float fz = 0.0f;
	float fx2 = 0.0f;
	float fz2 = 0.0f;
	unsigned index = 0;

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

			vertex.textureCoords = math::Vector2f(fx2, 1 - fz2);
			vertex.textureCoords2 = math::Vector2f(fx / 2.0f, fz / 2.0f);

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

void Terrain::createColorMapTexture(unsigned colorMapSize,
	const std::vector<gfx::Color>& colorMap)
{
	assert(colorMap.size() == colorMapSize * colorMapSize);

	device::Device* device = scene->getDevice();
	if (device == nullptr)
	{
		return;
	}

	Image image;
	image.create(math::Vector2u(colorMapSize, colorMapSize));

	for (unsigned x = 0; x < colorMapSize; ++x)
	{
		for (unsigned y = 0; y < colorMapSize; ++y)
		{
			image.setPixel(x, y, colorMap[x + y * colorMapSize]);
		}
	}

	colorMapTexture = device->loadTextureFromImage("terrainColorMap", image);
}

void Terrain::createDetailTexture()
{
	device::Device* device = scene->getDevice();
	if (device != nullptr)
	{
		return;
	}

	//detailTexture = device->loadTextureFromFile();
}

void Terrain::preRenderIndicesRecalculation()
{
	renderBuffer.getIndexBuffer().clear();

	auto& buffer = renderBuffer.getIndexBuffer();
	for (unsigned x = 0; x < terrainSize; ++x)
	{
		for (unsigned z = 0; z < terrainSize; ++z)
		{
			unsigned index = x + z * (terrainSize + 1);

			if ((x % 2 == 0 && z % 2 == 0) ||
				(x % 2 == 1 && z % 2 == 1))
			{
				// First triangle
				buffer.pushBack(index);
				buffer.pushBack(index + terrainSize + 1 + 1);
				buffer.pushBack(index + 1);

				// Second triangle
				buffer.pushBack(index);
				buffer.pushBack(index + terrainSize + 1);
				buffer.pushBack(index + terrainSize + 1 + 1);
			}
			else
			{
				// First triangle
				buffer.pushBack(index);
				buffer.pushBack(index + terrainSize + 1);
				buffer.pushBack(index + 1);

				// Second triangle
				buffer.pushBack(index + 1);
				buffer.pushBack(index + terrainSize + 1);
				buffer.pushBack(index + terrainSize + 1 + 1);
			}
		}
	}
}

} // namespace scene

} // namespace gfx
