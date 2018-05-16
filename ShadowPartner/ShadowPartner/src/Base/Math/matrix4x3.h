//==========================================================
// ŠT—v  :Martix4x3ƒNƒ‰ƒX‚ÌŽÀ‘•
// Author:Itsuki Namito
//==========================================================

#ifndef _BASE_MATH_MATRIX4X3_H_
#define _BASE_MATH_MATRIX4X3_H_

namespace shadowpartner
{
	//Constructers

	D3DXINLINE Matrix4x3::Matrix4x3(const Matrix4x3 &tran)
	{
		col0 = tran.col0;
		col1 = tran.col1;
		col2 = tran.col2;
		col3 = tran.col3;
	}

	D3DXINLINE Matrix4x3::Matrix4x3(const Vector3 &_col0, const Vector3 &_col1, const Vector3 &_col2, const Vector3 &_col3)
	{
		col0 = _col0;
		col1 = _col1;
		col2 = _col2;
		col3 = _col3;
	}

	D3DXINLINE Matrix4x3::Matrix4x3(const Matrix3x3 &tran, const Vector3 &translateVec)
	{
		this->upper3x3(tran);
		this->translation(translateVec);
	}

	D3DXINLINE Matrix4x3::Matrix4x3(const Quaternion &unitQuat, const Vector3 &translateVec)
	{
		this->upper3x3(Matrix3x3(unitQuat));
		this->translation(translateVec);
	}

	D3DXINLINE Matrix4x3::Matrix4x3(float scalar)
	{
		col0 = Vector3(scalar);
		col1 = Vector3(scalar);
		col2 = Vector3(scalar);
		col3 = Vector3(scalar);
	}

	//Static construct
	D3DXINLINE const Matrix4x3 Matrix4x3::Identity()
	{
		return Matrix4x3
		(
			Vector3::right(),
			Vector3::up(),
			Vector3::forward(),
			Vector3(0.0f)
		);
	}

		D3DXINLINE const Matrix4x3 Matrix4x3::RotationX(float radians)
	{
		float s, c;
		s = sinf(radians);
		c = cosf(radians);
		return Matrix4x3
		(
			Vector3::right(),
			Vector3(0.0f, c, s),
			Vector3(0.0f, -s, c),
			Vector3(0.0f)
		);
	}

	D3DXINLINE const Matrix4x3 Matrix4x3::RotationY(float radians)
	{
		float s, c;
		s = sinf(radians);
		c = cosf(radians);
		return Matrix4x3
		(
			Vector3(c, 0.0f, -s),
			Vector3::up(),
			Vector3(s, 0.0f, c),
			Vector3(0.0f)
		);
	}

	D3DXINLINE const Matrix4x3 Matrix4x3::RotationZ(float radians)
	{
		float s, c;
		s = sinf(radians);
		c = cosf(radians);
		return Matrix4x3
		(
			Vector3(c, s, 0.0f),
			Vector3(-s, c, 0.0f),
			Vector3::forward(),
			Vector3(0.0f)
		);
	}

	D3DXINLINE const Matrix4x3 Matrix4x3::RotationZYX(const Vector3 &radiansXYZ)
	{
		float sX, cX, sY, cY, sZ, cZ, tmp0, tmp1;
		sX = sinf(radiansXYZ.x);
		cX = cosf(radiansXYZ.x);
		sY = sinf(radiansXYZ.y);
		cY = cosf(radiansXYZ.y);
		sZ = sinf(radiansXYZ.z);
		cZ = cosf(radiansXYZ.z);
		tmp0 = (cZ * sY);
		tmp1 = (sZ * sY);
		return Matrix4x3
		(
			Vector3((cZ * cY), (sZ * cY), -sY),
			Vector3(((tmp0 * sX) - (sZ * cX)), ((tmp1 * sX) + (cZ * cX)), (cY * sX)),
			Vector3(((tmp0 * cX) + (sZ * sX)), ((tmp1 * cX) - (cZ * sX)), (cY * cX)),
			Vector3(0.0f)
		);
	}

	D3DXINLINE const Matrix4x3 Matrix4x3::Rotation(float radians, const Vector3 &unitVec)
	{
		return Matrix4x3(Matrix3x3::Rotation(radians, unitVec), Vector3(0.0f));
	}

	D3DXINLINE const Matrix4x3 Matrix4x3::Rotation(const Quaternion &unitQuat)
	{
		return Matrix4x3(Matrix3x3(unitQuat), Vector3(0.0f));
	}

	D3DXINLINE const Matrix4x3 Matrix4x3::Scale(const Vector3 &scaleVec)
	{
		return Matrix4x3
		(
			Vector3(scaleVec.x, 0.0f, 0.0f),
			Vector3(0.0f, scaleVec.y, 0.0f),
			Vector3(0.0f, 0.0f, scaleVec.z),
			Vector3(0.0f)
		);
	}

	D3DXINLINE const Matrix4x3 Matrix4x3::Translation(const Vector3 &translateVec)
	{
		return Matrix4x3
		(
			Vector3::right(),
			Vector3::up(),
			Vector3::forward(),
			translateVec
		);
	}

	//Operator
	D3DXINLINE Matrix4x3 &Matrix4x3::operator =(const Matrix4x3 &tran)
	{
		col0 = tran.col0;
		col1 = tran.col1;
		col2 = tran.col2;
		col3 = tran.col3;
		return *this;
	}

	D3DXINLINE Vector3 &Matrix4x3::operator [](int col)
	{
		return *(&col0 + col);
	}

	D3DXINLINE const Vector3 Matrix4x3::operator [](int col) const
	{
		return *(&col0 + col);
	}

	D3DXINLINE const Vector3 Matrix4x3::operator *(const Vector3 &vec) const
	{
		return Vector3
		(
			(((col0.x * vec.x) + (col1.x * vec.y)) + (col2.x * vec.z)),
			(((col0.y * vec.x) + (col1.y * vec.y)) + (col2.y * vec.z)),
			(((col0.z * vec.x) + (col1.z * vec.y)) + (col2.z * vec.z))
		);
	}

	D3DXINLINE const Matrix4x3 Matrix4x3::operator *(const Matrix4x3 &tran) const
	{
		return Matrix4x3(
			(*this * tran.col0),
			(*this * tran.col1),
			(*this * tran.col2),
			Vector3((*this * Vector3(tran.col3)))
		);
	}

	D3DXINLINE Matrix4x3 &Matrix4x3::operator *=(const Matrix4x3 &tran)
	{
		*this = *this * tran;
		return *this;
	}

	//Accessor
	D3DXINLINE Matrix4x3 &Matrix4x3::upper3x3(const Matrix3x3 &tran)
	{
		col0 = tran.col0;
		col1 = tran.col1;
		col2 = tran.col2;
		return *this;
	}

	D3DXINLINE const Matrix3x3 Matrix4x3::upper3x3(void) const
	{
		return Matrix3x3(col0, col1, col2);
	}

	D3DXINLINE Matrix4x3 &Matrix4x3::translation(const Vector3 &translateVec)
	{
		col3 = translateVec;
		return *this;
	}

	D3DXINLINE const Vector3 Matrix4x3::translation(void) const
	{
		return col3;
	}

	D3DXINLINE Matrix4x3 &Matrix4x3::col(int col, const Vector3 &vec)
	{
		*(&col0 + col) = vec;
		return *this;
	}

	D3DXINLINE const Vector3 Matrix4x3::col(int col) const
	{
		return *(&col0 + col);
	}

	//D3DXINLINE Matrix4x3 &row(int col, const Vector4 &vec);
	//D3DXINLINE const Vector4 row(int col) const;
	D3DXINLINE Matrix4x3 &Matrix4x3::element(int col, int row, float val)
	{
		Vector3 tmpV3_0;
		tmpV3_0 = this->col(col);
		tmpV3_0.element(row, val);
		this->col(col, tmpV3_0);
		return *this;
	}

	D3DXINLINE float Matrix4x3::element(int col, int row) const
	{
		return this->col(col).element(row);
	}

	//Functions
	D3DXINLINE const Matrix4x3 MulPerElem(const Matrix4x3 &tran0, const Matrix4x3 &tran1)
	{
		return Matrix4x3
		(
			MulPerElem(tran0.col0, tran1.col0),
			MulPerElem(tran0.col1, tran1.col1),
			MulPerElem(tran0.col2, tran1.col2),
			MulPerElem(tran0.col3, tran1.col3)
		);
	}

	D3DXINLINE const Matrix4x3 AbsPerElem(const Matrix4x3 &tran)
	{
		return Matrix4x3
		(
			AbsPerElem(tran.col0),
			AbsPerElem(tran.col1),
			AbsPerElem(tran.col2),
			AbsPerElem(tran.col3)
		);
	}

	D3DXINLINE const Matrix4x3 Inverse(const Matrix4x3 &tran)
	{
		Vector3 tmp0, tmp1, tmp2, inv0, inv1, inv2;
		float detinv;
		tmp0 = Cross(tran.col1, tran.col2);
		tmp1 = Cross(tran.col2, tran.col0);
		tmp2 = Cross(tran.col0, tran.col1);
		detinv = (1.0f / Dot(tran.col2, tmp2));
		inv0 = Vector3((tmp0.x * detinv), (tmp1.x * detinv), (tmp2.x * detinv));
		inv1 = Vector3((tmp0.y * detinv), (tmp1.y * detinv), (tmp2.y * detinv));
		inv2 = Vector3((tmp0.z * detinv), (tmp1.z * detinv), (tmp2.z * detinv));
		return Matrix4x3
		(
			inv0,
			inv1,
			inv2,
			Vector3((-((inv0 * tran.col3.x) + ((inv1 * tran.col3.y) + (inv2 * tran.col3.z)))))
		);
	}

	D3DXINLINE const Matrix4x3 OrthoInverse(const Matrix4x3 &tran)
	{
		Vector3 inv0, inv1, inv2;
		inv0 = Vector3(tran.col0.x, tran.col1.x, tran.col2.x);
		inv1 = Vector3(tran.col0.y, tran.col1.y, tran.col2.y);
		inv2 = Vector3(tran.col0.z, tran.col1.z, tran.col2.z);
		return Matrix4x3
		(
			inv0,
			inv1,
			inv2,
			Vector3((-((inv0 * tran.col3.x) + ((inv1 * tran.col3.y) + (inv2 * tran.col3.z)))))
		);
	}

}	// namespace 

#endif // !__MATRIX4X3_H_