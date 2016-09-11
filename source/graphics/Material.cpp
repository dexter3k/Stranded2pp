#include "Material.h"

namespace gfx
{

Material::Material() :
	ambientColor(255, 255, 255, 255),
	diffuseColor(255, 255, 255, 255),
	emissiveColor(0, 0, 0, 0),
	specularColor(255, 255, 255, 255),
	shininess(0.0f),
	thickness(1.0f),
	wireframe(false),
	lighting(true),
	zWriteEnabled(true),
	backFaceCulling(true),
	frontFaceCulling(false),
	fogEnabled(false)
{}

Material::~Material()
{}

} // namespace gfxs
