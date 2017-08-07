#pragma once

#include <vector>

#include "IndexSize.h"

namespace gfx
{

class IndexBuffer
{
	class IndexArray
	{
	public:
		virtual ~IndexArray() = default;

		virtual unsigned getStride() const = 0;
		virtual unsigned getSize() const = 0;

		virtual void pushBack(const unsigned& index) = 0;
		virtual void* getData() = 0;

		virtual void setUsed(unsigned count) = 0;

		virtual void clear() = 0;

		virtual unsigned operator[](const unsigned bufferIndex) const = 0;
	};

	template <typename T>
	class IndexArrayImplementation : public IndexArray
	{
	public:
		unsigned getStride() const override
		{
			return sizeof(T);
		}

		unsigned getSize() const override
		{
			return indices.size();
		}

		void pushBack(const unsigned& index) override
		{
			indices.push_back(index);
		}

		void* getData() override
		{
			return indices.data();
		}

		void setUsed(unsigned count) override
		{
			indices.resize(count, T());
		}

		void clear() override
		{
			indices.clear();
		}

		unsigned operator[](const unsigned bufferIndex) const override
		{
			return static_cast<unsigned>(indices[bufferIndex]);
		}
	private:
		std::vector<T> indices;
	};
public:
	IndexBuffer(IndexSize indexSize);
	~IndexBuffer();

	void* getData();
	IndexSize getIndexSize() const;

	unsigned getSize() const;

	void pushBack(const unsigned& value);

	void setUsed(unsigned count);

	void clear();
private:
	IndexSize indexSize;

	IndexArray* indices;
};

} // namespace gfx
