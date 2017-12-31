#include "Scene.h"

#include "Camera.h"
#include "InfinitePlane.h"
#include "Skybox.h"
#include "Terrain.h"

#include "../Color.h"
#include "../Material.h"
#include "../device/Device.h"

#include "../VertexBuffer.h"
#include "../IndexBuffer.h"

#include "common/Modification.h"

namespace gfx
{

namespace scene
{

Scene::Scene(device::Device & device, Modification const & modification) :
	RootNode(*this),
	device(device),
	activeCamera(nullptr),
	cameraWorldPosition(0.0f, 0.0f, 0.0f),
	sceneNodes(),
	animationDeltaTimer(),
	currentRenderPass(RenderPassNone),
	skyboxes(),
	solidObjects(),
	modPath(modification.getPath())
{}

Scene::~Scene()
{
	clearScene();
}

void Scene::drawAll()
{
	// TODO

	device.setMaterial(Material());
	device.resetTransforms();

	float const animationDeltaTime = animationDeltaTimer.restart();

	RootNode::onAnimate(animationDeltaTime);

	cameraWorldPosition = math::Vector3f(0.0f, 0.0f, 0.0f);
	if (activeCamera != nullptr) {
		activeCamera->render();
		cameraWorldPosition = activeCamera->getAbsolutePosition();
	}

	RootNode::onRegisterNode();

	// Render skyboxes
	{
		currentRenderPass = RenderPassSkybox;

		for (auto & skybox : skyboxes) {
			skybox->render();
		}

		skyboxes.clear();
	}

	// Render solid objects
	{
		currentRenderPass = RenderPassSolid;

		for (auto & object : solidObjects) {
			object->render();
		}

		solidObjects.clear();
	}

	currentRenderPass = RenderPassNone;
}

device::Device * Scene::getDevice()
{
	return &device;
}

void Scene::removeNode(Node* node)
{
	auto it = std::find(sceneNodes.begin(), sceneNodes.end(), node);
	if (it != sceneNodes.end())
	{
		delete node;

		sceneNodes.erase(it);
	}
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

Skybox* Scene::addSkybox(Texture* top, Texture* bottom, Texture* left,
	Texture* right, Texture* front, Texture* back, Node* parent, int id)
{
	if (parent == nullptr)
	{
		parent = this;
	}

	Skybox* skybox = new Skybox(top, bottom, left, right, front, back, parent,
		this, id);
	sceneNodes.push_back(skybox);

	return skybox;
}

Terrain * Scene::addTerrain(unsigned terrainSize, const std::vector<float>& heightMap,
	unsigned colorMapSize, const std::vector<gfx::Color>& colorMap,
	const math::Vector2f& scale, int id)
{
	Terrain * terrain = new Terrain(terrainSize, heightMap, colorMapSize, colorMap,
		this, this, id, scale);

	sceneNodes.push_back(terrain);

	return terrain;
}

InfinitePlane * Scene::addInfinitePlane(Texture * texture,
	const Color& planeColor, float textureScale,
	const math::Vector3f& position, Node* parent, int id)
{
	if (parent == nullptr)
	{
		parent = this;
	}

	InfinitePlane* plane = new InfinitePlane(texture, parent, this, planeColor,
		textureScale, position, id);

	sceneNodes.push_back(plane);

	return plane;
}

Node * Scene::addEmptyNode(Node * parent, int)
{
	if (parent == nullptr) {
		parent = this;
	}

	Node* emptyNode = new Node(*this, parent);

	sceneNodes.push_back(emptyNode);

	return emptyNode;
}

const std::string& Scene::getModPath() const
{
	return modPath;
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
		case RenderPassSolid:
		{
			solidObjects.push_back(node);

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
	for (auto & node : sceneNodes) {
		delete node;
	}

	sceneNodes.clear();
}

Scene::SceneNodeRenderPass Scene::getCurrentRenderPass() const
{
	return currentRenderPass;
}

bool Scene::isCulled(const Node*) const
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
