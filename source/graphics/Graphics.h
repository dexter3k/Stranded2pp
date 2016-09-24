#pragma once

#include <memory>

class Input;
class Modification;

namespace gfx
{

namespace device
{

	class Device;

} // namespace device


namespace scene
{

	class Scene;

} // namespace scene

class Texture;

class Graphics
{
public:
	Graphics(Input& input);
	~Graphics();

	bool init(const Modification& modification);
	void update(float deltaTime);

	void drawAll();
private:
	Input& input;

	std::shared_ptr<device::Device> device;
	std::shared_ptr<scene::Scene> scene;
};

} // namespace gfx
