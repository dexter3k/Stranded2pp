#pragma once

#include <cstdint>
#include <map>

#include <SFML/OpenGL.hpp>

#include "Device.h"
#include "../Material.h"
#include "../Vertex3D.h"

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


	// Try to grab texture. If texture is found, increases grab count and
	// return it. Else just return nullptr
	Texture* grabTexture(const std::string& name) override;
	
	// Release texture. If texture is found, decrease grab count and if grab
	// count is zero, then delete texture. If no texture is found, then
	// behaviour is undefined
	void releaseTexture(const std::string& name) override;


	// Load texture from file and set grab count to one
	// Will set to default pink rgb(127, 31, 127) texture, is not found and
	// loadEmptyIfMissing equals true. Will also apply color key if needed.
	// Returns pointer to texture on success or nullptr on error
	Texture* loadTextureFromFile(const std::string& name,
		bool loadEmptyIfMissing = false, bool applyColorKey = false,
		const Color& colorKey = Color(255, 0, 255)) override;

	// Load texture from image and set grab count to one
	// Returns pointer to texture on success or nullptr on error
	Texture* loadTextureFromImage(const std::string& name, const Image& image)
		override;


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

	void drawIndexedPrimitiveList(const void* vertices, uint32_t vertexCount,
		const void* indices, uint32_t primitiveCount,
		Vertex3D::VertexType vertexType = Vertex3D::Standard,
		IndexSize indexSize = Index32Bit) override;


	// Mesh buffers


	void drawMeshBuffer(const MeshBuffer* meshBuffer) override;


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
	struct TextureHolder
	{
		Texture* texture;
		unsigned referenceCount;
	};
private:

	/*
		Private utility functions
	*/

	TextureHolder findTexture(const std::string& name) const;

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
	Texture* createTextureFromImage(const std::string& name,
		const Image& image);
private:
	Color clearColor;

	std::map<std::string, TextureHolder> loadedTextures;

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
