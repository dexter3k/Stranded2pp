#pragma once

#include <cstdint>

#include "Node.h"

#include "../Material.h"
#include "../Vertex3D.h"
#include "graphics/Color.h"

namespace gfx
{

class Texture;

namespace scene
{

class InfinitePlane : public Node
{
	typedef Node super;
public:
	InfinitePlane(Texture* texture, Node* parent, Scene* scene,
		const Color& planeColor = Color(255, 255, 255),
		float textureScale = 1.0f,
		const math::Vector3f& position = math::Vector3f(0.0f), int id = -1);
	~InfinitePlane();

	void setColor(const Color& color);

	void onRegisterNode() override;

	void render() override;
private:
	bool buildVertices();
private:
	uint16_t indices[6];
	Vertex3D vertices[4];
	Material material;

	Color color;
	float textureScale;
};

} // namespace scene

} // namespace gfx
