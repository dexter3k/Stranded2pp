#pragma once

#include <vector>

namespace gfx
{

class MeshBuffer;

class Mesh
{
public:
	Mesh();
	~Mesh();

	void clear();

	unsigned getMeshBufferCount() const;

	MeshBuffer* getMeshBuffer(unsigned id) const;

	void addMeshBuffer(MeshBuffer* meshBuffer);

	void setDirty();
private:
	std::vector<gfx::MeshBuffer*> meshBuffers;
};

} // namespace gfx
