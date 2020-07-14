#pragma once

#include <array>
#include <string>

#include "graphics/Color.h"
#include "math/Vector3.h"
#include "mod/Materials.h"

namespace gfx {

class Model;

}

namespace mod
{

struct Object
{
	unsigned id;

	std::string name;
	
	std::string iconName;
	// Icon icon;
	
	std::string modelName;
	gfx::Model * model; // nullptr is not loaded

	math::Vector3f size = {1, 1, 1};
	gfx::Color color = {255, 255, 255};

	int fx;
	int autofade = 500;
	float alpha = 1.0f;
	float shininess;

	std::string detailTextureName;

	int collisionMode = 1;
	Material::Type material = Material::None;

	float health = 500.0f;
	float healthChange;
	float swaySpeed;
	float swayPower = 1.0f;
	int maxWeight = 100 * 1000;

	float state1;
	float state2;
	float state3;
	float state4;

	float searchRatio = 30.0f;

	bool active;
	std::string behaviour;

	std::string spawn;

	std::string script;
	std::string scriptOverride;

	int align;
	int afc;

	std::string description;

	bool inEditor = true;

	int growtime = 10;

	std::string group;
};

using Objects = std::array<Object, 1024+1>;

Objects loadObjects(std::string const & modPath);

} // namespace mod
