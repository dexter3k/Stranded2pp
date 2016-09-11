#pragma once

namespace math
{

template <typename T>
class Aabb
{
public:
	Vector3<T> minEdge;
	Vector3<T> maxEdge;

	Aabb() :
		minEdge(),
		maxEdge()
	{}

	Aabb(const Vector3<T>& min, const Vector3<T>& max) :
		minEdge(min),
		maxEdge(max)
	{}

	Aabb(const T& minX, const T& minY, const T& minZ, const T& maxX,
			const T& maxY, const T& maxZ) :
		minEdge(minX, minY, minZ),
		maxEdge(maxX, maxY, maxZ)
	{}

	~Aabb()
	{}
};

} // namespace math
