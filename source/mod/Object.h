#pragma once

#include <string>

#include "graphics/Color.h"
#include "math/Vector3.h"

namespace engine {
	class ObjectBuilder;
}

namespace mod
{

class Object
{
	friend class engine::ObjectBuilder;
public:
	Object() = default;
private:
	unsigned id;

	std::string name;
	
	std::string iconName;
	//Icon icon;
	
	std::string modelName;
	//Model model;
	math::Vector3f size;
	gfx::Color color;

	int fx;
	int autofade;
	float alpha;
	float shininess;

	std::string detailTextureName;

	int collisionMode;
	int material;

	float health;
	float healthChange;
	float swaySpeed;
	float swayPower;
	int maxweight;
	int gt;

	float state1;
	float state2;
	float state3;
	float state4;

	float searchRatio;

	bool active;
	std::string behaviour;

	std::string spawn;

	std::string script;
	std::string scriptOverride;

	int align;
	int afc;

	std::string description;

	bool inEditor;

	int growtime;

	std::string group;
};

} // namespace mod
