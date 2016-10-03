#pragma once

#include "IndexSize.h"

namespace gfx
{

template <IndexSize indexSize>
class IndexBuffer
{
public:
	IndexBuffer();
};

template <>
class IndexBuffer<Index16Bit>
{
public:
	IndexBuffer();
};



} // namespace gfx
