#include "Scene.h"

#include "Camera.h"
#include "Skybox.h"
#include "Terrain.h"

#include "../Color.h"
#include "../Material.h"
#include "../device/Device.h"

namespace gfx
{

namespace scene
{

Scene::Scene(Graphics& graphics, device::Device* device) :
	RootNode(nullptr, this),
	graphics(graphics),
	device(device),
	activeCamera(nullptr),
	cameraWorldPosition(0.0f, 0.0f, 0.0f),
	sceneNodes(),
	animationDeltaTimer(),
	currentRenderPass(RenderPassNone),
	skyboxes(),
	solidObjects()
{}

Scene::~Scene()
{
	clearScene();
}

void Scene::drawAll()
{
	// TODO

	if (device == nullptr)
	{
		return;
	}

	device->setMaterial(Material());
	device->resetTransforms();

	float animationDeltaTime = animationDeltaTimer.restart();

	RootNode::onAnimate(animationDeltaTime);

	cameraWorldPosition = math::Vector3f(0.0f, 0.0f, 0.0f);
	if (activeCamera != nullptr)
	{
		activeCamera->render();
		cameraWorldPosition = activeCamera->getAbsolutePosition();
	}

	RootNode::onRegisterNode();

	// Render skyboxes
	{
		currentRenderPass = RenderPassSkybox;

		for (auto&& skybox : skyboxes)
		{
			skybox->render();
		}

		skyboxes.clear();
	}

	// Render solid objects
	{
		currentRenderPass = RenderPassSolid;

		for (auto&& object : solidObjects)
		{
			object->render();
		}

		solidObjects.clear();
	}

	currentRenderPass = RenderPassNone;
}

device::Device* Scene::getDevice()
{
	return device;
}

Node* Scene::addWaterSurface(Mesh* mesh, float waveHeight, float waveSpeed,
	float waveLength, Node* parent, int id, const math::Vector3f& position,
	const math::Vector3f& rotation, const math::Vector3f& scale)
{
	// TODO
	return nullptr;
}

Camera* Scene::addCamera(Node* parent, const math::Vector3f& position,
	const math::Vector3f& rotation, int id, bool makeActive)
{
	if (parent == nullptr)
	{
		parent = this;
	}

	Camera* camera = new Camera(parent, this, id, position, rotation);
	sceneNodes.push_back(camera);

	if (makeActive)
	{
		setActiveCamera(camera);
	}

	return camera;
}

Node* Scene::addSkybox(Texture* top, Texture* bottom, Texture* left,
	Texture* right, Texture* front, Texture* back, Node* parent, int id)
{
	if (parent == nullptr)
	{
		parent = this;
	}

	Node* skybox = new Skybox(top, bottom, left, right, front, back, parent,
		this, id);
	sceneNodes.push_back(skybox);

	return skybox;
}

Node* Scene::addTerrain(unsigned terrainSize,
	const std::vector<float>& heightMap,
	const std::vector<gfx::Color>& colorMap, Texture* firstDetailTexture,
	Texture* secondDetailTexture, Node* parent, int id,
	const math::Vector3f& position, const math::Vector3f& rotation,
	const math::Vector3f& scale)
{
	if (parent == nullptr)
	{
		parent = this;
	}

	Node* terrain = new Terrain(terrainSize, heightMap, colorMap,
		firstDetailTexture, secondDetailTexture, parent, this, id, position, rotation,
		scale);

	sceneNodes.push_back(terrain);

	return terrain;
}

Node* Scene::addEmptyNode(Node* parent, int id)
{
	if (parent == nullptr)
	{
		parent = this;
	}

	Node* emptyNode = new Node(parent, this, id);

	return emptyNode;
}

Node* Scene::getRootNode()
{
	return this;
}

Camera* Scene::getActiveCamera() const
{
	return activeCamera;
}

void Scene::setActiveCamera(Camera* camera)
{
	activeCamera = camera;
}

bool Scene::registerNodeForRendering(Node* node, SceneNodeRenderPass pass)
{
	if (node == nullptr)
	{
		return false;
	}

	switch (pass)
	{
		case RenderPassSkybox:
		{
			skyboxes.push_back(node);

			break;
		}
		default:
		{
			break;
		}
	}

	return true;
}

void Scene::clearScene()
{
	for (auto&& node : sceneNodes)
	{
		delete node;
	}

	sceneNodes.clear();
}

Scene::SceneNodeRenderPass Scene::getCurrentRenderPass() const
{
	return currentRenderPass;
}

bool Scene::isCulled(const Node* node) const
{
	// TODO
	return false;
}

void Scene::render()
{
	// Nothing to do here
}

} // namespace scene

} // namespace gfx
