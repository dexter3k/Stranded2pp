#pragma once

namespace gfx
{

namespace scene
{

class MeshBuffer;

class Mesh
{
public:
	Mesh();
	virtual ~Mesh();

	virtual MeshBuffer* getMeshBuffer(unsigned id) const = 0;
};

} // namespace scene

} // namespace gfx
