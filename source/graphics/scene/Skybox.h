#pragma once

#include <cstdint>

#include "Node.h"

#include "../Material.h"
#include "../Vertex3D.h"

namespace gfx
{

class Texture;

namespace scene
{

class Skybox : public Node
{
	typedef Node super;
public:
	Skybox(Texture* top, Texture* bottom, Texture* left, Texture* right,
		Texture* front, Texture* back, Node* parent, Scene* scene, int id = -1);
	~Skybox();

	void onRegisterNode() override;

	void render() override;
private:
	uint16_t indices[6];

	Vertex3D vertices[6 * 4];
	Material materials[6];
};

} // namespace scene

} // namespace gfx
