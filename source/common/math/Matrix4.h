#pragma once

#include "Vector3.h"

namespace math
{

class Matrix4
{
public:
	enum MatrixConstructor
	{
		EmptyMatrix,
		IdentityMatrix
	};
public:
	Matrix4(MatrixConstructor constructor = IdentityMatrix);

	float& operator()(unsigned row, unsigned column);
	const float& operator()(unsigned row, unsigned column) const;

	float& operator[](unsigned index);
	const float& operator[](unsigned index) const;

	Matrix4& operator=(const Matrix4& other);

	const float* pointer() const;
	float* pointer();

	bool operator==(const Matrix4& other) const;
	bool operator!=(const Matrix4& other) const;

	Matrix4 operator+(const Matrix4& other) const;
	Matrix4 operator-(const Matrix4& other) const;

	Matrix4& operator+=(const Matrix4& other);
	Matrix4& operator-=(const Matrix4& other);

	Matrix4 operator*(const Matrix4& other) const;
	Matrix4 operator*(float scalar) const;

	Matrix4& operator*=(const Matrix4& other);
	Matrix4& operator*=(float scalar);

	Matrix4& makeIdentity();
	bool isIdentity() const;

	Matrix4& setTranslation(const math::Vector3f& translation);
	math::Vector3f getTranslation() const;

	Matrix4& setRotationDegrees(const math::Vector3f& rotation);
	Matrix4& setRotationRadians(const math::Vector3f& rotation);
	math::Vector3f getRotationDegrees() const;

	Matrix4& setScale(const math::Vector3f& scale);
	math::Vector3f getScale() const;

	Matrix4& buildProjectionMatrixOrtho(float width, float height, float near,
		float far);
	Matrix4& buildProjectionMatrixPerspective(float fieldOfViewDegrees,
		float aspectRatio, float near, float far);
private:
	float matrix[16];
};

} // namespace math
