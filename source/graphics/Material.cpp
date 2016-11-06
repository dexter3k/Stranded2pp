#include "Material.h"

#include <cassert>

namespace gfx
{

Material::TextureLayer::TextureLayer() :
	texture(nullptr),
	bilinearFilter(false),
	trilinearFilter(false),
	lodBias(0),
	textureMatrix()
{}

Material::TextureLayer::~TextureLayer()
{}

Material::TextureLayer& Material::TextureLayer::operator=(
	const TextureLayer& other)
{
	texture = other.texture;
	bilinearFilter = other.bilinearFilter;
	trilinearFilter = other.trilinearFilter;
	lodBias = other.lodBias;
	textureMatrix = other.textureMatrix;

	return *this;
}

bool Material::TextureLayer::operator==(const TextureLayer& other) const
{
	return !(operator!=(other));
}

bool Material::TextureLayer::operator!=(const TextureLayer& other) const
{
	return (
		texture != other.texture ||
		bilinearFilter != other.bilinearFilter ||
		trilinearFilter != other.trilinearFilter ||
		lodBias != other.lodBias ||
		textureMatrix != other.textureMatrix
	);
}

Material::Material() :
	materialType(Solid),
	colorMaterial(Diffuse),
	depthFunction(LessEqual),
	zWriteFineControl(OnlyNonTransparent),
	blendOperation(Add),
	blendFactor(0.0f),
	ambientColor(255, 255, 255, 255),
	diffuseColor(255, 255, 255, 255),
	emissiveColor(0, 0, 0, 0),
	specularColor(255, 255, 255, 255),
	shininess(0.0f),
	thickness(1.0f),
	textureLayers(),
	normalizeNormals(false),
	smoothShading(true),
	wireframe(false),
	lighting(false),
	zWriteEnabled(true),
	backFaceCulling(true),
	frontFaceCulling(false),
	fogEnabled(false),
	useMipMaps(false)
{
	for (unsigned i = 0; i < maxTexturesPerMaterial; ++i)
	{
		textureLayers[i] = TextureLayer();
	}
}

Material::~Material()
{}

Material& Material::operator=(const Material& other)
{
	if (this == &other)
	{
		return *this;
	}

	materialType = other.materialType;
	colorMaterial = other.colorMaterial;
	depthFunction = other.depthFunction;
	zWriteFineControl = other.zWriteFineControl;
	blendOperation = other.blendOperation;

	blendFactor = other.blendFactor;

	ambientColor = other.ambientColor;
	diffuseColor = other.diffuseColor;
	emissiveColor = other.emissiveColor;
	specularColor = other.specularColor;
	shininess = other.shininess;

	thickness = other.thickness;

	for (unsigned i = 0; i < maxTexturesPerMaterial; ++i)
	{
		textureLayers[i] = other.textureLayers[i];
	}

	normalizeNormals = other.normalizeNormals;
	smoothShading = other.smoothShading;
	wireframe = other.wireframe;
	lighting = other.lighting;
	zWriteEnabled = other.zWriteEnabled;
	backFaceCulling = other.backFaceCulling;
	frontFaceCulling = other.frontFaceCulling;
	fogEnabled = other.fogEnabled;
	useMipMaps = other.useMipMaps;

	return *this;
}

bool Material::operator==(const Material& other) const
{
	if (this == &other)
	{
		return true;
	}

	return !(operator!=(other));
}

bool Material::operator!=(const Material& other) const
{
	bool isDifferent = (
		materialType != other.materialType ||
		colorMaterial != other.colorMaterial ||
		depthFunction != other.depthFunction ||
		zWriteFineControl != other.zWriteFineControl ||
		blendOperation != other.blendOperation ||
		blendFactor != other.blendFactor ||
		ambientColor != other.ambientColor ||
		diffuseColor != other.diffuseColor ||
		emissiveColor != other.emissiveColor ||
		specularColor != other.specularColor ||
		shininess != other.shininess ||
		thickness != other.thickness ||
		normalizeNormals != other.normalizeNormals ||
		smoothShading != other.smoothShading ||
		wireframe != other.wireframe ||
		lighting != other.lighting ||
		zWriteEnabled != other.zWriteEnabled ||
		backFaceCulling != other.backFaceCulling ||
		frontFaceCulling != other.frontFaceCulling ||
		fogEnabled != other.fogEnabled ||
		useMipMaps != other.useMipMaps
	);

	for (unsigned i = 0; i < maxTexturesPerMaterial; ++i)
	{
		isDifferent |= textureLayers[i] != other.textureLayers[i];
	}

	return isDifferent;
}

bool Material::isTransparent() const
{
	if (materialType == SemiTransparent ||
		materialType == SharpTransparent)
	{
		return true;
	}

	if (blendOperation != NoBlend && blendFactor != 0.0f)
	{
		// Do i really need this check?
		assert(false);
	}

	return false;
}

} // namespace gfxs
