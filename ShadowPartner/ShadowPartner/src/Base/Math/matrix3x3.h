//==========================================================
// 概要  :Matrix3x3クラスの実装
// Author:Itsuki Namito
//==========================================================

#ifndef _BASE_MATH_MATRIX3X3_H_
#define _BASE_MATH_MATRIX3X3_H_

namespace shadowpartner
{
	//Constructor
	D3DXINLINE Matrix3x3::Matrix3x3(const Matrix3x3 &mat)
	{
		col0 = mat.col0;
		col1 = mat.col1;
		col2 = mat.col2;
	}

	D3DXINLINE Matrix3x3::Matrix3x3(const Vector3 &_col0, const Vector3 &_col1, const Vector3 &_col2)
	{
		col0 = _col0;
		col1 = _col1;
		col2 = _col2;
	}

	D3DXINLINE Matrix3x3::Matrix3x3(const Quaternion &unitQuat)
	{
		float qx, qy, qz, qw, qx2, qy2, qz2, qxqx2, qyqy2, qzqz2, qxqy2, qyqz2, qzqw2, qxqz2, qyqw2, qxqw2;
		qx = unitQuat.x;
		qy = unitQuat.y;
		qz = unitQuat.z;
		qw = unitQuat.w;
		qx2 = (qx + qx);
		qy2 = (qy + qy);
		qz2 = (qz + qz);
		qxqx2 = (qx * qx2);
		qxqy2 = (qx * qy2);
		qxqz2 = (qx * qz2);
		qxqw2 = (qw * qx2);
		qyqy2 = (qy * qy2);
		qyqz2 = (qy * qz2);
		qyqw2 = (qw * qy2);
		qzqz2 = (qz * qz2);
		qzqw2 = (qw * qz2);
		col0 = Vector3(((1.0f - qyqy2) - qzqz2), (qxqy2 + qzqw2), (qxqz2 - qyqw2));
		col1 = Vector3((qxqy2 - qzqw2), ((1.0f - qxqx2) - qzqz2), (qyqz2 + qxqw2));
		col2 = Vector3((qxqz2 + qyqw2), (qyqz2 - qxqw2), ((1.0f - qxqx2) - qyqy2));
	}

	D3DXINLINE Matrix3x3::Matrix3x3(float scalar)
	{
		col0 = Vector3(scalar);
		col1 = Vector3(scalar);
		col2 = Vector3(scalar);
	}

	//Static construct
	D3DXINLINE const Matrix3x3 Matrix3x3::Identity()
	{
		return Matrix3x3
		(
			Vector3::right(),
			Vector3::up(),
			Vector3::forward()
		);
	}

	D3DXINLINE const Matrix3x3 Matrix3x3::RotationX(float radians)
	{
		float s, c;
		s = sinf(radians);
		c = cosf(radians);
		return Matrix3x3(
			Vector3::right(),
			Vector3(0.0f, c, s),
			Vector3(0.0f, -s, c)
		);
	}

	D3DXINLINE const Matrix3x3 Matrix3x3::RotationY(float radians)
	{
		float s, c;
		s = sinf(radians);
		c = cosf(radians);
		return Matrix3x3(
			Vector3(c, 0.0f, -s),
			Vector3::up(),
			Vector3(s, 0.0f, c)
		);
	}

	D3DXINLINE const Matrix3x3 Matrix3x3::RotationZ(float radians)
	{
		float s, c;
		s = sinf(radians);
		c = cosf(radians);
		return Matrix3x3(
			Vector3(c, s, 0.0f),
			Vector3(-s, c, 0.0f),
			Vector3::forward()
		);
	}

	D3DXINLINE const Matrix3x3 Matrix3x3::RotationZYX(const Vector3 &radiansXYZ)
	{
		float sX, cX, sY, cY, sZ, cZ, temp0, temp1;
		sX = sinf(radiansXYZ.x);
		cX = cosf(radiansXYZ.x);
		sY = sinf(radiansXYZ.y);
		cY = cosf(radiansXYZ.y);
		sZ = sinf(radiansXYZ.z);
		cZ = cosf(radiansXYZ.z);
		temp0 = (cZ * sY);
		temp1 = (sZ * sY);
		return Matrix3x3(
			Vector3((cZ * cY), (sZ * cY), -sY),
			Vector3(((temp0 * sX) - (sZ * cX)), ((temp1 * sX) + (cZ * cX)), (cY * sX)),
			Vector3(((temp0 * cX) + (sZ * sX)), ((temp1 * cX) - (cZ * sX)), (cY * cX))
		);
	}

	D3DXINLINE const Matrix3x3 Matrix3x3::Rotation(float radians, const Vector3 &unitVec)
	{
		float x, y, z, s, c, oneMinusC, xy, yz, zx;
		s = sinf(radians);
		c = cosf(radians);
		x = unitVec.x;
		y = unitVec.y;
		z = unitVec.z;
		xy = (x * y);
		yz = (y * z);
		zx = (z * x);
		oneMinusC = (1.0f - c);
		return Matrix3x3(
			Vector3((((x * x) * oneMinusC) + c), ((xy * oneMinusC) + (z * s)), ((zx * oneMinusC) - (y * s))),
			Vector3(((xy * oneMinusC) - (z * s)), (((y * y) * oneMinusC) + c), ((yz * oneMinusC) + (x * s))),
			Vector3(((zx * oneMinusC) + (y * s)), ((yz * oneMinusC) - (x * s)), (((z * z) * oneMinusC) + c))
		);
	}

	D3DXINLINE const Matrix3x3 Matrix3x3::Rotation(const Quaternion &unitQuat)
	{
		return Matrix3x3(unitQuat);
	}

	D3DXINLINE const Matrix3x3 Matrix3x3::Scale(const Vector3 &scaleVec)
	{
		return Matrix3x3(
			Vector3(scaleVec.x, 0.0f, 0.0f),
			Vector3(0.0f, scaleVec.y, 0.0f),
			Vector3(0.0f, 0.0f, scaleVec.z)
		);
	}

	//Operator
	D3DXINLINE Matrix3x3 &Matrix3x3::operator =(const Matrix3x3 &mat)
	{
		col0 = mat.col0;
		col1 = mat.col1;
		col2 = mat.col2;
		return *this;
	}

	D3DXINLINE Vector3 &Matrix3x3::operator [](int col)
	{
		return *(&col0 + col);
	}

	D3DXINLINE const Vector3 Matrix3x3::operator [](int col) const
	{
		return *(&col0 + col);
	}

	D3DXINLINE const Matrix3x3 Matrix3x3::operator +(const Matrix3x3 &mat) const
	{
		return Matrix3x3(
			(col0 + mat.col0),
			(col1 + mat.col1),
			(col2 + mat.col2)
		);
	}

	D3DXINLINE const Matrix3x3 Matrix3x3::operator -(const Matrix3x3 &mat) const
	{
		return Matrix3x3(
			(col0 - mat.col0),
			(col1 - mat.col1),
			(col2 - mat.col2)
		);
	}

	D3DXINLINE const Matrix3x3 Matrix3x3::operator -() const
	{
		return Matrix3x3(
			(-col0),
			(-col1),
			(-col2)
		);
	}

	D3DXINLINE const Matrix3x3 Matrix3x3::operator *(float scalar) const
	{
		return Matrix3x3(
			(col0 * scalar),
			(col1 * scalar),
			(col2 * scalar)
		);
	}

	D3DXINLINE const Vector3 Matrix3x3::operator *(const Vector3 &vec) const
	{
		return Vector3(
			(((col0.x * vec.x) + (col1.x * vec.y)) + (col2.x * vec.z)),
			(((col0.y * vec.x) + (col1.y * vec.y)) + (col2.y * vec.z)),
			(((col0.z * vec.x) + (col1.z * vec.y)) + (col2.z * vec.z))
		);
	}

	D3DXINLINE const Matrix3x3 Matrix3x3::operator *(const Matrix3x3 &mat) const
	{
		return Matrix3x3(
			(*this * mat.col0),
			(*this * mat.col1),
			(*this * mat.col2)
		);
	}

	D3DXINLINE Matrix3x3 &Matrix3x3::operator +=(const Matrix3x3 &mat)
	{
		*this = *this + mat;
		return *this;
	}

	D3DXINLINE Matrix3x3 &Matrix3x3::operator -=(const Matrix3x3 &mat)
	{
		*this = *this - mat;
		return *this;
	}
	D3DXINLINE Matrix3x3 &Matrix3x3::operator *=(float scalar)
	{
		*this = *this * scalar;
		return *this;
	}

	D3DXINLINE Matrix3x3 &Matrix3x3::operator *=(const Matrix3x3 &mat)
	{
		*this = *this * mat;
		return *this;
	}

	//Accessor

	D3DXINLINE Matrix3x3 &Matrix3x3::col(int col, const Vector3 &vec)
	{
		*(&col0 + col) = vec;
		return *this;
	}

	D3DXINLINE const Vector3 Matrix3x3::col(int col) const
	{
		return *(&col0 + col);
	}

	D3DXINLINE Matrix3x3 &Matrix3x3::row(int row, const Vector3 &vec)
	{
		col0.element(row, vec.element(0));
		col1.element(row, vec.element(1));
		col2.element(row, vec.element(2));
		return *this;
	}

	D3DXINLINE const Vector3 Matrix3x3::row(int row) const
	{
		return Vector3(col0.element(row), col1.element(row), col2.element(row));
	}

	D3DXINLINE Matrix3x3 &Matrix3x3::element(int col, int row, float val)
	{
		Vector3 tempV3_0;
		tempV3_0 = this->col(col);
		tempV3_0.element(row, val);
		this->col(col, tempV3_0);
		return *this;
	}

	D3DXINLINE float Matrix3x3::element(int col, int row) const
	{
		return this->col(col).element(row);
	}

	//Functions
	D3DXINLINE const Matrix3x3 operator *(float scalar, const Matrix3x3 &mat)
	{
		return mat * scalar;
	}

	D3DXINLINE void CrossMatrix(Matrix3x3 &out, const Vector3 &vec)				//3次元ベクトルを外積する行列
	{
		out.col0 = Vector3(0.0f, vec.z, -vec.y);
		out.col1 = Vector3(-vec.z, 0.0f, vec.x);
		out.col2 = Vector3(vec.y, -vec.x, 0.0f);
	}

	D3DXINLINE const Matrix3x3 CrossMatrix(const Vector3 &vec)						//3次元ベクトルを外積する行列
	{
		Matrix3x3 result;
		CrossMatrix(result, vec);
		return result;
	}

	D3DXINLINE const Matrix3x3 MulPerElem(const Matrix3x3 &mat0, const Matrix3x3 &mat1)
	{
		return Matrix3x3
		(
			MulPerElem(mat0.col0, mat1.col0),
			MulPerElem(mat0.col1, mat1.col1),
			MulPerElem(mat0.col2, mat1.col2)
		);
	}

	D3DXINLINE const Matrix3x3 AbsPerElem(const Matrix3x3 &mat)
	{
		return Matrix3x3
		(
			AbsPerElem(mat.col0),
			AbsPerElem(mat.col1),
			AbsPerElem(mat.col2)
		);
	}


	D3DXINLINE const Matrix3x3 Transpose(const Matrix3x3 &mat)
	{
		return Matrix3x3(
			Vector3(mat.col0.x, mat.col1.x, mat.col2.x),
			Vector3(mat.col0.y, mat.col1.y, mat.col2.y),
			Vector3(mat.col0.z, mat.col1.z, mat.col2.z)
		);
	}
	D3DXINLINE const Matrix3x3 Inverse(const Matrix3x3 &mat)
	{
		Vector3 temp0, temp1, temp2;
		float detinv;
		temp0 = Cross(mat.col1, mat.col2);
		temp1 = Cross(mat.col2, mat.col0);
		temp2 = Cross(mat.col0, mat.col1);
		detinv = (1.0f / Dot(mat.col2, temp2));
		return Matrix3x3(
			Vector3((temp0.x * detinv), (temp1.x * detinv), (temp2.x * detinv)),
			Vector3((temp0.y * detinv), (temp1.y * detinv), (temp2.y * detinv)),
			Vector3((temp0.z * detinv), (temp1.z * detinv), (temp2.z * detinv))
		);
	}

}

#endif