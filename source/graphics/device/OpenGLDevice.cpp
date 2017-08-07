#include "OpenGLDevice.h"

#include <cmath>
#include <iostream>
#include <stdexcept>

#include <SFML/OpenGL.hpp>

#include "../MeshBuffer.h"

#include "math/MathUtility.h"
#include "common/FileSystem.h"

namespace gfx
{

namespace device
{

namespace impl
{
	static inline char* buffer_offset(const long offset)
	{
		return (static_cast<char*>(0) + offset);
	}
} // namespace impl

OpenGLDevice::OpenGLDevice() :
	super(),
	clearColor(0, 0, 0, 255),
	loadedTextures(),
	matrices(),
	transformationChanged(true),
	screenSize(800, 600),
	quad2DVertices(),
	quad2DIndices{0, 1, 2, 3},
	bindedTextures(),
	clientStateVertex(false),
	clientStateNormal(false),
	clientStateColor(false),
	clientStateTexCoord0(false),
	currentRenderMode(RenderModeNone),
	currentMaterial(),
	lastMaterial(),
	material2D(),
	shouldResetRenderStates(true)
{
	deviceName = "OpenGL";

	material2D.lighting = false;
	material2D.zWriteEnabled = false;
	material2D.useMipMaps = false;
	for (unsigned i = 0; i < maxTextures; ++i)
	{
		material2D.textureLayers[i].bilinearFilter = false;
	}

	if (!init())
		throw std::runtime_error("Unable to init OpenGLDevice");
}

OpenGLDevice::~OpenGLDevice()
{
	std::cout << loadedTextures.size() << " textures left loaded!" << std::endl;
	for (const auto& texture : loadedTextures)
	{
		std::cout << texture.first << std::endl;
	}

	for (unsigned i = 0; i < maxTextures; ++i)
	{
		bindTexture(i, nullptr);
	}

	for (auto&& holderEntry : loadedTextures)
	{
		delete holderEntry.second.texture;
	}

	loadedTextures.clear();
}

bool OpenGLDevice::init()
{
	setClearColor(clearColor);

	resetTransforms();

	glDepthMask(true);
	glClearDepth(1.0);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
	glHint(GL_POINT_SMOOTH_HINT, GL_FASTEST);

	//glFrontFace(GL_CCW);

	quad2DVertices[0] = Vertex3D(math::Vector3f(-1.0f, 1.0f, 0.0f),
		math::Vector3f(0.0f, 0.0f, 0.0f),
		Color(255, 255, 255, 255),
		math::Vector2f(0.0f, 1.0f));
	quad2DVertices[1] = Vertex3D(math::Vector3f(1.0f, 1.0f, 0.0f),
		math::Vector3f(0.0f, 0.0f, 0.0f),
		Color(255, 255, 255, 255),
		math::Vector2f(1.0f, 1.0f));
	quad2DVertices[2] = Vertex3D(math::Vector3f(1.0f, -1.0f, 0.0f),
		math::Vector3f(0.0f, 0.0f, 0.0f),
		Color(255, 255, 255, 255),
		math::Vector2f(1.0f, 0.0f));
	quad2DVertices[3] = Vertex3D(math::Vector3f(-1.0f, -1.0f, 0.0f),
		math::Vector3f(0.0f, 0.0f, 0.0f),
		Color(255, 255, 255, 255),
		math::Vector2f(0.0f, 0.0f));

	set3DRenderMode();

	//setFog();

	shouldResetRenderStates = true;

	return true;
}

math::Vector2u OpenGLDevice::getRenderTargetSize() const
{
	return screenSize;
}

Texture* OpenGLDevice::grabTexture(const std::string& name)
{
	auto it = loadedTextures.find(name);
	if (it == loadedTextures.end())
	{
		return nullptr;
	}

	++(it->second.referenceCount);

	return it->second.texture;
}

void OpenGLDevice::releaseTexture(const std::string& name)
{
	auto it = loadedTextures.find(name);
	if (it == loadedTextures.end())
	{
		std::cout << "Error: Trying to release unknown texture - '" << name <<
			"'" << std::endl;

		assert(!"Releasing unknown texture!");

		return;
	}

	if (it->second.referenceCount <= 1)
	{
		delete it->second.texture;

		loadedTextures.erase(name);
	}
	else
	{
		--(it->second.referenceCount);
	}
}

Texture* OpenGLDevice::loadTextureFromFile(const std::string& name,
	bool loadEmptyIfMissing, bool applyColorKey, const Color& colorKey)
{
	auto it = loadedTextures.find(name);
	if (it != loadedTextures.end())
	{
		std::cout << "Warn: texture '" << name << "' is already loaded!" <<
			std::endl;

		return grabTexture(name);	
	}

	Image image;
	bool exists = fs::checkFileExists(name);
	if (!exists ||
		!image.loadFromFile(name))
	{
		if (!exists)
		{
			std::cout << "Error: unable to load texture: file '" << name << 
				"' does not exist" << std::endl;
		}
		else
		{
			std::cout << "Error: unable to load texture: file '" << name << 
				"' is corrupted" << std::endl;
		}

		if (!loadEmptyIfMissing)
		{
			return nullptr;
		}

		std::cout << "Creating empty \"missing\" texture" << std::endl;

		image.create(math::Vector2u(16, 16), Color(127, 31, 127));
	}

	if (applyColorKey)
	{
		image.applyColorKey(colorKey);
	}

	return createTextureFromImage(name, image);
}

Texture* OpenGLDevice::loadTextureFromImage(const std::string& name,
	const Image& image)
{
	auto it = loadedTextures.find(name);
	if (it != loadedTextures.end())
	{
		std::cout << "Error: texture '" << name << "' is already loaded!" <<
			std::endl;

		assert(!"Texture is already loaded (fromImage)");
	}

	return createTextureFromImage(name, image);	
}

/*
	Rendering utilities
*/

void OpenGLDevice::beginScene()
{
	glDepthMask(true);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
}

void OpenGLDevice::endScene()
{}

void OpenGLDevice::setClearColor(const Color& color)
{
	clearColor = color;

	glClearColor(clearColor.getClampRed(), clearColor.getClampGreen(),
		clearColor.getClampBlue(), clearColor.getClampAlpha());
}

void OpenGLDevice::clearZBuffer()
{
	glClear(GL_DEPTH_BUFFER_BIT);
}

/*
	Rendering properties
*/

void OpenGLDevice::setTransform(TransformType transformType,
	const math::Matrix4& transform)
{
	matrices[transformType] = transform;
	transformationChanged = true;

	switch (transformType)
	{
		case View:
		case Model:
		{
			glMatrixMode(GL_MODELVIEW);

			glLoadMatrixf(matrices[View].pointer());
			glMultMatrixf(matrices[Model].pointer());

			break;
		}
		case Projection:
		{
			glMatrixMode(GL_PROJECTION);
			glLoadMatrixf(matrices[Projection].pointer());

			break;
		}
		default:
		{
			break;
		}
	}
}

void OpenGLDevice::resetTransforms()
{
	for (unsigned i = 0; i < TransformCount; ++i)
	{
		setTransform(static_cast<TransformType>(i), math::Matrix4());
	}
}

void OpenGLDevice::setMaterial(const Material& material)
{
	currentMaterial = material;

	// NOTE: maxTextures and maxTexturesPerMaterial are static consts
	// We must copy them to a real value
	unsigned max = math::min(unsigned(maxTextures),
		unsigned(Material::maxTexturesPerMaterial));
	for (unsigned i = 0; i < max; ++i)
	{
		bindTexture(i, material.textureLayers[i].texture);
		setTransform(static_cast<TransformType>(Texture0 + i),
			material.textureLayers[i].textureMatrix);
	}

	glActiveTexture(GL_TEXTURE0);
}

/*
	3D Rendering
*/

void OpenGLDevice::draw3DLine(const math::Vector3f& start,
	const math::Vector3f& end, const Color& color)
{
	set3DRenderMode();

	quad2DVertices[0].color = color;
	quad2DVertices[1].color = color;

	quad2DVertices[0].position = start;
	quad2DVertices[1].position = end;

	setClientStates(true, false, true, false);

	glVertexPointer(3, GL_FLOAT, sizeof(Vertex3D),
		&((static_cast<const Vertex3D*>(quad2DVertices))[0].position));
	glColorPointer(4, GL_UNSIGNED_BYTE, sizeof(Vertex3D),
		&((static_cast<const Vertex3D*>(quad2DVertices))[0].color));

	glDrawElements(GL_LINES, 2, GL_UNSIGNED_SHORT, quad2DIndices);
}

void OpenGLDevice::drawIndexedPrimitiveList(const void* vertices,
	uint32_t vertexCount, const void* indices, uint32_t primitiveCount,
	Vertex3D::VertexType vertexType, IndexSize indexSize)
{
	if (vertexCount == 0 || primitiveCount == 0)
	{
		return;
	}

	if (primitiveCount > 0x7fffffff)
	{
		std::cout << "Unable to draw so much primitives (" << primitiveCount <<
			") limit: " << 0x7fffffff << std::endl;

		return;
	}

	set3DRenderMode();

	setClientStates(true, true, true, true);

	switch (vertexType)
	{
		case Vertex3D::Standard:
		{
			if (vertices != nullptr)
			{
				glNormalPointer(GL_FLOAT, sizeof(Vertex3D),
					&((static_cast<const Vertex3D*>(vertices))[0].normal));
				glColorPointer(4, GL_UNSIGNED_BYTE, sizeof(Vertex3D),
					&((static_cast<const Vertex3D*>(vertices))[0].color));
				glTexCoordPointer(2, GL_FLOAT, sizeof(Vertex3D),
					&((static_cast<const Vertex3D*>(vertices))[0].textureCoords));
				glVertexPointer(3, GL_FLOAT, sizeof(Vertex3D),
					&((static_cast<const Vertex3D*>(vertices))[0].position));
			}
			else
			{
				glNormalPointer(GL_FLOAT, sizeof(Vertex3D),
					impl::buffer_offset(12));
				glColorPointer(4, GL_UNSIGNED_BYTE, sizeof(Vertex3D),
					impl::buffer_offset(24));
				glTexCoordPointer(2, GL_FLOAT, sizeof(Vertex3D),
					impl::buffer_offset(28));
				glVertexPointer(3, GL_FLOAT, sizeof(Vertex3D),
					impl::buffer_offset(0));
			}

			if (bindedTextures[1] != nullptr)
			{
				glClientActiveTexture(GL_TEXTURE1);
				glEnableClientState(GL_TEXTURE_COORD_ARRAY);

				if (vertices != nullptr)
				{
					glTexCoordPointer(2, GL_FLOAT, sizeof(Vertex3D),
						&((static_cast<const Vertex3D*>(vertices))[0]
							.textureCoords));
				}
				else
				{
					glTexCoordPointer(2, GL_FLOAT, sizeof(Vertex3D),
						impl::buffer_offset(28));
				}
			}

			break;
		}
		case Vertex3D::DoubleTCoords:
		{
			if (vertices != nullptr)
			{
				glNormalPointer(GL_FLOAT, sizeof(Vertex3D2TCoords),
					&((static_cast<const Vertex3D2TCoords*>(vertices))[0]
						.normal));
				glColorPointer(4, GL_UNSIGNED_BYTE, sizeof(Vertex3D2TCoords),
					&((static_cast<const Vertex3D2TCoords*>(vertices))[0]
						.color));
				glTexCoordPointer(2, GL_FLOAT, sizeof(Vertex3D2TCoords),
					&((static_cast<const Vertex3D2TCoords*>(vertices))[0]
						.textureCoords));
				glVertexPointer(3, GL_FLOAT, sizeof(Vertex3D2TCoords),
					&((static_cast<const Vertex3D2TCoords*>(vertices))[0]
						.position));

				glClientActiveTexture(GL_TEXTURE1);
				glEnableClientState(GL_TEXTURE_COORD_ARRAY);
				glTexCoordPointer(2, GL_FLOAT, sizeof(Vertex3D2TCoords),
					&((static_cast<const Vertex3D2TCoords*>(vertices))[0]
						.textureCoords2));
			}
			else
			{
				glNormalPointer(GL_FLOAT, sizeof(Vertex3D2TCoords),
					impl::buffer_offset(12));
				glColorPointer(4, GL_UNSIGNED_BYTE, sizeof(Vertex3D2TCoords),
					impl::buffer_offset(24));
				glTexCoordPointer(2, GL_FLOAT, sizeof(Vertex3D2TCoords),
					impl::buffer_offset(28));
				glVertexPointer(3, GL_FLOAT, sizeof(Vertex3D2TCoords),
					impl::buffer_offset(0));

				glClientActiveTexture(GL_TEXTURE1);
				glEnableClientState(GL_TEXTURE_COORD_ARRAY);
				glTexCoordPointer(2, GL_FLOAT, sizeof(Vertex3D2TCoords),
					impl::buffer_offset(36));
			}

			break;
		}
		default:
		{
			break;
		}
	}

	GLenum glIndexSize = GL_UNSIGNED_SHORT;
	switch (indexSize)
	{
		case Index32Bit:
		{
			glIndexSize = GL_UNSIGNED_INT;

			break;
		}
		case Index16Bit:
		{
			glIndexSize = GL_UNSIGNED_SHORT;

			break;
		}
		default:
		{
			break;
		}
	}

	glDrawElements(GL_TRIANGLES, primitiveCount * 3, glIndexSize, indices);

	if (bindedTextures[1] != nullptr ||
		vertexType == Vertex3D::DoubleTCoords)
	{
		glClientActiveTexture(GL_TEXTURE1);
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);

		glClientActiveTexture(GL_TEXTURE0);
	}
}


// Mesh buffers


void OpenGLDevice::drawMeshBuffer(const MeshBuffer* meshBuffer)
{
	if (meshBuffer == nullptr)
	{
		return;
	}

	// TOOD

	if (false)
	{

	}
	else
	{
		drawIndexedPrimitiveList(meshBuffer->getVertices(),
			meshBuffer->getVertexCount(), meshBuffer->getIndices(),
			meshBuffer->getIndexCount() / 3,
			meshBuffer->getVertexType(), meshBuffer->getIndexSize());
	}
}


/*
	2D Rendering
*/

void OpenGLDevice::drawPixel(unsigned x, unsigned y, const Color& pixelColor)
{
	auto renderTargetSize = getRenderTargetSize();
	if (x > renderTargetSize.x || y > renderTargetSize.y)
	{
		return;
	}

	disableTextures();
	set2DRenderMode(pixelColor.getAlpha() < 255, false, false);

	quad2DVertices[0].color = pixelColor;
	quad2DVertices[0].position = math::Vector3f(static_cast<float>(x),
		static_cast<float>(x), 0.0f);

	setClientStates(true, false, true, false);

	glVertexPointer(2, GL_FLOAT, sizeof(Vertex3D),
		&((static_cast<const Vertex3D*>(quad2DVertices))[0].position));
	glColorPointer(4, GL_UNSIGNED_BYTE, sizeof(Vertex3D),
		&((static_cast<const Vertex3D*>(quad2DVertices))[0].color));

	glDrawArrays(GL_POINTS, 0, 1);
}

void OpenGLDevice::draw2DImage(Texture* texture,
	const math::Vector2i& imageDestination)
{
	if (!texture)
	{
		return;
	}

	auto originalSize = texture->getSize();

	draw2DImage(texture, imageDestination,
		math::Recti(0, 0, static_cast<int>(originalSize.x),
			static_cast<int>(originalSize.y)));
}

void OpenGLDevice::draw2DImage(Texture* texture,
	const math::Vector2i& imageDestination, const math::Recti& sourceRectangle,
	const Color& color, const math::Recti* clippingRectangle,
	bool useAlphaChannel)
{
	if (!texture)
	{
		return;
	}

	if (!sourceRectangle.isValid())
	{
		return;
	}

	math::Vector2i targetPosition = imageDestination;
	math::Vector2i sourcePosition = sourceRectangle.upperLeft;

	math::Vector2i sourceSize = sourceRectangle.getSize();
	// TODO
	if (clippingRectangle)
	{

	}

	if (targetPosition.x < 0)
	{
		sourceSize.x += targetPosition.x;
		if (sourceSize.x <= 0)
		{
			return;
		}

		sourcePosition.x -= targetPosition.x;
		targetPosition.x = 0;
	}

	// TODO
	const math::Vector2u& renderTargetSize = getRenderTargetSize();

	if (targetPosition.x + sourceSize.x > static_cast<int>(renderTargetSize.x))
	{
		sourceSize.x -= (targetPosition.x + sourceSize.x) - renderTargetSize.x;
		if (sourceSize.x <= 0)
		{
			return;
		}
	}

	if (targetPosition.y < 0)
	{
		sourceSize.y += targetPosition.y;
		if (sourceSize.y <= 0)
		{
			return;
		}

		sourcePosition.y -= targetPosition.y;
		targetPosition.y = 0;
	}

	if (targetPosition.y + sourceSize.y > static_cast<int>(renderTargetSize.y))
	{
		sourceSize.y -= (targetPosition.y + sourceSize.y) - renderTargetSize.y;
		if (sourceSize.y <= 0)
		{
			return;
		}
	}

	const math::Vector2u& textureSize = texture->getSize();
	float invertedWidth = 1.0f / static_cast<float>(textureSize.x);
	float invertedHeight = 1.0f / static_cast<float>(textureSize.y);

	math::Rectf textureCoords(
		sourcePosition.x * invertedWidth,
		sourcePosition.y * invertedHeight,
		(sourcePosition.x + sourceSize.x) * invertedWidth,
		(sourcePosition.y + sourceSize.y) * invertedHeight);

	math::Recti poss(targetPosition, targetPosition + sourceSize);

	disableTextures(1);
	bindTexture(0, texture);

	set2DRenderMode(color.getAlpha() < 255, true, useAlphaChannel);

	quad2DVertices[0].color = color;
	quad2DVertices[1].color = color;
	quad2DVertices[2].color = color;
	quad2DVertices[3].color = color;

	quad2DVertices[0].position = math::Vector3f(
		static_cast<float>(poss.upperLeft.x),
		static_cast<float>(poss.upperLeft.y), 0.0f);
	quad2DVertices[3].position = math::Vector3f(
		static_cast<float>(poss.lowerRight.x),
		static_cast<float>(poss.upperLeft.y), 0.0f);
	quad2DVertices[2].position = math::Vector3f(
		static_cast<float>(poss.lowerRight.x),
		static_cast<float>(poss.lowerRight.y), 0.0f);
	quad2DVertices[1].position = math::Vector3f(
		static_cast<float>(poss.upperLeft.x),
		static_cast<float>(poss.lowerRight.y), 0.0f);

	quad2DVertices[0].textureCoords = math::Vector2f(textureCoords.upperLeft.x,
		textureCoords.upperLeft.y);
	quad2DVertices[3].textureCoords = math::Vector2f(textureCoords.lowerRight.x,
		textureCoords.upperLeft.y);
	quad2DVertices[2].textureCoords = math::Vector2f(textureCoords.lowerRight.x,
		textureCoords.lowerRight.y);
	quad2DVertices[1].textureCoords = math::Vector2f(textureCoords.upperLeft.x,
		textureCoords.lowerRight.y);

	setClientStates(true, false, true, true);

	glTexCoordPointer(2, GL_FLOAT, sizeof(Vertex3D),
		&((static_cast<const Vertex3D*>(quad2DVertices))[0].textureCoords));
	glVertexPointer(2, GL_FLOAT, sizeof(Vertex3D),
		&((static_cast<const Vertex3D*>(quad2DVertices))[0].position));
	glColorPointer(4, GL_UNSIGNED_BYTE, sizeof(Vertex3D),
		&((static_cast<const Vertex3D*>(quad2DVertices))[0].color));

	glDrawElements(GL_TRIANGLE_FAN, 4, GL_UNSIGNED_SHORT, quad2DIndices);
}

void OpenGLDevice::draw2DImage(Texture* texture,
	const math::Recti& destinationRectangle)
{
	if (!texture)
	{
		return;
	}

	auto originalSize = texture->getSize();

	draw2DImage(texture, destinationRectangle,
		math::Recti(0, 0, static_cast<int>(originalSize.x),
			static_cast<int>(originalSize.y)));
}

void OpenGLDevice::draw2DImage(Texture* texture,
	const math::Recti& destinationRectangle, const math::Recti& sourceRectangle,
	const Color* colors, const math::Recti* clippingRectangle,
	bool useAlphaChannel)
{
	if (texture == nullptr)
	{
		return;
	}

	math::Vector2u textureSize = texture->getSize();
	float invertedWidth = 1.0f / static_cast<float>(textureSize.x);
	float invertedHeight = 1.0f / static_cast<float>(textureSize.y);

	math::Rectf textureCoords(
		sourceRectangle.upperLeft.x * invertedWidth,
		sourceRectangle.upperLeft.y * invertedHeight,
		sourceRectangle.lowerRight.x * invertedWidth,
		sourceRectangle.lowerRight.y * invertedHeight);

	Color tempColors[4] = {
		Color(255, 255, 255, 255),
		Color(255, 255, 255, 255),
		Color(255, 255, 255, 255),
		Color(255, 255, 255, 255)
	};

	const Color* usedColors = colors ? colors : tempColors;

	disableTextures(1);
	bindTexture(0, texture);

	set2DRenderMode((usedColors[0].getAlpha() < 255) ||
		(usedColors[1].getAlpha() < 255) ||
		(usedColors[2].getAlpha() < 255) ||
		(usedColors[3].getAlpha() < 255), true, useAlphaChannel);

	if (clippingRectangle)
	{
		if (!clippingRectangle->isValid())
		{
			return;
		}

		glEnable(GL_SCISSOR_TEST);
		math::Vector2u renderTargetSize = getRenderTargetSize();
		glScissor(clippingRectangle->upperLeft.x,
			renderTargetSize.y - clippingRectangle->lowerRight.y,
			clippingRectangle->getWidth(), clippingRectangle->getHeight());
	}

	quad2DVertices[0].color = usedColors[0];
	quad2DVertices[1].color = usedColors[3];
	quad2DVertices[2].color = usedColors[2];
	quad2DVertices[3].color = usedColors[1];

	quad2DVertices[0].position = math::Vector3f(
		static_cast<float>(destinationRectangle.upperLeft.x),
		static_cast<float>(destinationRectangle.upperLeft.y), 0.0f);
	quad2DVertices[3].position = math::Vector3f(
		static_cast<float>(destinationRectangle.lowerRight.x),
		static_cast<float>(destinationRectangle.upperLeft.y), 0.0f);
	quad2DVertices[2].position = math::Vector3f(
		static_cast<float>(destinationRectangle.lowerRight.x),
		static_cast<float>(destinationRectangle.lowerRight.y), 0.0f);
	quad2DVertices[1].position = math::Vector3f(
		static_cast<float>(destinationRectangle.upperLeft.x),
		static_cast<float>(destinationRectangle.lowerRight.y), 0.0f);

	quad2DVertices[0].textureCoords = math::Vector2f(textureCoords.upperLeft.x,
		textureCoords.upperLeft.y);
	quad2DVertices[3].textureCoords = math::Vector2f(textureCoords.lowerRight.x,
		textureCoords.upperLeft.y);
	quad2DVertices[2].textureCoords = math::Vector2f(textureCoords.lowerRight.x,
		textureCoords.lowerRight.y);
	quad2DVertices[1].textureCoords = math::Vector2f(textureCoords.upperLeft.x,
		textureCoords.lowerRight.y);

	setClientStates(true, false, true, true);

	glTexCoordPointer(2, GL_FLOAT, sizeof(Vertex3D),
		&((static_cast<const Vertex3D*>(quad2DVertices))[0].textureCoords));
	glVertexPointer(2, GL_FLOAT, sizeof(Vertex3D),
		&((static_cast<const Vertex3D*>(quad2DVertices))[0].position));
	glColorPointer(4, GL_UNSIGNED_BYTE, sizeof(Vertex3D),
		&((static_cast<const Vertex3D*>(quad2DVertices))[0].color));

	glDrawElements(GL_TRIANGLE_FAN, 4, GL_UNSIGNED_SHORT, quad2DIndices);

	if (clippingRectangle)
	{
		glDisable(GL_SCISSOR_TEST);
	}
}

void OpenGLDevice::draw2DLine(const math::Vector2i& start,
	const math::Vector2i& end, const Color& color)
{
	if (start == end)
	{
		drawPixel(start.x, start.y, color);
	}
	else
	{
		disableTextures();
		set2DRenderMode(color.getAlpha() < 255, false, false);

		quad2DVertices[0].color = color;
		quad2DVertices[1].color = color;

		quad2DVertices[0].position = math::Vector3f(static_cast<float>(start.x),
			static_cast<float>(start.y), 0.0f);
		quad2DVertices[1].position = math::Vector3f(static_cast<float>(end.x),
			static_cast<float>(end.y), 0.0f);

		setClientStates(true, false, true, false);

		glVertexPointer(2, GL_FLOAT, sizeof(Vertex3D),
			&((static_cast<const Vertex3D*>(quad2DVertices))[0].position));
		glColorPointer(4, GL_UNSIGNED_BYTE, sizeof(Vertex3D),
			&((static_cast<const Vertex3D*>(quad2DVertices))[0].color));

		glDrawElements(GL_LINES, 2, GL_UNSIGNED_SHORT, quad2DIndices);
	}
}

void OpenGLDevice::draw2DPolygon(const math::Vector2i& center, float radius,
	unsigned vertexCount, const Color& color)
{
	if (vertexCount < 2)
	{
		return;
	}

	math::Vector2i first;
	math::Vector2i a, b;

	for (unsigned i = 0; i < vertexCount; ++i)
	{
		b = a;

		float p = static_cast<float>(i) / static_cast<float>(vertexCount) *
			(math::pi * 2);

		a = center + math::Vector2i(static_cast<int>(std::sin(p) * radius),
			static_cast<int>(std::cos(p) * radius));

		if (i == 0)
		{
			first = a;
		}
		else
		{
			draw2DLine(a, b, color);
		}
	}

	draw2DLine(a, first, color);
}

void OpenGLDevice::draw2DRectangle(const math::Recti& destinationRectangle,
	const Color& color, const math::Recti* clippingRectangle)
{
	if (color.getAlpha() == 0)
		return;

	math::Recti clipped = destinationRectangle;
	if (clippingRectangle != nullptr)
	{
		clipped.clipAgainst(*clippingRectangle);
	}
	if (!clipped.isValid())
	{
		return;
	}

	disableTextures();
	set2DRenderMode(color.getAlpha() < 255, false, false);

	glColor4ub(color.getRed(), color.getGreen(), color.getBlue(),
		color.getAlpha());
	glRectf(static_cast<GLfloat>(clipped.upperLeft.x),
		static_cast<GLfloat>(clipped.lowerRight.y),
		static_cast<GLfloat>(clipped.lowerRight.x),
		static_cast<GLfloat>(clipped.upperLeft.y));
}

void OpenGLDevice::draw2DRectangle(const math::Recti& destinationRectangle,
	const Color& colorLeftUp, const Color& colorRightUp,
	const Color& colorLeftDown, const Color& colorRightDown,
	const math::Recti* clippingRectangle)
{
	math::Recti clipped = destinationRectangle;
	if (clippingRectangle != nullptr)
	{
		clipped.clipAgainst(*clippingRectangle);
	}
	if (!clipped.isValid())
	{
		return;
	}

	disableTextures();
	set2DRenderMode((colorLeftUp.getAlpha() < 255) ||
		(colorRightUp.getAlpha() < 255) ||
		(colorLeftDown.getAlpha() < 255) ||
		(colorRightDown.getAlpha() < 255), false, false);

	quad2DVertices[0].color = colorLeftUp;
	quad2DVertices[1].color = colorLeftDown;
	quad2DVertices[2].color = colorRightDown;
	quad2DVertices[3].color = colorRightUp;

	quad2DVertices[0].position = math::Vector3f(
		static_cast<float>(clipped.upperLeft.x),
		static_cast<float>(clipped.upperLeft.y), 0.0f);
	quad2DVertices[1].position = math::Vector3f(
		static_cast<float>(clipped.upperLeft.x),
		static_cast<float>(clipped.lowerRight.y), 0.0f);
	quad2DVertices[2].position = math::Vector3f(
		static_cast<float>(clipped.lowerRight.x),
		static_cast<float>(clipped.lowerRight.y), 0.0f);
	quad2DVertices[3].position = math::Vector3f(
		static_cast<float>(clipped.lowerRight.x),
		static_cast<float>(clipped.upperLeft.y), 0.0f);

	setClientStates(true, false, true, false);

	glVertexPointer(2, GL_FLOAT, sizeof(Vertex3D),
		&((static_cast<const Vertex3D*>(quad2DVertices))[0].position));
	glColorPointer(4, GL_UNSIGNED_BYTE, sizeof(Vertex3D),
		&((static_cast<const Vertex3D*>(quad2DVertices))[0].color));

	glDrawElements(GL_TRIANGLE_FAN, 4, GL_UNSIGNED_SHORT, quad2DIndices);
}

void OpenGLDevice::draw2DRectangleOutline(
	const math::Recti& destinationRectangle, const Color& color)
{
	draw2DLine(destinationRectangle.upperLeft,
		math::Vector2i(destinationRectangle.lowerRight.x,
			destinationRectangle.upperLeft.y),
		color);
	draw2DLine(
		math::Vector2i(destinationRectangle.lowerRight.x,
			destinationRectangle.upperLeft.y),
		destinationRectangle.lowerRight, color);
	draw2DLine(destinationRectangle.lowerRight,
		math::Vector2i(destinationRectangle.upperLeft.x,
			destinationRectangle.lowerRight.y),
		color);
	draw2DLine(
		math::Vector2i(destinationRectangle.upperLeft.x,
			destinationRectangle.lowerRight.y),
		destinationRectangle.upperLeft, color);
}

/*
	Utility events
*/

void OpenGLDevice::onResize(math::Vector2u size)
{
	screenSize = size;

	glViewport(0, 0, size.x, size.y);

	transformationChanged = true;
}

/*
	Private utility functions
*/

void OpenGLDevice::bindTexture(unsigned textureLayer, Texture* texture)
{
	assert(textureLayer < maxTextures);

	if (bindedTextures[textureLayer] == texture)
	{
		return;
	}

	bindedTextures[textureLayer] = texture;
	glActiveTexture(GL_TEXTURE0 + textureLayer);

	if (texture == nullptr)
	{
		glBindTexture(GL_TEXTURE_2D, 0);
		glDisable(GL_TEXTURE_2D);

		return;
	}

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture->getGlTextureName());
}

void OpenGLDevice::disableTextures(unsigned fromLayer)
{
	for (unsigned i = fromLayer; i < maxTextures; ++i)
	{
		bindTexture(i, nullptr);
	}
}

void OpenGLDevice::setClientStates(bool vertex, bool normal, bool color,
	bool texCoord0)
{
	if (clientStateVertex != vertex)
	{
		if (vertex)
		{
			glEnableClientState(GL_VERTEX_ARRAY);
		}
		else
		{
			glDisableClientState(GL_VERTEX_ARRAY);
		}

		clientStateVertex = vertex;
	}

	if (clientStateNormal != normal)
	{
		if (normal)
		{
			glEnableClientState(GL_NORMAL_ARRAY);
		}
		else
		{
			glDisableClientState(GL_NORMAL_ARRAY);
		}
		clientStateNormal = normal;
	}

	if (clientStateColor != color)
	{
		if (color)
		{
			glEnableClientState(GL_COLOR_ARRAY);
		}
		else
		{
			glDisableClientState(GL_COLOR_ARRAY);
		}

		clientStateColor = color;
	}

	if (clientStateTexCoord0 != texCoord0)
	{
		glActiveTexture(GL_TEXTURE0);

		if (texCoord0)
		{
			glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		}
		else
		{
			glDisableClientState(GL_TEXTURE_COORD_ARRAY);
		}

		clientStateTexCoord0 = texCoord0;
	}
}

void OpenGLDevice::set2DRenderMode(bool transparent, bool textured,
	bool alphaChannel)
{
	if (currentRenderMode == RenderMode3D)
	{
		onUnsetMaterial();
	}

	if (currentRenderMode != RenderMode2D || transformationChanged)
	{
		math::Vector2u renderTargetSize = getRenderTargetSize();
		math::Matrix4 projection;
		projection.buildProjectionMatrixOrtho(
			static_cast<float>(renderTargetSize.x),
			-(static_cast<float>(renderTargetSize.y)), -1.0f, 1.0f);
		projection.setTranslation(math::Vector3f(-1.0f, 1.0f, 0.0f));

		glMatrixMode(GL_PROJECTION);
		glLoadMatrixf(projection.pointer());

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		// www.opengl.org/archives/resources/faq/technical/transformations.htm
		// 9.030
		// Used for exact "pixelization"

		// Important TODO
		glTranslatef(0.375f, 0.375f, 0.0f);

		transformationChanged = false;
	}

	if (currentRenderMode != RenderMode2D)
	{
		glActiveTexture(GL_TEXTURE0);

		setBasicRenderStates(material2D, lastMaterial, true);
		lastMaterial = material2D;

		// Is this really needed to be called twice on each frame?
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}

	bool blending = (textured & alphaChannel) || transparent;
	if (blending)
	{
		glEnable(GL_BLEND);
		glEnable(GL_ALPHA_TEST);
		glAlphaFunc(GL_GREATER, 0.0f);
	}
	else
	{
		glDisable(GL_BLEND);
		glDisable(GL_ALPHA_TEST);
	}

	if (textured)
	{
		setTextureRenderStates(material2D, false);

		currentMaterial.textureLayers[0].texture = getBindedTexture(0);
		setTransform(Texture0, math::Matrix4());
		transformationChanged = false; // Texture transformation won't affect

		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	}

	currentRenderMode = RenderMode2D;
}

void OpenGLDevice::set3DRenderMode()
{
	if (currentRenderMode != RenderMode3D)
	{
		glDisable(GL_BLEND);
		glDisable(GL_ALPHA_TEST);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glMatrixMode(GL_PROJECTION);
		glLoadMatrixf(matrices[Projection].pointer());

		glMatrixMode(GL_MODELVIEW);
		glLoadMatrixf((matrices[View] * matrices[Model]).pointer());

		glActiveTexture(GL_TEXTURE0);

		shouldResetRenderStates = true;
	}

	if (shouldResetRenderStates || lastMaterial != currentMaterial)
	{
		if (lastMaterial.materialType != currentMaterial.materialType)
		{
			onUnsetMaterial();
		}

		onSetMaterial();

		lastMaterial = currentMaterial;
		shouldResetRenderStates = false;
	}

	currentRenderMode = RenderMode3D;
}

void OpenGLDevice::setBasicRenderStates(const Material& currentMaterial,
	const Material& lastMaterial, bool shouldResetRenderStates)
{
	if (shouldResetRenderStates ||
		currentMaterial.colorMaterial != lastMaterial.colorMaterial)
	{
		if (currentMaterial.colorMaterial != Material::NoColorMaterial)
		{
			glEnable(GL_COLOR_MATERIAL);

			switch (currentMaterial.colorMaterial)
			{
				case Material::Diffuse:
				{
					glColorMaterial(GL_FRONT_AND_BACK, GL_DIFFUSE);

					break;
				}
				case Material::Ambient:
				{
					glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT);

					break;
				}
				case Material::Specular:
				{
					glColorMaterial(GL_FRONT_AND_BACK, GL_SPECULAR);

					break;
				}
				case Material::Emissive:
				{
					glColorMaterial(GL_FRONT_AND_BACK, GL_EMISSION);

					break;
				}
				case Material::DiffuseAndAmbient:
				{
					glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);

					break;
				}
				default:
				{
					glDisable(GL_COLOR_MATERIAL);

					break;
				}
			}
		}
		else
		{
			glDisable(GL_COLOR_MATERIAL);
		}
	}

	if (shouldResetRenderStates ||
		lastMaterial.diffuseColor != currentMaterial.diffuseColor ||
		lastMaterial.ambientColor != currentMaterial.ambientColor ||
		lastMaterial.emissiveColor != currentMaterial.emissiveColor ||
		lastMaterial.colorMaterial != currentMaterial.colorMaterial)
	{
		GLfloat color[4];

		float inverse = 1.0f / 255.0f;

		if (currentMaterial.colorMaterial != Material::Ambient &&
			currentMaterial.colorMaterial != Material::DiffuseAndAmbient)
		{
			color[0] = currentMaterial.ambientColor.getRed() * inverse;
			color[1] = currentMaterial.ambientColor.getGreen() * inverse;
			color[2] = currentMaterial.ambientColor.getBlue() * inverse;
			color[3] = currentMaterial.ambientColor.getAlpha() * inverse;
			glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, color);
		}

		if (currentMaterial.colorMaterial != Material::Diffuse &&
			currentMaterial.colorMaterial != Material::DiffuseAndAmbient)
		{
			color[0] = currentMaterial.diffuseColor.getRed() * inverse;
			color[1] = currentMaterial.diffuseColor.getGreen() * inverse;
			color[2] = currentMaterial.diffuseColor.getBlue() * inverse;
			color[3] = currentMaterial.diffuseColor.getAlpha() * inverse;
			glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, color);
		}

		if (currentMaterial.colorMaterial != Material::Emissive)
		{
			color[0] = currentMaterial.emissiveColor.getRed() * inverse;
			color[1] = currentMaterial.emissiveColor.getGreen() * inverse;
			color[2] = currentMaterial.emissiveColor.getBlue() * inverse;
			color[3] = currentMaterial.emissiveColor.getAlpha() * inverse;
			glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, color);
		}
	}

	if (shouldResetRenderStates ||
		lastMaterial.emissiveColor != currentMaterial.emissiveColor ||
		lastMaterial.shininess != currentMaterial.shininess ||
		lastMaterial.colorMaterial != currentMaterial.colorMaterial)
	{
		GLfloat color[4] = {0.0f, 0.0f, 0.0f, 1.0f};

		float inverse = 1.0f / 255.0f;

		glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, currentMaterial.shininess);

		if (currentMaterial.shininess != 0.0f &&
			currentMaterial.colorMaterial != Material::Specular)
		{
			color[0] = currentMaterial.specularColor.getRed() * inverse;
			color[1] = currentMaterial.specularColor.getGreen() * inverse;
			color[2] = currentMaterial.specularColor.getBlue() * inverse;
			color[3] = currentMaterial.specularColor.getAlpha() * inverse;
		}

		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, color);
	}

	for (unsigned i = 0; i < maxTextures; ++i)
	{
		if (!bindedTextures[i])
		{
			continue;
		}

		glActiveTexture(GL_TEXTURE0 + i);

		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,
			(currentMaterial.textureLayers[i].bilinearFilter ||
				currentMaterial.textureLayers[i].trilinearFilter) ?
					GL_LINEAR : GL_NEAREST);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
			(currentMaterial.textureLayers[i].bilinearFilter ||
				currentMaterial.textureLayers[i].trilinearFilter) ?
					GL_LINEAR : GL_NEAREST);
	}

	if (shouldResetRenderStates ||
		lastMaterial.smoothShading != currentMaterial.smoothShading)
	{
		glShadeModel(currentMaterial.smoothShading ? GL_SMOOTH : GL_FLAT);
	}

	if (shouldResetRenderStates ||
		lastMaterial.lighting != currentMaterial.lighting)
	{
		if (currentMaterial.lighting)
		{
			glEnable(GL_LIGHTING);
		}
		else
		{
			glDisable(GL_LIGHTING);
		}
	}

	if (shouldResetRenderStates ||
		lastMaterial.fogEnabled != currentMaterial.fogEnabled)
	{
		if (currentMaterial.fogEnabled)
		{
			glEnable(GL_FOG);
		}
		else
		{
			glDisable(GL_FOG);
		}
	}

	if (shouldResetRenderStates ||
		lastMaterial.normalizeNormals != currentMaterial.normalizeNormals)
	{
		if (currentMaterial.normalizeNormals)
		{
			glEnable(GL_NORMALIZE);
		}
		else
		{
			glDisable(GL_NORMALIZE);
		}
	}

	if (shouldResetRenderStates ||
		lastMaterial.wireframe != currentMaterial.wireframe)
	{
		glPolygonMode(GL_FRONT_AND_BACK,
			currentMaterial.wireframe ? GL_LINE : GL_FILL);
	}

	if (shouldResetRenderStates ||
		lastMaterial.backFaceCulling != currentMaterial.backFaceCulling ||
		lastMaterial.frontFaceCulling != currentMaterial.frontFaceCulling)
	{
		if (currentMaterial.backFaceCulling == true &&
			currentMaterial.frontFaceCulling == true)
		{
			glCullFace(GL_FRONT_AND_BACK);
			glEnable(GL_CULL_FACE);
		}
		else if (currentMaterial.backFaceCulling == true)
		{
			glCullFace(GL_BACK);
			glEnable(GL_CULL_FACE);
		}
		else if (currentMaterial.frontFaceCulling == true)
		{
			glCullFace(GL_FRONT);
			glEnable(GL_CULL_FACE);
		}
		else
		{
			glDisable(GL_CULL_FACE);
		}
	}

	if (shouldResetRenderStates ||
		lastMaterial.depthFunction != currentMaterial.depthFunction)
	{
		if (currentMaterial.depthFunction != Material::Disabled)
		{
			glEnable(GL_DEPTH_TEST);

			switch (currentMaterial.depthFunction)
			{
				case Material::LessEqual:
				{
					glDepthFunc(GL_LEQUAL);
					break;
				}
				case Material::Equal:
				{
					glDepthFunc(GL_EQUAL);
					break;
				}
				case Material::Less:
				{
					glDepthFunc(GL_LESS);
					break;
				}
				case Material::NotEqual:
				{
					glDepthFunc(GL_NOTEQUAL);
					break;
				}
				case Material::GreaterEqual:
				{
					glDepthFunc(GL_GEQUAL);
					break;
				}
				case Material::Greater:
				{
					glDepthFunc(GL_GREATER);
					break;
				}
				case Material::Always:
				{
					glDepthFunc(GL_ALWAYS);
					break;
				}
				case Material::Never:
				{
					glDepthFunc(GL_NEVER);
					break;
				}
				default:
				{
					break;
				}
			}
		}
		else
		{
			glDisable(GL_DEPTH_TEST);
		}
	}

	glDepthMask(currentMaterial.zWriteEnabled);

	if (currentMaterial.blendOperation == Material::NoBlend)
	{
		glDisable(GL_BLEND);
	}
	else
	{
		glEnable(GL_BLEND);
	}

	// TODO: Anti-Aliasing

	// TODO: Color mask
}

#if 0
void OpenGLDevice::setBasicRenderStates(const Material& currentMaterial,
	const Material& lastMaterial, bool shouldResetRenderStates)
{
	if (currentMaterial.zWriteEnabled)
	{
		switch (currentMaterial.zWriteFineControl)
		{
			case Material::OnlyNonTransparent:
			{
				glDepthMask(!currentMaterial.isTransparent());
			}
			case Material::ZBufferFlag:
			{
				glDepthMask(true);
				break;
			}
		}
	}
	else
	{
		glDepthMask(false);
	}

	if (currentMaterial.blendOperation == Material::NoBlend)
	{
		glDisable(GL_BLEND);
	}
	else
	{
		glEnable(GL_BLEND);
	}

	setTextureRenderStates(currentMaterial, shouldResetRenderStates);
}
#endif

void OpenGLDevice::toGLTextureMatrix(GLfloat* glMatrix,
	const math::Matrix4& matrix)
{
	glMatrix[0] = matrix[0];
	glMatrix[1] = matrix[1];
	glMatrix[2] = 0.0f;
	glMatrix[3] = 0.0f;

	glMatrix[4] = matrix[4];
	glMatrix[5] = matrix[5];
	glMatrix[6] = 0.0f;
	glMatrix[7] = 0.0f;

	glMatrix[8] = 0.0f;
	glMatrix[9] = 0.0f;
	glMatrix[10] = 1.0f;
	glMatrix[11] = 0.0f;

	glMatrix[12] = matrix[8];
	glMatrix[13] = matrix[9];
	glMatrix[14] = 0.0f;
	glMatrix[15] = 1.0f;
}

void OpenGLDevice::setTextureRenderStates(const Material& currentMaterial,
	bool shouldResetRenderStates)
{
	// TODO

	// THIS FUNCTION IS COMPLETELY INCOMPLETE :D
	// MANY FEATURES (MOST OF THEM, REALLY) ARE MISSING

	for (signed i = maxTextures - 1; i >= 0; --i)
	{
		Texture* tempTexture = getBindedTexture(i);
		if (tempTexture == nullptr)
		{
			continue;
		}

		glActiveTexture(GL_TEXTURE0 + i);

		glMatrixMode(GL_TEXTURE);

		if (matrices[Texture0 + i].isIdentity())
		{
			glLoadIdentity();
		}
		else
		{
			GLfloat glMatrix[16];
			toGLTextureMatrix(glMatrix, matrices[Texture0 + i]);
		}

		if (shouldResetRenderStates /* || check LOD */)
		{
			if (false) //(currentMaterial.textureLayers[i].lodBias != 0)
			{
				//float clamped = math::clamp(currentMaterial.textureLayers[i].lodBias * 0.125f, -max);
			}
			else
			{
				glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_LOD_BIAS, 0.0f);
			}
		}

		if (shouldResetRenderStates /* || check bilinear filter */)
		{

		}

		if (currentMaterial.useMipMaps && false /* tempTexture->hasMipMaps() */)
		{

		}
		else
		{
			if (shouldResetRenderStates /* || bilinear filter */)
			{

			}
		}
	}

	glActiveTexture(GL_TEXTURE0);
}

void OpenGLDevice::onSetMaterial()
{
	switch (currentMaterial.materialType)
	{
		case Material::Solid:
		{
			disableTextures(1);
			setBasicRenderStates(currentMaterial, lastMaterial,
				shouldResetRenderStates);

			if (shouldResetRenderStates || (lastMaterial != currentMaterial))
			{
				glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
			}

			break;
		}
		case Material::LightMap:
		case Material::DoubleLightMap:
		case Material::LightMapLighting:
		case Material::DoubleLightMapLighting:
		{
			disableTextures(2);
			setBasicRenderStates(currentMaterial, lastMaterial,
				shouldResetRenderStates);

			if (shouldResetRenderStates ||
				(lastMaterial.materialType != currentMaterial.materialType))
			{
				switch (currentMaterial.materialType)
				{
					case Material::LightMapLighting:
					case Material::DoubleLightMapLighting:
					{
						glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE,
							GL_MODULATE);
						break;
					}
					case Material::LightMap:
					case Material::DoubleLightMap:
					{
						glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE,
							GL_REPLACE);
						break;
					}
					default:
					{
						break;
					}
				}
/*
				glActiveTexture(GL_TEXTURE1);

				glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_COMBINE_ARB);

				glTexEnvi(GL_TEXTURE_ENV, GL_COMBINE_RGB_ARB, GL_MODULATE);

				glTexEnvi(GL_TEXTURE_ENV, GL_SOURCE0_RGB_ARB, GL_TEXTURE);
				glTexEnvi(GL_TEXTURE_ENV, GL_SOURCE1_RGB_ARB, GL_PREVIOUS_ARB);
				glTexEnvf(GL_TEXTURE_ENV, GL_COMBINE_ALPHA_ARB, GL_MODULATE);
				glTexEnvi(GL_TEXTURE_ENV, GL_SOURCE0_ALPHA_ARB, GL_TEXTURE);
				glTexEnvi(GL_TEXTURE_ENV, GL_SOURCE1_ALPHA_ARB,
					GL_PREVIOUS_ARB);

				switch (currentMaterial.materialType)
				{
					case Material::DoubleLightMap:
					case Material::DoubleLightMapLighting:
					{
						glTexEnvf(GL_TEXTURE_ENV, GL_RGB_SCALE_ARB, 2.0f);
						break;
					}
					case Material::LightMap:
					case Material::LightMapLighting:
					default:
					{
						glTexEnvf(GL_TEXTURE_ENV, GL_RGB_SCALE_ARB, 1.0f);
						break;
					}
				}

				glActiveTexture(GL_TEXTURE0);
*/
			}

			break;
		}
		case Material::Reflection:
		{
			break;
		}
		case Material::SemiTransparent:
		{
			break;
		}
		case Material::SharpTransparent:
		{
			disableTextures(1);
			setBasicRenderStates(currentMaterial, lastMaterial,
				shouldResetRenderStates);

			glEnable(GL_ALPHA_TEST);
			glAlphaFunc(GL_GREATER, 0.5f);

			if (shouldResetRenderStates || (lastMaterial != currentMaterial))
			{
				glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
			}

			break;
		}
		case Material::DetailMap:
		{
			disableTextures(2);
			setBasicRenderStates(currentMaterial, lastMaterial,
				shouldResetRenderStates);

			glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

			glActiveTexture(GL_TEXTURE1);

			glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_COMBINE);

			glTexEnvi(GL_TEXTURE_ENV, GL_COMBINE_RGB, GL_MODULATE);
			glTexEnvi(GL_TEXTURE_ENV, GL_SRC0_RGB, GL_TEXTURE);
			glTexEnvi(GL_TEXTURE_ENV, GL_SRC1_RGB, GL_PREVIOUS);

			glTexEnvf(GL_TEXTURE_ENV, GL_COMBINE_ALPHA, GL_MODULATE);
			glTexEnvi(GL_TEXTURE_ENV, GL_SRC0_ALPHA, GL_TEXTURE);
			glTexEnvi(GL_TEXTURE_ENV, GL_SRC1_ALPHA, GL_PREVIOUS);

			glTexEnvf(GL_TEXTURE_ENV, GL_RGB_SCALE, 2.0f);

			glActiveTexture(GL_TEXTURE0);

			break;
		}
		case Material::ColorDetailMap:
		{
			disableTextures(1);
			setBasicRenderStates(currentMaterial, lastMaterial,
				shouldResetRenderStates);

			glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

			glActiveTexture(GL_TEXTURE0);

			glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_COMBINE);

			glTexEnvi(GL_TEXTURE_ENV, GL_COMBINE_RGB, GL_MODULATE);
			glTexEnvi(GL_TEXTURE_ENV, GL_SRC0_RGB, GL_TEXTURE);
			glTexEnvi(GL_TEXTURE_ENV, GL_SRC1_RGB, GL_PREVIOUS);

			glTexEnvf(GL_TEXTURE_ENV, GL_COMBINE_ALPHA, GL_MODULATE);
			glTexEnvi(GL_TEXTURE_ENV, GL_SRC0_ALPHA, GL_TEXTURE);
			glTexEnvi(GL_TEXTURE_ENV, GL_SRC1_ALPHA, GL_PREVIOUS);

			glTexEnvf(GL_TEXTURE_ENV, GL_RGB_SCALE, 2.0f);

			break;
		}
		default:
		{
			break;
		}
	}
}

void OpenGLDevice::onUnsetMaterial()
{
	switch (lastMaterial.materialType)
	{
		case Material::Solid:
		case Material::LightMap:
		case Material::DoubleLightMap:
		case Material::LightMapLighting:
		case Material::DoubleLightMapLighting:
		case Material::Reflection:
		case Material::SemiTransparent:
		{
			break;
		}
		case Material::SharpTransparent:
		{
			glDisable(GL_ALPHA_TEST);

			break;
		}
		case Material::DetailMap:
		{
			glActiveTexture(GL_TEXTURE1);

			glTexEnvf(GL_TEXTURE_ENV, GL_RGB_SCALE, 1.0f);

			glActiveTexture(GL_TEXTURE0);

			break;
		}
		case Material::ColorDetailMap:
		{
			glTexEnvf(GL_TEXTURE_ENV, GL_RGB_SCALE, 1.0f);

			break;
		}
		default:
		{
			break;
		}
	}
}

Texture* OpenGLDevice::getBindedTexture(unsigned onLayer)
{
	assert(onLayer < maxTextures);

	return bindedTextures[onLayer];
}

Texture* OpenGLDevice::createTextureFromImage(const std::string& name,
	const Image& image)
{
	math::Vector2u imageSize = image.getSize();
	if (imageSize.x == 0 ||
		imageSize.y == 0)
	{
		std::cout << "Incorrect texture size: (" << imageSize.x << "; " <<
			imageSize.y << ")" << std::endl;

		return nullptr;	
	}

	Texture* texture = new Texture(name, image, *this);
	if (texture != nullptr)
	{
		TextureHolder holder;
		holder.texture = texture;
		holder.referenceCount = 1;

		loadedTextures[name] = holder;
	}

	return texture;
}

} // namespace device

} // namespace gfx
