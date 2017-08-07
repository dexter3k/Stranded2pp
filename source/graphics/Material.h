#pragma once

#include <cstdint>

#include "Color.h"
#include "Texture.h"

#include "math/Matrix4.h"

namespace gfx
{

class Material
{
public:
	enum Type
	{
		Solid,
		LightMap,
		DoubleLightMap,
		LightMapLighting,
		DoubleLightMapLighting,
		DetailMap,
		ColorDetailMap,
		Reflection,
		SemiTransparent,
		SharpTransparent
	};

	enum ColorMaterial
	{
		NoColorMaterial,
		Diffuse,
		Ambient,
		Specular,
		Emissive,
		DiffuseAndAmbient
	};

	enum DepthFunction
	{
		Disabled,
		LessEqual,
		Equal,
		Less,
		NotEqual,
		GreaterEqual,
		Greater,
		Always,
		Never
	};

	enum ZWriteFineControl
	{
		OnlyNonTransparent,
		ZBufferFlag
	};

	enum BlendOperation
	{
		NoBlend,
		Add,
		Subtract,
		RevSubtract,
		Min,
		Max,
		MinFactor,
		MaxFactor,
		MinAlpha,
		MaxAlpha
	};

	class TextureLayer
	{
	public:
		Texture* texture;

		bool bilinearFilter : 1;
		bool trilinearFilter : 1;

		uint8_t lodBias;

		math::Matrix4 textureMatrix;

		TextureLayer();
		~TextureLayer();

		TextureLayer& operator=(const TextureLayer& other);

		bool operator==(const TextureLayer& other) const;
		bool operator!=(const TextureLayer& other) const;
	};
public:
	const static unsigned maxTexturesPerMaterial = 2;
public:
	Type materialType;
	ColorMaterial colorMaterial;
	DepthFunction depthFunction;
	ZWriteFineControl zWriteFineControl;
	BlendOperation blendOperation;

	float blendFactor;

	Color ambientColor;
	Color diffuseColor;
	Color emissiveColor;
	Color specularColor;
	float shininess;

	float thickness;

	TextureLayer textureLayers[maxTexturesPerMaterial];

	bool normalizeNormals : 1;
	bool smoothShading : 1;
	bool wireframe : 1;
	bool lighting : 1;
	bool zWriteEnabled : 1;
	bool backFaceCulling : 1;
	bool frontFaceCulling : 1;
	bool fogEnabled : 1;
	bool useMipMaps : 1;

	Material();
	~Material();

	Material& operator=(const Material& other);

	bool operator==(const Material& other) const;
	bool operator!=(const Material& other) const;

	bool isTransparent() const;
};

} // namespace gfx
