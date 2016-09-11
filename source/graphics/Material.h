#pragma once

#include "Color.h"

namespace gfx
{

const unsigned MaterialMaxTextures = 4;

class Material
{
public:
	Color ambientColor;
	Color diffuseColor;
	Color emissiveColor;
	Color specularColor;

	float shininess;
	float thickness;

	bool wireframe;
	bool lighting;
	bool zWriteEnabled;
	bool backFaceCulling;
	bool frontFaceCulling;
	bool fogEnabled;

	Material();

	~Material();
};

} // namespace gfx
