#pragma once

#include "Node.h"

namespace gfx
{

namespace scene
{

class Mesh;

class MeshNode : public Node
{
	typedef Node super;
public:
	MeshNode(Node* parent, Scene* scene, int id = -1,
		const math::Vector3f& position = math::Vector3f(0.0f),
		const math::Vector3f& rotation = math::Vector3f(0.0f),
		const math::Vector3f& scale = math::Vector3f(1.0f));
	virtual ~MeshNode();

	virtual Mesh* getMesh() = 0;
	virtual void setMesh(Mesh* mesh) = 0;
};

} // namespace scene

} // namespace gfx
