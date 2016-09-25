#pragma once

#include <list>

#include "Node.h"

#include "common/Timer.h"
#include "common/math/Vector3.h"

namespace gfx
{

class Color;
class Graphics;
class Texture;

namespace device
{
	class Device;
}

namespace scene
{

class Camera;
class Mesh;

class Scene : public Node
{
	typedef Node RootNode;
public:
	enum SceneNodeRenderPass
	{
		RenderPassNone,
		RenderPassCamera,
		RenderPassLight,
		RenderPassSkybox,
		RenderPassAutomatic,
		RenderPassSolid,
		RenderPassShadow,
		RenderPassTransparent,
		RenderPassTransparentEffect
	};
private:
	friend class gfx::Graphics;

	Scene(Graphics& graphics, device::Device* device);
public:
	~Scene();
public:

	// Main drawing method. Will draw all the objects contained in the scene
	void drawAll();

	/*
		Scene configuration
	*/

	Camera* getActiveCamera() const;
	void setActiveCamera(Camera* camera);

	const Color& getAmbientLightColor() const;
	void setAmbientLightColor(const Color& color);

	/*
		Node creation and management
	*/

	Node* getRootNode();

	// Clear scene graph and delete all nodes
	void clearScene();

	Node* addWaterSurface(Mesh* mesh, float waveHeight = 2.0f,
		float waveSpeed = 300.0f, float waveLength = 10.0f,
		Node* parent = nullptr, int id = -1,
		const math::Vector3f& position = math::Vector3f(0.0f, 0.0f, 0.0f),
		const math::Vector3f& rotation = math::Vector3f(0.0f, 0.0f, 0.0f),
		const math::Vector3f& scale = math::Vector3f(1.0f, 1.0f, 1.0f));

	Camera* addCamera(Node* parent = nullptr,
		const math::Vector3f& position = math::Vector3f(0.0f, 0.0f, 0.0f),
		const math::Vector3f& rotation = math::Vector3f(0.0f, 0.0f, 0.0f),
		int id = -1, bool makeActive = true);

	Node* addSkybox(Texture* top, Texture* bottom, Texture* left,
		Texture* right, Texture* front, Texture* back, Node* parent = nullptr,
		int id = -1);

	Node* addEmptyNode(Node* parent, int id = -1);

	/*
		Methods that are used mostly by nodes (rendering, etc)
	*/

	device::Device* getDevice();

	bool isCulled(const Node* node) const;

	bool registerNodeForRendering(Node* node,
		SceneNodeRenderPass pass = RenderPassAutomatic);

	SceneNodeRenderPass getCurrentRenderPass() const;

	/*
		Node overrides
	*/

	void render();
private:
	Graphics& graphics;
	device::Device* device;

	Camera* activeCamera;
	math::Vector3f cameraWorldPosition;

	std::list<Node*> sceneNodes;

	Timer animationDeltaTimer;

	SceneNodeRenderPass currentRenderPass;

	std::list<Node*> skyboxes;
	std::list<Node*> solidObjects;
};

} // namespace scene

} // namespace gfx
