#pragma once

#include <cstdint>
#include <map>

#include <SFML/OpenGL.hpp>

#include "Device.h"

namespace gfx
{

namespace device
{

class OpenGLDevice : public Device
{
	typedef Device super;

	friend class gfx::Texture;
public:
	OpenGLDevice();
	~OpenGLDevice();

	bool init() override;

	// Device info

	math::Vector2u getRenderTargetSize() const override;

	// Data management

	Texture* getTexture(const std::string& name) const override;
	Texture* loadTextureFromFile(const std::string& name,
		bool applyColorKey = false) override;

	void unloadAllTextures() override;

	// Rendering utilities

	void beginScene() override;
	void endScene() override;

	void setClearColor(const Color& color) override;

	void clearZBuffer() override;

	// Rendering properties

	void setTransform(TransformType transformType,
		const math::Matrix4& transform) override;
	void resetTransforms() override;
	void setMaterial(const Material& material) override;

	// 3D Rendering

	void draw3DLine(const math::Vector3f& start, const math::Vector3f& end,
		const Color& color = Color(255, 255, 255, 255)) override;

	void drawIndexedPrimitiveList(const Vertex3D* vertices,
		uint32_t vertexCount, const uint16_t* indices, uint32_t primitiveCount)
		override;

	// 2D Rendering

	void drawPixel(unsigned x, unsigned y,
		const Color& pixelColor = Color(255, 255, 255, 255)) override;

	void draw2DImage(Texture* texture, const math::Vector2i& imageDestination)
		override;

	void draw2DImage(Texture* texture, const math::Vector2i& imageDestination,
		const math::Recti& sourceRectangle,
		const Color& color = Color(255, 255, 255, 255),
		const math::Recti* clippingRectangle = nullptr,
		bool useAlphaChannel = true) override;

	void draw2DImage(Texture* texture, const math::Recti& destinationRectangle)
		override;

	void draw2DImage(Texture* texture,
		const math::Recti& destinationRectangle,
		const math::Recti& sourceRectangle, const Color* colors = nullptr,
		const math::Recti* clippingRectangle = nullptr,
		bool useAlphaChannel = true) override;

	void draw2DLine(const math::Vector2i& start, const math::Vector2i& end,
		const Color& color = Color(255, 255, 255, 255)) override;

	void draw2DPolygon(const math::Vector2i& center, float radius,
		unsigned vertexCount = 10,
		const Color& color = Color(255, 255, 255, 255)) override;

	void draw2DRectangle(const math::Recti& destinationRectangle,
		const Color& color = Color(255, 255, 255, 255),
		const math::Recti* clippingRectangle = nullptr) override;

	void draw2DRectangle(const math::Recti& destinationRectangle,
		const Color& colorLeftUp, const Color& colorRightUp,
		const Color& colorLeftDown, const Color& colorRightDown,
		const math::Recti* clippingRectangle = nullptr) override;

	void draw2DRectangleOutline(const math::Recti& destinationRectangle,
		const Color& color = Color(255, 255, 255, 255)) override;

	/*
		Utility events
	*/

	void onResize(const math::Vector2u& size) override;
private:

	/*
		Private utility functions
	*/

	Texture* findTexture(const std::string& name) const;

	void bindTexture(unsigned textureLayer, Texture* texture);

	void disableTextures(unsigned fromLayer = 0);

	void setClientStates(bool vertex, bool normal, bool color, bool texCoord0);

	void set2DRenderMode(bool transparent, bool textured, bool alphaChannel);
	void set3DRenderMode();

	Texture* getBindedTexture(unsigned onLayer);

	/*
		Material utilities
	*/

	void onSetMaterial();
	void onUnsetMaterial();

	void setBasicRenderStates(const Material& currentMaterial,
		const Material& lastMaterial, bool shouldResetRenderStates);
	void setTextureRenderStates(const Material& currentMaterial,
		bool shouldResetRenderStates);

	void toGLTextureMatrix(GLfloat* glMatrix, const math::Matrix4& matrix);
private:
	Color clearColor;

	std::map<std::string, Texture*> loadedTextures;

	math::Matrix4 matrices[TransformCount];

	bool transformationChanged;

	math::Vector2u screenSize;

	Vertex3D quad2DVertices[4];
	const uint16_t quad2DIndices[4];

	Texture* bindedTextures[maxTextures];

	bool clientStateVertex;
	bool clientStateNormal;
	bool clientStateColor;
	bool clientStateTexCoord0;

	enum RenderMode
	{
		RenderModeNone,
		RenderMode3D,
		RenderMode2D
	} currentRenderMode;

	Material currentMaterial; // current !3D! material (rename?)
	Material lastMaterial;
	Material material2D;

	bool shouldResetRenderStates;
};

} // namespace device

} // namespace gfx
