#pragma once

#include "Node.h"

namespace gfx
{

class Model;

namespace scene
{

class Entity : public Node
{
	typedef Node super;
public:
	Entity(Scene & scene, Node * parent, Model * model,
		math::Vector3f position, math::Vector3f rotation, math::Vector3f scale);
};

} // namespace scene

} // namespace gfx
