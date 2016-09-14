#include "OpenGLDevice.h"

#include <cmath>
#include <iostream>

#include <SFML/OpenGL.hpp>

#include "common/math/MathUtility.h"

namespace gfx
{

namespace device
{

OpenGLDevice::OpenGLDevice() :
	super(),
	clearColor(0, 0, 0),
	matrices(),
	quad2DVertices(),
	quad2DIndices{0, 1, 2, 3},
	currentRenderMode(RenderModeNone),
	shouldResetRenderStates(false),
	transformation3DChanged(false),
	currentMaterial(),
	lastMaterial(),
	screenSize(800, 600),
	clientStateVertex(false),
	clientStateNormal(false),
	clientStateColor(false),
	clientStateTexCoord0(false)
{
	deviceName = "OpenGL";
}

OpenGLDevice::~OpenGLDevice()
{}

bool OpenGLDevice::init()
{
	setClearColor(clearColor);

	for (unsigned i = 0; i < TransformationCount; ++i)
	{
		setTransform(static_cast<TransformationState>(i), math::Matrix4());
	}

	setAmbientLight(Color(0, 0, 0, 0));

	glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, 1);

	glClearDepth(1.0);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
	glHint(GL_POINT_SMOOTH_HINT, GL_FASTEST);

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

	return true;
}

void OpenGLDevice::beginScene()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
}

void OpenGLDevice::endScene()
{}

void OpenGLDevice::setClientState(bool vertex, bool normal, bool color,
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

void OpenGLDevice::set3DRenderMode()
{
	return;
	if (currentRenderMode != RenderMode3D)
	{
		glDisable(GL_BLEND);
		glDisable(GL_ALPHA_TEST);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glMatrixMode(GL_MODELVIEW);
		//glLoadMatrixf(
		//	(matrices[TransformationView] *
		//		matrices[TransformationWorld]).pointer());

		glLoadMatrixf(matrices[TransformationView].pointer());

		glMultMatrixf(matrices[TransformationWorld].pointer());

		glMatrixMode(GL_PROJECTION);
		glLoadMatrixf(matrices[TransformationProjection].pointer());

		shouldResetRenderStates = true;
	}

	//if (shouldResetRenderStates || lastMaterial != currentMaterial)
	{
		lastMaterial = currentMaterial;
		shouldResetRenderStates = false;
	}

	currentRenderMode = RenderMode3D;
}

void OpenGLDevice::set2DRenderMode(bool transparent, bool textured, bool alphaChannel)
{
	if (currentRenderMode != RenderMode2D)
	{
		if (currentRenderMode == RenderMode3D || transformation3DChanged)
		{

		}
		if (transformation3DChanged)
		{
			glMatrixMode(GL_PROJECTION);

			math::Vector2u renderTargetSize = screenSize;
			math::Matrix4 matrix;
			matrix.buildProjectionMatrixOrtho(
				static_cast<float>(renderTargetSize.x),
				-(static_cast<float>(renderTargetSize.y)), -1.0f, 1.0f);
			matrix.setTranslation(math::Vector3f(-1.0f, 1.0f, 0.0f));
			glLoadMatrixf(matrix.pointer());

			glMatrixMode(GL_MODELVIEW);
			glLoadIdentity();

			glTranslatef(0.375f, 0.375f, 0.0f);

			transformation3DChanged = false;
		}

		//if (!overrideMaterial2DEnabled)
		{

		}

		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}

	//if (overrideMaterial2DEnabled)
	//{
	//
	//}

	alphaChannel &= textured;

	if (alphaChannel || transparent)
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

	}

	currentRenderMode = RenderMode2D;
}

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

const math::Matrix4& OpenGLDevice::getTransform(TransformationState state) const
{
	return matrices[state];
}

void OpenGLDevice::setTransform(TransformationState state,
	const math::Matrix4& matrix)
{
	matrices[state] = matrix;
	transformation3DChanged = true;

	switch (state)
	{
		case TransformationView:
		case TransformationWorld:
		{
			glMatrixMode(GL_MODELVIEW);

			glLoadMatrixf(matrices[TransformationView].pointer());

			glMultMatrixf(matrices[TransformationWorld].pointer());
			break;
		}
		case TransformationProjection:
		{
			glMatrixMode(GL_PROJECTION);
			glLoadMatrixf(matrix.pointer());
		}
		default:
		{
			break;
		}
	}
}

Texture* OpenGLDevice::loadTextureFromFile(const std::string& name)
{
	return nullptr;
}

Texture* OpenGLDevice::loadTextureFromImage(const std::string& name,
	const Image& image)
{
	return nullptr;
}

void OpenGLDevice::drawPixel(unsigned x, unsigned y, const Color& color)
{
	math::Vector2u renderTargetSize = screenSize;
	if (x > renderTargetSize.x || y > renderTargetSize.y)
	{
		return;
	}

	//disableTextures();
	set2DRenderMode(color.getAlpha() < 255, false, false);

	quad2DVertices[0].color = color;
	quad2DVertices[0].position = math::Vector3f(static_cast<float>(x),
		static_cast<float>(x), 0.0f);

	setClientState(true, false, true, false);

	glVertexPointer(2, GL_FLOAT, sizeof(Vertex3D),
		&((static_cast<const Vertex3D*>(quad2DVertices))[0].position));

	glColorPointer(4, GL_UNSIGNED_BYTE, sizeof(Vertex3D),
		&((static_cast<const Vertex3D*>(quad2DVertices))[0].color));

	glDrawArrays(GL_POINTS, 0, 1);
}

void OpenGLDevice::draw2DImage(const Texture* texture,
	const math::Vector2i& destination)
{
	if (!texture)
	{
		return;
	}

	draw2DImage(texture, destination,
		math::Recti(math::Vector2i(0, 0), texture->getOriginalSize()));
}

void OpenGLDevice::draw2DImage(const Texture* texture,
	const math::Vector2i& destination, const math::Recti& sourceRect,
	const math::Recti* clipRect, const Color& color, bool useAlphaChannel)
{
	if (!texture)
	{
		return;
	}

	if (!sourceRect.isValid())
	{
		return;
	}

	
}

void OpenGLDevice::draw2DImage(const Texture* texture,
	const math::Recti& destination, const math::Recti& sourceRect,
	const math::Recti* clipRect, const Color* colors, bool useAlphaChannel)
{

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
		//disableTextures();
		set2DRenderMode(color.getAlpha() < 255, false, false);

		quad2DVertices[0].color = color;
		quad2DVertices[1].color = color;

		quad2DVertices[0].position = math::Vector3f(static_cast<float>(start.x),
			static_cast<float>(start.y), 0.0f);
		quad2DVertices[1].position = math::Vector3f(static_cast<float>(end.x),
			static_cast<float>(end.y), 0.0f);

		setClientState(true, false, true, false);

		glVertexPointer(2, GL_FLOAT, sizeof(Vertex3D),
			&((static_cast<const Vertex3D*>(quad2DVertices))[0].position));

		glColorPointer(4, GL_UNSIGNED_BYTE, sizeof(Vertex3D),
			&((static_cast<const Vertex3D*>(quad2DVertices))[0].color));

		glDrawElements(GL_LINES, 2, GL_UNSIGNED_SHORT, quad2DIndices);
	}
}

void OpenGLDevice::draw2DPolygon(const math::Vector2i& center, float radius,
	const Color& color, unsigned vertexCount)
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

void OpenGLDevice::draw2DRectangle(const Color& color,
	const math::Recti& position, const math::Recti* clipRect)
{
	math::Recti clipped = position;
	if (clipRect != nullptr)
	{
		clipped.clipAgainst(*clipRect);
	}
	if (!clipped.isValid())
	{
		return;
	}

	//disableTextures();
	set2DRenderMode(color.getAlpha() < 255, false, false);

	glColor4ub(color.getRed(), color.getGreen(), color.getBlue(),
		color.getAlpha());
	glRectf(static_cast<GLfloat>(position.upperLeft.x),
		static_cast<GLfloat>(position.upperLeft.y),
		static_cast<GLfloat>(position.lowerRight.x),
		static_cast<GLfloat>(position.lowerRight.y));
}

void OpenGLDevice::draw2DRectangle(const math::Recti& position,
	const Color& colorLeftUp, const Color& colorRightUp,
	const Color& colorLeftDown, const Color& colorRightDown,
	const math::Recti* clipRect)
{
	math::Recti clipped = position;
	if (clipRect != nullptr)
	{
		clipped.clipAgainst(*clipRect);
	}
	if (!clipped.isValid())
	{
		return;
	}

	//disableTextures();
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

	setClientState(true, false, true, false);

	glVertexPointer(2, GL_FLOAT, sizeof(Vertex3D),
		&((static_cast<const Vertex3D*>(quad2DVertices))[0].position));

	glColorPointer(4, GL_UNSIGNED_BYTE, sizeof(Vertex3D),
		&((static_cast<const Vertex3D*>(quad2DVertices))[0].color));

	glDrawElements(GL_TRIANGLE_FAN, 4, GL_UNSIGNED_SHORT, quad2DIndices);
}

void OpenGLDevice::draw2DRectangleOutline(const math::Recti& position,
	const Color& color)
{
	draw2DLine(position.upperLeft,
		math::Vector2i(position.lowerRight.x, position.upperLeft.y), color);
	draw2DLine(math::Vector2i(position.lowerRight.x, position.upperLeft.y),
		position.lowerRight, color);
	draw2DLine(position.lowerRight,
		math::Vector2i(position.upperLeft.x, position.lowerRight.y), color);
	draw2DLine(math::Vector2i(position.upperLeft.x, position.lowerRight.y),
		position.upperLeft, color);
}

void OpenGLDevice::setAmbientLight(const Color& color)
{
	GLfloat data[4] = {color.getClampRed(), color.getClampGreen(),
		color.getClampBlue(), color.getClampAlpha()};
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, data);
}

void OpenGLDevice::onResize(const math::Vector2u& size)
{
	screenSize = size;

	glViewport(0, 0, size.x, size.y);

	transformation3DChanged = true;
}

} // namespace device

} // namespace gfx
