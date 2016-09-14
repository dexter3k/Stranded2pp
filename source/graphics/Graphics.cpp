#include "Graphics.h"

#include "device/Device.h"
#include "device/OpenGLDevice.h"
#include "scene/Scene.h"

#include "common/Modification.h"
#include "input/Input.h"

namespace gfx
{

Graphics::Graphics(Input& input) :
	input(input),
	device(new device::OpenGLDevice()),
	scene(new scene::Scene(*this))
{}

Graphics::~Graphics()
{}

bool Graphics::init(const Modification& modification)
{
	if (!device->init())
	{
		return false;
	}

	myTexture = device->loadTextureFromFile(modification.getPath() + "sys/gfx/bigbutton.bmp");

	return true;
}

void Graphics::update(float deltaTime)
{}

void Graphics::drawAll()
{
	device->beginScene();

	scene->drawAll();

	device->draw2DRectangle(Color(0, 255, 0), math::Recti(400, 80, 700, 100));
	device->draw2DRectangle(Color(0, 255, 255), math::Recti(40, 80, 100, 100));
	device->draw2DRectangle(Color(255, 0, 0), math::Recti(80, 40, 100, 100));
	device->draw2DRectangle(Color(0, 0, 255), math::Recti(100, 200, 300, 400));
	device->draw2DRectangle(Color(0, 255, 0, 127), math::Recti(200, 300, 500, 580));

	device->draw2DRectangle(math::Recti(100, 100, 700, 500),
		Color(0, 255, 0, 32), Color(0, 255, 255), Color(255, 0, 0), Color(0, 0, 255));

	device->drawPixel(10, 10, Color(0, 255, 0));

	device->draw2DPolygon(math::Vector2i(400, 300), 300.0f, Color(0, 255, 0), 15);

	device->draw2DRectangleOutline(math::Recti(40, 40, 100, 100), Color(0, 255, 255));

	device->draw2DImage(myTexture, math::Vector2i(100, 100));

	device->endScene();
}

} // namespace gfx
