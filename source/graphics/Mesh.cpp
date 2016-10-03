#include "Mesh.h"

#include <cassert>

#include "MeshBuffer.h"

namespace gfx
{

Mesh::Mesh() :
	meshBuffers()
{}

Mesh::~Mesh()
{}

void Mesh::clear()
{
	meshBuffers.clear();
}

unsigned Mesh::getMeshBufferCount() const
{
	return meshBuffers.size();
}

MeshBuffer* Mesh::getMeshBuffer(unsigned id) const
{
	assert(id < meshBuffers.size());

	return meshBuffers[id];
}

void Mesh::addMeshBuffer(MeshBuffer* meshBuffer)
{
	assert(meshBuffer != nullptr);

	meshBuffers.push_back(meshBuffer);
}

void Mesh::setDirty()
{
	for (auto&& meshBuffer : meshBuffers)
	{
		//meshBuffer->setDirty();
	}
}

} // namespace gfx
