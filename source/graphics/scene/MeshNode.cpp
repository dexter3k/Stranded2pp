#include "MeshNode.h"

namespace gfx
{

namespace scene
{

MeshNode::MeshNode(Node* parent, Scene* scene, int id,
		const math::Vector3f& position, const math::Vector3f& rotation,
		const math::Vector3f& scale) :
	super(parent, scene, id, position, rotation, scale)
{}

MeshNode::~MeshNode()
{}

} // namespace scene

} // namespace gfx
