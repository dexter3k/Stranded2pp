#pragma once

namespace gfx
{

class Graphics;

namespace scene
{

class Scene
{
	friend class Graphics;
public:
	Scene(Graphics& graphics);
	~Scene();

	void drawAll();
private:
	Graphics& graphics;
};

} // namespace scene

} // namespace gfx
