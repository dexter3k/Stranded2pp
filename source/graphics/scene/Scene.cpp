#include "Scene.h"

#include "Camera.h"
#include "Skybox.h"
#include "Terrain.h"

#include "../Color.h"
#include "../Material.h"
#include "../device/Device.h"

#include "../VertexBuffer.h"
#include "../IndexBuffer.h"

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

	debug();

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

void Scene::debug()
{

	MeshBuffer buffer(Vertex3D::DoubleTCoords, Index16Bit);
	buffer.getVertexBuffer().setUsed(4);

	auto vertices = static_cast<Vertex3D2TCoords*>(buffer.getVertices());
	vertices[0] = Vertex3D2TCoords(-1.0f, -1.0f, 0.0f, 0, 0, 1.0f, Color(255, 255, 255), 0.0f, 1.0f, 0.0f, 1.0f);
	vertices[1] = Vertex3D2TCoords( 1.0f, -1.0f, 0.0f, 0, 0, 1.0f, Color(255, 255, 255), 1.0f, 1.0f, 1.0f, 1.0f);
	vertices[2] = Vertex3D2TCoords( 1.0f,  1.0f, 0.0f, 0, 0, 1.0f, Color(255, 255, 255), 1.0f, 0.0f, 1.0f, 0.0f);
	vertices[3] = Vertex3D2TCoords(-1.0f,  1.0f, 0.0f, 0, 0, 1.0f, Color(255, 255, 255), 0.0f, 0.0f, 0.0f, 0.0f);
/*
	vertices[0] = Vertex3D(0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f,
		Color(255, 255, 255), 0.0f, 0.0f);
	vertices[1] = Vertex3D(1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f,
		Color(255, 255, 255), 0.0f, 1.0f);
	vertices[2] = Vertex3D(1.0f, 0.0f,-1.0f, 0.0f, 1.0f, 0.0f,
		Color(255, 255, 255), 1.0f, 1.0f);
	vertices[3] = Vertex3D(0.0f, 0.0f,-1.0f, 0.0f, 1.0f, 0.0f,
		Color(255, 255, 255), 1.0f, 0.0f);
*/
	buffer.getIndexBuffer().setUsed(6);

	auto indices = static_cast<uint16_t*>(buffer.getIndices());
	indices[0] = 0;
	indices[1] = 1;
	indices[2] = 3;
	indices[3] = 1;
	indices[4] = 2;
	indices[5] = 3;

	Material material;
	material.textureLayers[0].texture = device->loadTextureFromFile("mods/Stranded II/sys/gfx/iconbutton.bmp");

	static float rot;
	if (rot > 360.0f)
	{
		rot = 0.0f;
	}
	else if (rot < 0.0f)
	{
		rot = 360.0f;
	}

	rot += 4;

	math::Matrix4 transform;
	transform.setRotationDegrees(math::Vector3f(0.0f, rot, 0.0f));
	transform.setTranslation(math::Vector3f(0.0f, 0.0f, 0.0f));
	device->setTransform(device::Device::Model, transform);
	device->setMaterial(material);

	device->drawMeshBuffer(&buffer);

	device->releaseTexture("mods/Stranded II/sys/gfx/iconbutton.bmp");


/*
	MeshBuffer buffer(Vertex3D::Standard, Index16Bit);
	buffer.getVertexBuffer().setUsed(4);

	auto vertices = static_cast<Vertex3D*>(buffer.getVertices());
	vertices[0] = Vertex3D(-1.0f, -1.0f, 0.0f, 0, 0, 1.0f, Color(255, 255, 255), 0.0f, 1.0f);
	vertices[1] = Vertex3D( 1.0f, -1.0f, 0.0f, 0, 0, 1.0f, Color(255, 255, 255), 1.0f, 1.0f);
	vertices[2] = Vertex3D( 1.0f,  1.0f, 0.0f, 0, 0, 1.0f, Color(255, 255, 255), 1.0f, 0.0f);
	vertices[3] = Vertex3D(-1.0f,  1.0f, 0.0f, 0, 0, 1.0f, Color(255, 255, 255), 0.0f, 0.0f);

	buffer.getIndexBuffer().setUsed(6);

	auto indices = static_cast<uint16_t*>(buffer.getIndices());
	indices[0] = 0;
	indices[1] = 1;
	indices[2] = 3;
	indices[3] = 1;
	indices[4] = 2;
	indices[5] = 3;

	Material material;
	material.textureLayers[0].texture = device->loadTextureFromFile("mods/Stranded II/sys/gfx/tutor.bmp");

	device->setTransform(device::Device::Model, math::Matrix4());
	device->setMaterial(material);
	//device->drawIndexedPrimitiveList(vertices, 4, indices, 2,
	//	Vertex3D::Standard, Index16Bit);
	device->drawMeshBuffer(&buffer);

	device->releaseTexture("mods/Stranded II/sys/gfx/tutor.bmp");
*/
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
