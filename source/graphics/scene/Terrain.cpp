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
	colorMapTexture(nullptr),
	firstDetailTexture(firstDetailTexture),
	secondDetailTexture(secondDetailTexture),
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
	createColorMapTexture(colorMap);

	terrainMaterial.materialType = Material::DetailMap;
	terrainMaterial.textureLayers[0].texture = colorMapTexture;
	terrainMaterial.textureLayers[1].texture = firstDetailTexture;
	terrainMaterial.lighting = false;
	terrainMaterial.wireframe = false;
	terrainMaterial.backFaceCulling = false;
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

			vertex.textureCoords = math::Vector2f(1.0f - fx2, fz2);
			vertex.textureCoords2 = math::Vector2f(fx / 4.0f, fz / 4.0f);

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
	assert(colorMap.size() == terrainSize * terrainSize);

	device::Device* device = scene->getDevice();
	if (device == nullptr)
	{
		return;
	}

	Image image;
	image.create(math::Vector2u(terrainSize, terrainSize));

	for (unsigned x = 0; x < terrainSize; ++x)
	{
		for (unsigned y = 0; y < terrainSize; ++y)
		{
			image.setPixel(x, y, colorMap[x + y * terrainSize]);
		}
	}

	colorMapTexture = device->loadTextureFromImage("terrainColorMap", image);
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

} // namespace scene

} // namespace gfx
