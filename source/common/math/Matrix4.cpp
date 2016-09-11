#include "Matrix4.h"

#include <cstring>

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

Matrix4& Matrix4::makeIdentity()
{
	memset(matrix, 0, 16 * sizeof(float));
	matrix[0] = matrix[5] = matrix[10] = matrix[15] = 1.0f;

	return *this;
}

Matrix4& Matrix4::setTranslation(const math::Vector3f& translation)
{
	matrix[12] = translation.x;
	matrix[13] = translation.y;
	matrix[14] = translation.z;

	return *this;
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

} // namespace math
