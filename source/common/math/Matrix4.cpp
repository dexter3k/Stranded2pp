#include "Matrix4.h"

#include <cassert>
#include <cstring>
#include <iostream>

#include "MathUtility.h"

namespace math
{

Matrix4::Matrix4(MatrixConstructor constructor) :
	matrix{
		0.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 0.0f
	}
{
	if (constructor == IdentityMatrix)
	{
		matrix[0] = 1.0f;
		matrix[5] = 1.0f;
		matrix[10] = 1.0f;
		matrix[15] = 1.0f;
	}
}

float& Matrix4::operator[](unsigned index)
{
	assert(index < 16);

	return matrix[index];
}

const float& Matrix4::operator[](unsigned index) const
{
	assert(index < 16);

	return matrix[index];
}

Matrix4& Matrix4::operator=(const Matrix4& other)
{
	memcpy(matrix, other.matrix, 16 * sizeof(float));

	return *this;
}

const float* Matrix4::pointer() const
{
	return matrix;
}

float* Matrix4::pointer()
{
	return matrix;
}

bool Matrix4::operator==(const Matrix4& other) const
{
	return !(operator!=(other));
}

bool Matrix4::operator!=(const Matrix4& other) const
{
	for (unsigned i = 0; i < 16; ++i)
	{
		if (matrix[i] != other.matrix[i])
		{
			return true;
		}
	}

	return false;
}

Matrix4 Matrix4::operator*(const Matrix4& other) const
{
	Matrix4 mat(*this);

	const float* m1 = this->matrix;
	const float* m2 = other.matrix;
	float* m3 = mat.matrix;

	m3[0] = m1[0] * m2[0] + m1[4] * m2[1] + m1[8] * m2[2] + m1[12] * m2[3];
	m3[1] = m1[1] * m2[0] + m1[5] * m2[1] + m1[9] * m2[2] + m1[13] * m2[3];
	m3[2] = m1[2] * m2[0] + m1[6] * m2[1] + m1[10] * m2[2] + m1[14] * m2[3];
	m3[3] = m1[3] * m2[0] + m1[7] * m2[1] + m1[11] * m2[2] + m1[15] * m2[3];

	m3[4] = m1[0] * m2[4] + m1[4] * m2[5] + m1[8] * m2[6] + m1[12] * m2[7];
	m3[5] = m1[1] * m2[4] + m1[5] * m2[5] + m1[9] * m2[6] + m1[13] * m2[7];
	m3[6] = m1[2] * m2[4] + m1[6] * m2[5] + m1[10] * m2[6] + m1[14] * m2[7];
	m3[7] = m1[3] * m2[4] + m1[7] * m2[5] + m1[11] * m2[6] + m1[15] * m2[7];

	m3[8] = m1[0] * m2[8] + m1[4] * m2[9] + m1[8] * m2[10] + m1[12] * m2[11];
	m3[9] = m1[1] * m2[8] + m1[5] * m2[9] + m1[9] * m2[10] + m1[13] * m2[11];
	m3[10] = m1[2] * m2[8] + m1[6] * m2[9] + m1[10] * m2[10] + m1[14] * m2[11];
	m3[11] = m1[3] * m2[8] + m1[7] * m2[9] + m1[11] * m2[10] + m1[15] * m2[11];

	m3[12] = m1[0] * m2[12] + m1[4] * m2[13] + m1[8] * m2[14] + m1[12] * m2[15];
	m3[13] = m1[1] * m2[12] + m1[5] * m2[13] + m1[9] * m2[14] + m1[13] * m2[15];
	m3[14] = m1[2] * m2[12] + m1[6] * m2[13] + m1[10] * m2[14] +
		m1[14] * m2[15];
	m3[15] = m1[3] * m2[12] + m1[7] * m2[13] + m1[11] * m2[14] +
		m1[15] * m2[15];

	return mat;
}

Matrix4 Matrix4::operator*(float scalar) const
{
	assert(false && "TODO");
}

Matrix4& Matrix4::operator*=(const Matrix4& other)
{
	Matrix4 tempMatrix(*this);

	const float* m1 = tempMatrix.matrix;
	const float* m2 = other.matrix;
	matrix[0] = m1[0] * m2[0] + m1[4] * m2[1] + m1[8] * m2[2] + m1[12] * m2[3];
	matrix[1] = m1[1] * m2[0] + m1[5] * m2[1] + m1[9] * m2[2] + m1[13] * m2[3];
	matrix[2] = m1[2] * m2[0] + m1[6] * m2[1] + m1[10] * m2[2] + m1[14] * m2[3];
	matrix[3] = m1[3] * m2[0] + m1[7] * m2[1] + m1[11] * m2[2] + m1[15] * m2[3];

	matrix[4] = m1[0] * m2[4] + m1[4] * m2[5] + m1[8] * m2[6] + m1[12] * m2[7];
	matrix[5] = m1[1] * m2[4] + m1[5] * m2[5] + m1[9] * m2[6] + m1[13] * m2[7];
	matrix[6] = m1[2] * m2[4] + m1[6] * m2[5] + m1[10] * m2[6] + m1[14] * m2[7];
	matrix[7] = m1[3] * m2[4] + m1[7] * m2[5] + m1[11] * m2[6] + m1[15] * m2[7];

	matrix[8] = m1[0] * m2[8] + m1[4] * m2[9] + m1[8] * m2[10] +
		m1[12] * m2[11];
	matrix[9] = m1[1] * m2[8] + m1[5] * m2[9] + m1[9] * m2[10] +
		m1[13] * m2[11];
	matrix[10] = m1[2] * m2[8] + m1[6] * m2[9] + m1[10] * m2[10] +
		m1[14] * m2[11];
	matrix[11] = m1[3] * m2[8] + m1[7] * m2[9] + m1[11] * m2[10] +
		m1[15] * m2[11];

	matrix[12] = m1[0] * m2[12] + m1[4] * m2[13] + m1[8] * m2[14] +
		m1[12] * m2[15];
	matrix[13] = m1[1] * m2[12] + m1[5] * m2[13] + m1[9] * m2[14] +
		m1[13] * m2[15];
	matrix[14] = m1[2] * m2[12] + m1[6] * m2[13] + m1[10] * m2[14] +
		m1[14] * m2[15];
	matrix[15] = m1[3] * m2[12] + m1[7] * m2[13] + m1[11] * m2[14] +
		m1[15] * m2[15];

	return *this;
}

Matrix4& Matrix4::operator*=(float scalar)
{
	assert(false && "TODO");
}

Matrix4& Matrix4::makeIdentity()
{
	memset(matrix, 0, 16 * sizeof(float));
	matrix[0] = matrix[5] = matrix[10] = matrix[15] = 1.0f;

	return *this;
}

bool Matrix4::isIdentity() const
{
	return (
		matrix[0] == 1.0f &&
		matrix[4] == 0.0f &&
		matrix[8] == 0.0f &&
		matrix[12] == 0.0f &&
		matrix[1] == 0.0f &&
		matrix[5] == 1.0f &&
		matrix[9] == 0.0f &&
		matrix[13] == 0.0f &&
		matrix[2] == 0.0f &&
		matrix[6] == 0.0f &&
		matrix[10] == 1.0f &&
		matrix[14] == 0.0f &&
		matrix[3] == 0.0f &&
		matrix[7] == 0.0f &&
		matrix[11] == 0.0f &&
		matrix[15] == 1.0f
	);
}

Matrix4& Matrix4::setTranslation(const math::Vector3f& translation)
{
	matrix[12] = translation.x;
	matrix[13] = translation.y;
	matrix[14] = translation.z;

	return *this;
}

math::Vector3f Matrix4::getTranslation() const
{
	return math::Vector3f(matrix[12], matrix[13], matrix[14]);
}

Matrix4& Matrix4::setRotationDegrees(const math::Vector3f& rotation)
{
	return setRotationRadians(math::Vector3f(rotation * degreesToRadians));
}

Matrix4& Matrix4::setRotationRadians(const math::Vector3f& rotation)
{
	float rollCos = std::cos(rotation.x);
	float rollSin = std::sin(rotation.x);
	float pitchCos = std::cos(rotation.y);
	float pitchSin = std::sin(rotation.y);
	float yawCos = std::cos(rotation.z);
	float yawSin = std::sin(rotation.z);

	matrix[0] = pitchCos * yawCos;
	matrix[1] = pitchCos * yawSin;
	matrix[2] = -pitchSin;

	float rollSinPitchSin = rollSin * pitchSin;
	float rollCosPitchSin = rollCos * pitchSin;

	matrix[4] = rollSinPitchSin * yawCos - rollCos * yawSin;
	matrix[5] = rollSinPitchSin * yawSin + rollCos * yawCos;
	matrix[6] = rollSin * pitchCos;

	matrix[8] = rollCosPitchSin * yawCos + rollSin * yawSin;
	matrix[9] = rollCosPitchSin * yawSin - rollSin * yawCos;
	matrix[10] = rollCos * pitchCos;

	return *this;
}

math::Vector3f Matrix4::getRotationDegrees() const
{
	Vector3f scale = getScale();

	// we need to check for negative scale on to axes, which would bring up wrong results
	if (scale.y < 0 && scale.z < 0)
	{
		scale.y = -scale.y;
		scale.z = -scale.z;
	}
	else if (scale.x < 0 && scale.z < 0)
	{
		scale.x = -scale.x;
		scale.z = -scale.z;
	}
	else if (scale.x < 0 && scale.y < 0)
	{
		scale.x = -scale.x;
		scale.y = -scale.y;
	}

	Vector3f invScale(1.0f / scale.x, 1.0f / scale.y, 1.0f / scale.z);


	float y = -std::asin(clamp(matrix[2] * invScale.x, -1.0f, 1.0f));
	float c = std::cos(y);
	y *= radiansToDegrees;

	float rotx, roty, x, z;

	if (!compareRelative(c, 0.0f))
	{
		float invC = 1.0f / c;

		rotx = matrix[10] * invC * invScale.z;
		roty = matrix[6] * invC * invScale.y;
		x = std::atan2(roty, rotx) * radiansToDegrees;

		rotx = matrix[0] * invC * invScale.x;
		roty = matrix[1] * invC * invScale.x;
		z = std::atan2(roty, rotx) * radiansToDegrees;
	}
	else
	{
		x = 0.0f;

		rotx = matrix[5] * invScale.y;
		roty = -matrix[4] * invScale.y;
		z = std::atan2(roty, rotx) * radiansToDegrees;
	}

	if (x < 0.0f) x += 360.0f;
	if (y < 0.0f) y += 360.0f;
	if (z < 0.0f) z += 360.0f;

	return Vector3f(x, y, z);
}

Matrix4& Matrix4::setScale(const math::Vector3f& scale)
{
	matrix[0] = scale.x;
	matrix[5] = scale.y;
	matrix[10] = scale.z;

	return *this;
}

math::Vector3f Matrix4::getScale() const
{
	if (compareRelative(matrix[1], 0.0f) &&
		compareRelative(matrix[2], 0.0f) &&
		compareRelative(matrix[4], 0.0f) &&
		compareRelative(matrix[6], 0.0f) &&
		compareRelative(matrix[8], 0.0f) &&
		compareRelative(matrix[9], 0.0f))
	{
		return math::Vector3f(matrix[0], matrix[5], matrix[10]);
	}

	return math::Vector3f(
		std::sqrt(
			matrix[0] * matrix[0] +
			matrix[1] * matrix[1] +
			matrix[2] * matrix[2]),
		std::sqrt(
			matrix[4] * matrix[4] +
			matrix[5] * matrix[5] +
			matrix[6] * matrix[6]),
		std::sqrt(
			matrix[8] * matrix[8] +
			matrix[9] * matrix[9] +
			matrix[10] * matrix[10]));
}

Matrix4& Matrix4::buildProjectionMatrixOrtho(float width, float height,
	float near, float far)
{
	matrix[0] = 2.0f / width;
	matrix[1] = 0.0f;
	matrix[2] = 0.0f;
	matrix[3] = 0.0f;

	matrix[4] = 0.0f;
	matrix[5] = 2.0f / height;
	matrix[6] = 0.0f;
	matrix[7] = 0.0f;

	matrix[8] = 0.0f;
	matrix[9] = 0.0f;
	matrix[10] = 1.0f / (far - near);
	matrix[11] = 0.0f;

	matrix[12] = 0.0f;
	matrix[13] = 0.0f;
	matrix[14] = near / (near - far);
	matrix[15] = 1.0f;

	return *this;
}

Matrix4& Matrix4::buildProjectionMatrixPerspective(float fieldOfViewDegrees,
		float aspectRatio, float near, float far)
{
	float h = 1.0f / std::tan(fieldOfViewDegrees * degreesToRadians * 0.5f);
	float w = h / aspectRatio;

	matrix[0] = w;
	matrix[1] = 0.0f;
	matrix[2] = 0.0f;
	matrix[3] = 0.0f;

	matrix[4] = 0.0f;
	matrix[5] = h;
	matrix[6] = 0.0f;
	matrix[7] = 0.0f;

	matrix[8] = 0.0f;
	matrix[9] = 0.0f;
	matrix[10] = -far / (far - near);
	matrix[11] = -1.0f;

	matrix[12] = 0.0f;
	matrix[13] = 0.0f;
	matrix[14] = - (2 * near * far / (far - near));
	matrix[15] = 0.0f;
/*
	// std::cout -- best debugging tool ever (nah, vaglrind is better sometimes)
	for (unsigned y = 0; y < 4; ++y)
	{
		for (unsigned x = 0; x < 4; ++x)
		{
			std::cout << matrix[4 * x + y] << " ";
		}

		std::cout << std::endl;
	}

	std::cout << std::endl;
*/
	return *this;
}

} // namespace math
