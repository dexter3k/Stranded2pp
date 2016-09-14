#pragma once

#include <string>

#include "../Color.h"
#include "../Image.h"
#include "../Light.h"
#include "../Material.h"
#include "../Texture.h"
#include "../Vertex3D.h"

#include "common/math/Matrix4.h"
#include "common/math/Rect.h"
#include "common/math/Vector2.h"

namespace gfx
{

namespace device
{

class Device
{
public:
	enum TransformationState
	{
		TransformationView,
		TransformationWorld,
		TransformationProjection,
		TransformationTexture0,
		TransformationTexture1,
		TransformationTexture2,
		TransformationTexture3,

		TransformationCount
	};
public:
	Device();
	virtual ~Device();

	virtual bool init() = 0;

	virtual void beginScene() = 0;
	virtual void endScene() = 0;

	virtual void setClearColor(const Color& color) = 0;

	virtual void clearZBuffer() = 0;

	virtual const math::Matrix4& getTransform(TransformationState state) const
		= 0;

	virtual void setTransform(TransformationState state,
		const math::Matrix4& matrix) = 0;

	virtual Texture* getTexture(const std::string& name) const = 0;
	virtual Texture* loadTextureFromFile(const std::string& name) = 0;

	virtual void unloadAllTextures() = 0;

	virtual void drawPixel(unsigned x, unsigned y, const Color& color) = 0;

	virtual void draw2DImage(const Texture* texture,
		const math::Vector2i& destination) = 0;

	virtual void draw2DImage(const Texture* texture,
		const math::Vector2i& destination, const math::Recti& sourceRect,
		const math::Recti* clipRect = 0,
		const Color& color = Color(255, 255, 255, 255),
		bool useAlphaChannel = false) = 0;

	virtual void draw2DImage(const Texture* texture,
		const math::Recti& destination, const math::Recti& sourceRect,
		const math::Recti* clipRect = nullptr,
		const Color* colors = nullptr, bool useAlphaChannel = false) = 0;

	virtual void draw2DLine(const math::Vector2i& start,
		const math::Vector2i& end,
		const Color& color = Color(255, 255, 255, 255)) = 0;

	virtual void draw2DPolygon(const math::Vector2i& center, float radius,
		const Color& color = Color(100, 255, 255, 255),
		unsigned vertexCount = 10) = 0;

	virtual void draw2DRectangle(const Color& color,
		const math::Recti& position, const math::Recti* clipRect = nullptr) = 0;

	virtual void draw2DRectangle(const math::Recti& position,
		const Color& colorLeftUp, const Color& colorRightUp,
		const Color& colorLeftDown, const Color& colorRightDown,
		const math::Recti* clipRect = nullptr) = 0;

	virtual void draw2DRectangleOutline(const math::Recti& position,
		const Color& color = Color(255, 255, 255, 255)) = 0;

	virtual void setAmbientLight(const Color& color) = 0;

	virtual void onResize(const math::Vector2u& size) = 0;
protected:
	std::string deviceName;
};

} // namespace device

} // namespace gfx
