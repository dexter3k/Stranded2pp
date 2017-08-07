#pragma once

#include <iostream>
#include <vector>

#include "Vertex3D.h"

namespace gfx
{

class VertexBuffer
{
	class VertexArray
	{
	public:
		virtual ~VertexArray()
		{}

		virtual unsigned getStride() const = 0;
		virtual unsigned getSize() const = 0;

		virtual void pushBack(const Vertex3D& vertex) = 0;
		virtual void* getData() = 0;

		virtual void reserve(unsigned count) = 0;
		virtual void setUsed(unsigned count) = 0;

		virtual void clear() = 0;

		virtual Vertex3D& operator[](const unsigned index) = 0;
	};

	template <typename T>
	class VertexArrayImplementation : public VertexArray
	{
	public:
		unsigned getStride() const override
		{
			return sizeof(T);
		}

		unsigned getSize() const override
		{
			return vertices.size();
		}

		void pushBack(const Vertex3D& vertex) override
		{
			vertices.push_back(static_cast<const T&>(vertex));
		}

		void* getData() override
		{
			return vertices.data();
		}

		void reserve(unsigned count) override
		{
			vertices.reserve(count);
		}

		void setUsed(unsigned count) override
		{
			vertices.resize(count, T());
		}

		void clear() override
		{
			vertices.clear();
		}

		Vertex3D& operator[](const unsigned index) override
		{
			return static_cast<Vertex3D&>(vertices[index]);
		}
	private:
		std::vector<T> vertices;
	};
public:
	VertexBuffer(Vertex3D::VertexType vertexType);
	~VertexBuffer();

	void* getData();
	Vertex3D::VertexType getVertexType() const;

	unsigned getSize() const;

	void pushBack(const Vertex3D& vertex);

	void setUsed(unsigned count);
	void reserve(unsigned count);

	void clear();
private:
	Vertex3D::VertexType vertexType;

	VertexArray* vertices;
};

} // namespace gfx
