#include "Entity.h"

namespace gfx
{

namespace scene
{

Entity::Entity(Scene & scene, Node * parent, Model *,
		math::Vector3f position, math::Vector3f rotation, math::Vector3f scale) :
	super(scene, parent, position, rotation, scale)
{}

} // namespace scene

} // namespace gfx
