#pragma once

#include <cstdint>

#include "Device.h"

namespace gfx
{

namespace device
{

class OpenGLDevice : public Device
{
	typedef Device super;
public:
	OpenGLDevice();
	~OpenGLDevice();

	bool init() override;

	void beginScene() override;
	void endScene() override;

	void setClientState(bool vertex, bool normal, bool color, bool texCoord0);
	void set3DRenderMode();
	void set2DRenderMode(bool transparent, bool textured, bool alphaChannel);

	void setClearColor(const Color& color) override;

	void clearZBuffer() override;

	const math::Matrix4& getTransform(TransformationState state) const override;

	void setTransform(TransformationState state, const math::Matrix4& matrix)
		override;

	void drawPixel(unsigned x, unsigned y, const Color& color) override;

	void draw2DImage(const Texture& texture,
		const math::Vector2i& destination) override;

	void draw2DImage(const Texture& texture,
		const math::Vector2i& destination, const math::Recti& sourceRect,
		const math::Recti* clipRect = 0,
		const Color& color = Color(255, 255, 255, 255),
		bool useAlphaChannel = false) override;

	void draw2DImage(const Texture& texture,
		const math::Recti& destination, const math::Recti& sourceRect,
		const math::Recti* clipRect = nullptr,
		const Color* colors = nullptr, bool useAlphaChannel = false) override;

	void draw2DLine(const math::Vector2i& start,
		const math::Vector2i& end,
		const Color& color = Color(255, 255, 255, 255)) override;

	void draw2DPolygon(const math::Vector2i& center, float radius,
		const Color& color = Color(100, 255, 255, 255),
		unsigned vertexCount = 10) override;

	void draw2DRectangle(const Color& color,
		const math::Recti& position, const math::Recti* clipRect = nullptr)
		override;

	void draw2DRectangle(const math::Recti& position,
		const Color& colorLeftUp, const Color& colorRightUp,
		const Color& colorLeftDown, const Color& colorRightDown,
		const math::Recti* clipRect = nullptr) override;

	void draw2DRectangleOutline(const math::Recti& position,
		const Color& color = Color(255, 255, 255, 255)) override;

	void setAmbientLight(const Color& color) override;

	void onResize(const math::Vector2u& size) override;
private:
	Color clearColor;

	math::Matrix4 matrices[super::TransformationCount];

	// Prebuilt 2D quad (2 tris)
	Vertex3D quad2DVertices[4];
	const uint16_t quad2DIndices[4];

	enum RenderMode
	{
		RenderModeNone = 0,
		RenderMode2D,
		RenderMode3D
	} currentRenderMode;

	bool shouldResetRenderStates;
	bool transformation3DChanged;

	Material currentMaterial;
	Material lastMaterial;

	math::Vector2u screenSize;

	bool clientStateVertex;
	bool clientStateNormal;
	bool clientStateColor;
	bool clientStateTexCoord0;
};

} // namespace device

} // namespace gfx
