#pragma once

#include <string>

#include "../Color.h"
#include "../FontType.h"
#include "../IndexSize.h"
#include "../TextStyle.h"
#include "../Vertex3D.h"

#include "math/Matrix4.h"
#include "math/Rect.h"
#include "math/Vector2.h"
#include "math/Vector3.h"

namespace gfx
{

class BmpFont;
class Image;
class Material;
class MeshBuffer;
class Texture;
class Vertex3D;

namespace device
{

class Device
{
public:
	enum TransformType
	{
		Projection = 0,
		Model = 1,
		View,
		Texture0,
		Texture1,

		TransformCount
	};

	static const unsigned maxTextures = 2;
public:
	Device();
	virtual ~Device() = default;


	// Device info


	virtual math::Vector2u getRenderTargetSize() const = 0;


	// Data management


	// Try to grab texture. If texture is found, increases grab count and
	// return it. Else just return nullptr
	virtual Texture* grabTexture(std::string const & name) = 0;
	
	// Release texture. If texture is found, decrease grab count and if grab
	// count is zero, then delete texture. If no texture is found, then
	// behaviour is undefined
	virtual void releaseTexture(std::string const & name) = 0;


	// Load texture from file and set grab count to one
	// Will set to default pink rgb(127, 31, 127) texture, is not found and
	// loadEmptyIfMissing equals true. Will also apply color key if needed.
	// Returns pointer to texture on success or nullptr on error
	virtual Texture* loadTextureFromFile(const std::string& name,
		bool loadEmptyIfMissing = false, bool applyColorKey = false,
		const Color& colorKey = Color(255, 0, 255)) = 0;

	// Load texture from image and set grab count to one
	// Returns pointer to texture on success or nullptr on error
	virtual Texture* loadTextureFromImage(const std::string& name,
		const Image& image) = 0;


	// Rendering utilities


	virtual void beginScene() = 0;
	virtual void endScene() = 0;

	virtual void setClearColor(const Color& color) = 0;

	virtual void clearZBuffer() = 0;


	// Rendering properties


	virtual void setTransform(TransformType transformType,
		const math::Matrix4& transform) = 0;
	virtual void resetTransforms() = 0;
	virtual void setMaterial(const Material& material) = 0;


	// 3D Drawing


	virtual void draw3DLine(const math::Vector3f& start,
		const math::Vector3f& end,
		const Color& color = Color(255, 255, 255, 255)) = 0;

	virtual void drawIndexedPrimitiveList(const void* vertices,
		uint32_t vertexCount, const void* indices, uint32_t primitiveCount,
		Vertex3D::VertexType vertexType = Vertex3D::Standard,
		IndexSize indexSize = Index32Bit) = 0;


	// Mesh buffers


	virtual void drawMeshBuffer(const MeshBuffer* meshBuffer) = 0;


	// 2D Text Drawing


	virtual void drawText(BmpFont const & font, std::string const & text,
		math::Vector2i const & position,
		math::Recti * clippingRectangle = nullptr) = 0;


	// 2D Drawing


	virtual void drawPixel(unsigned x, unsigned y,
		const Color& pixelColor = Color(255, 255, 255, 255)) = 0;


	virtual void draw2DImage(Texture* texture,
		const math::Vector2i& imageDestination) = 0;

	virtual void draw2DImage(Texture* texture,
		const math::Vector2i& imageDestination,
		const math::Recti& sourceRectangle,
		const Color& color = Color(255, 255, 255, 255),
		const math::Recti* clippingRectangle = nullptr,
		bool useAlphaChannel = true) = 0;

	virtual void draw2DImage(Texture* texture,
		const math::Recti& destinationRectangle) = 0;

	virtual void draw2DImage(Texture* texture,
		const math::Recti& destinationRectangle,
		const math::Recti& sourceRectangle, const Color* colors = nullptr,
		const math::Recti* clippingRectangle = nullptr,
		bool useAlphaChannel = true) = 0;


	virtual void draw2DLine(const math::Vector2i& start,
		const math::Vector2i& end,
		const Color& color = Color(255, 255, 255, 255)) = 0;

	virtual void draw2DPolygon(const math::Vector2i& center, float radius,
		unsigned vertexCount = 10,
		const Color& color = Color(255, 255, 255, 255)) = 0;

	virtual void draw2DRectangle(const math::Recti& destinationRectangle,
		const Color& color = Color(255, 255, 255, 255),
		const math::Recti* clippingRectangle = nullptr) = 0;

	virtual void draw2DRectangle(const math::Recti& destinationRectangle,
		const Color& colorLeftUp, const Color& colorRightUp,
		const Color& colorLeftDown, const Color& colorRightDown,
		const math::Recti* clippingRectangle = nullptr) = 0;

	virtual void draw2DRectangleOutline(const math::Recti& destinationRectangle,
		const Color& color = Color(255, 255, 255, 255)) = 0;


	// Utility events


	virtual void onResize(math::Vector2u size) = 0;
protected:
	std::string deviceName;
};

} // namespace device

} // namespace gfx
