#include "Scene.h"

#include "Camera.h"

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
	sceneNodes()
{}

Scene::~Scene()
{
	for (auto&& node : sceneNodes)
	{
		delete node;
	}

	sceneNodes.clear();
}

float roty = 0.0f;
float rotx = 0.0f;

void Scene::drawAll()
{
	// TODO

	if (device == nullptr)
	{
		return;
	}

	Material test;
	test.materialType = Material::SharpTransparent;
	test.wireframe = false;
	test.backFaceCulling = false;
	test.frontFaceCulling = false;
	test.textureLayers[0].texture = device->loadTextureFromFile("mods/Stranded II/sys/gfx/tutor.bmp", true);

	device->setMaterial(test);
	device->resetTransforms();

	RootNode::onAnimate(1.0f);

	cameraWorldPosition = math::Vector3f(0.0f, 0.0f, 0.0f);
	if (activeCamera != nullptr)
	{
		activeCamera->render();
		cameraWorldPosition = activeCamera->getAbsolutePosition();
	}

	//device->draw3DLine(math::Vector3f(-2.0f, 0.0f, -10.0f),
	//	math::Vector3f(5.0f, -3.0f, -10.0f));

	device->setTransform(device::Device::Model,
		math::Matrix4()
			.setTranslation(math::Vector3f(0.0f, 0.0f, -5.0f))
			.setRotationDegrees(math::Vector3f(++rotx, ++roty, 0.0f)));

	const unsigned vertexCount = 24;
	Vertex3D vertices[vertexCount] = {
		Vertex3D(-0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 0.0f, Color(255, 255, 255), 0.0f, 0.0f),
		Vertex3D(-0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 0.0f, Color(255, 255, 255), 0.0f, 1.0f),
		Vertex3D(0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 0.0f, Color(255, 255, 255), 1.0f, 1.0f),
		Vertex3D(0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 0.0f, Color(255, 255, 255), 1.0f, 0.0f),

		Vertex3D(-0.5f, 0.5f, -0.5f, 0.0f, 0.0f, 0.0f, Color(255, 255, 255), 0.0f, 0.0f),
		Vertex3D(-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, Color(255, 255, 255), 0.0f, 1.0f),
		Vertex3D(0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, Color(255, 255, 255), 1.0f, 1.0f),
		Vertex3D(0.5f, 0.5f, -0.5f, 0.0f, 0.0f, 0.0f, Color(255, 255, 255), 1.0f, 0.0f),

		Vertex3D(-0.5f, 0.5f, -0.5f, 0.0f, 0.0f, 0.0f, Color(255, 255, 255), 0.0f, 0.0f),
		Vertex3D(-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, Color(255, 255, 255), 0.0f, 1.0f),
		Vertex3D(-0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 0.0f, Color(255, 255, 255), 1.0f, 1.0f),
		Vertex3D(-0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 0.0f, Color(255, 255, 255), 1.0f, 0.0f),

		Vertex3D(0.5f, 0.5f, -0.5f, 0.0f, 0.0f, 0.0f, Color(255, 255, 255), 0.0f, 0.0f),
		Vertex3D(0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, Color(255, 255, 255), 0.0f, 1.0f),
		Vertex3D(0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 0.0f, Color(255, 255, 255), 1.0f, 1.0f),
		Vertex3D(0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 0.0f, Color(255, 255, 255), 1.0f, 0.0f),

		Vertex3D(0.5f, 0.5f, -0.5f, 0.0f, 0.0f, 0.0f, Color(255, 255, 255), 0.0f, 0.0f),
		Vertex3D(-0.5f, 0.5f, -0.5f, 0.0f, 0.0f, 0.0f, Color(255, 255, 255), 0.0f, 1.0f),
		Vertex3D(-0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 0.0f, Color(255, 255, 255), 1.0f, 1.0f),
		Vertex3D(0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 0.0f, Color(255, 255, 255), 1.0f, 0.0f),

		Vertex3D(0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, Color(255, 255, 255), 0.0f, 0.0f),
		Vertex3D(-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, Color(255, 255, 255), 0.0f, 1.0f),
		Vertex3D(-0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 0.0f, Color(255, 255, 255), 1.0f, 1.0f),
		Vertex3D(0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 0.0f, Color(255, 255, 255), 1.0f, 0.0f),
	};
	unsigned short indices[] = {0, 1, 2, 0, 2, 3, 4, 5, 6, 4, 6, 7, 8, 9, 10, 8, 10, 11, 12, 13, 14, 12, 14, 15, 16, 17, 18, 16, 18, 19, 20, 21, 22, 20, 22, 23};
	unsigned primitiveCount = 12;

	device->drawIndexedPrimitiveList(vertices, vertexCount, indices, primitiveCount);

	device->draw2DRectangleOutline(math::Recti(50, 50, 750, 550));

	device->draw2DImage(
		device->loadTextureFromFile("mods/Stranded II/sys/gfx/tutor.bmp", true),
		math::Recti(51, 51, 250, 200));
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

Node* Scene::addSkyBox(Texture* top, Texture* bottom, Texture* left,
	Texture* right, Texture* front, Texture* back, Node* parent, int id)
{
	// TODO
	return nullptr;
}

Node* Scene::addEmptyNode(Node* parent, int id)
{
	// TODO
	return nullptr;
}

Node* Scene::getRootNode()
{
	return this;
}

Camera* Scene::getActiveCamera() const
{
	// TODO
	return activeCamera;
}

void Scene::setActiveCamera(Camera* camera)
{
	activeCamera = camera;
}

bool Scene::registerNodeForRendering(Node* node, SceneNodeRenderPass pass)
{
	// TODO
	return false;
}

void Scene::clearScene()
{
	// TODO
}

Scene::SceneNodeRenderPass Scene::getCurrentRenderPass() const
{
	// TODO
	return RenderPassNone;
}

const Color& Scene::getAmbientLightColor() const
{
	// TODO
	return Color(255, 255, 255);
}

void Scene::setAmbientLightColor(const Color& color)
{
	// TODO
}

bool Scene::isCulled(const Node* node) const
{
	// TODO
	return false;
}

void Scene::render()
{
	// TODO
}

} // namespace scene

} // namespace gfx
