//==========================================================
// äTóv  :QuaternionÉNÉâÉXÇÃé¿ëï
// Author:Itsuki Namito
//==========================================================

#ifndef _BASE_MATH_QUATERNION_H_
#define _BASE_MATH_QUATERNION_H_

namespace shadowpartner
{
	//Constructor

	D3DXINLINE Quaternion::Quaternion(const Quaternion &quat)
	{
		x = quat.x;
		y = quat.y;
		z = quat.z;
		w = quat.w;
	}

	D3DXINLINE Quaternion::Quaternion(float _x, float _y, float _z, float _w)
	{
		x = _x;
		y = _y;
		z = _z;
		w = _w;
	}

	D3DXINLINE Quaternion::Quaternion(const Vector3 &xyz, float _w)
	{
		x = xyz.x;
		y = xyz.y;
		z = xyz.z;
		w = _w;
	}

	//âÒì]çsóÒÇ≈èâä˙âª
	D3DXINLINE Quaternion::Quaternion(const Matrix3x3 &rotMat)
	{
		float trace, radicand, scale, xx, yx, zx, xy, yy, zy, xz, yz, zz, tempx, tempy, tempz, tempw, qx, qy, qz, qw;
		int negTrace, ZgtX, ZgtY, YgtX;
		int largestXorY, largestYorZ, largestZorX;

		xx = rotMat.col0.x;
		yx = rotMat.col0.y;
		zx = rotMat.col0.z;
		xy = rotMat.col1.x;
		yy = rotMat.col1.y;
		zy = rotMat.col1.z;
		xz = rotMat.col2.x;
		yz = rotMat.col2.y;
		zz = rotMat.col2.z;

		trace = ((xx + yy) + zz);

		negTrace = (trace < 0.0f);
		ZgtX = zz > xx;
		ZgtY = zz > yy;
		YgtX = yy > xx;
		largestXorY = (!ZgtX || !ZgtY) && negTrace;
		largestYorZ = (YgtX || ZgtX) && negTrace;
		largestZorX = (ZgtY || !YgtX) && negTrace;

		if (largestXorY)
		{
			zz = -zz;
			xy = -xy;
		}
		if (largestYorZ)
		{
			xx = -xx;
			yz = -yz;
		}
		if (largestZorX)
		{
			yy = -yy;
			zx = -zx;
		}

		radicand = (((xx + yy) + zz) + 1.0f);
		scale = (0.5f * (1.0f / sqrtf(radicand)));

		tempx = ((zy - yz) * scale);
		tempy = ((xz - zx) * scale);
		tempz = ((yx - xy) * scale);
		tempw = (radicand * scale);
		qx = tempx;
		qy = tempy;
		qz = tempz;
		qw = tempw;

		if (largestXorY)
		{
			qx = tempw;
			qy = tempz;
			qz = tempy;
			qw = tempx;
		}
		if (largestYorZ)
		{
			tempx = qx;
			tempz = qz;
			qx = qy;
			qy = tempx;
			qz = qw;
			qw = tempz;
		}

		x = qx;
		y = qy;
		z = qz;
		w = qw;
	}

	D3DXINLINE Quaternion::Quaternion(float scalar)
	{
		x = scalar;
		y = scalar;
		z = scalar;
		w = scalar;
	}

	//Static construct
	D3DXINLINE const Quaternion Quaternion::Identity()
	{
		return Quaternion(Vector3::zero(), 1.0f);
	}

	D3DXINLINE const Quaternion Quaternion::Rotation(const Vector3 &unitVec0, const Vector3 &unitVec1)
	{
		float cosHalfAngleX2, recipCosHalfAngleX2;
		cosHalfAngleX2 = sqrtf((2.0f * (1.0f + Dot(unitVec0, unitVec1))));
		recipCosHalfAngleX2 = (1.0f / cosHalfAngleX2);
		return Quaternion((Cross(unitVec0, unitVec1) * recipCosHalfAngleX2), (cosHalfAngleX2 * 0.5f));
	}

	D3DXINLINE const Quaternion Quaternion::Rotation(float radians, const Vector3 &unitVec)
	{
		float s, c, angle;
		angle = (radians * 0.5f);
		s = sinf(angle);
		c = cosf(angle);
		return Quaternion((unitVec * s), c);
	}

	D3DXINLINE const Quaternion Quaternion::RotationX(float radians)
	{
		float s, c, angle;
		angle = (radians * 0.5f);
		s = sinf(angle);
		c = cosf(angle);
		return Quaternion(s, 0.0f, 0.0f, c);
	}

	D3DXINLINE const Quaternion Quaternion::RotaitonY(float radians)
	{
		float s, c, angle;
		angle = (radians * 0.5f);
		s = sinf(angle);
		c = cosf(angle);
		return Quaternion(0.0f, s, 0.0f, c);
	}

	D3DXINLINE const Quaternion Quaternion::RotationZ(float radians)
	{
		float s, c, angle;
		angle = (radians * 0.5f);
		s = sinf(angle);
		c = cosf(angle);
		return Quaternion(0.0f, 0.0f, s, c);
	}

	//Operator
	D3DXINLINE Quaternion &Quaternion::operator =(const Quaternion &quat)
	{
		x = quat.x;
		y = quat.y;
		z = quat.z;
		w = quat.w;

		return *this;
	}

	D3DXINLINE float &Quaternion::operator [](int idx)
	{
		return *(&x + idx);
	}

	D3DXINLINE float Quaternion::operator [](int idx) const
	{
		return *(&x + idx);
	}

	D3DXINLINE const Quaternion Quaternion::operator +(const Quaternion &quat) const
	{
		return Quaternion
		(
			x + quat.x,
			y + quat.y,
			z + quat.z,
			w + quat.w
		);
	}

	D3DXINLINE const Quaternion Quaternion::operator -(const Quaternion &quat) const
	{
		return Quaternion
		(
			x - quat.x,
			y - quat.y,
			z - quat.z,
			w - quat.w
		);
	}

	D3DXINLINE const Quaternion Quaternion::operator *(const Quaternion &quat) const
	{
		return Quaternion
		(
			((((w * quat.x) + (x * quat.w)) + (y * quat.z)) - (z * quat.y)),
			((((w * quat.y) + (y * quat.w)) + (z * quat.x)) - (x * quat.z)),
			((((w * quat.z) + (z * quat.w)) + (x * quat.y)) - (y * quat.x)),
			((((w * quat.w) - (x * quat.x)) - (y * quat.y)) - (z * quat.z))
		);
	}

	D3DXINLINE const Quaternion Quaternion::operator *(float scalar) const
	{
		return Quaternion(x * scalar, y * scalar, z * scalar, w * scalar);
	}

	D3DXINLINE const Quaternion Quaternion::operator /(float scalar) const
	{
		return Quaternion(x / scalar, y / scalar, z / scalar, w / scalar);
	}

	D3DXINLINE Quaternion &Quaternion::operator +=(const Quaternion &_quat)
	{
		*this = *this + _quat;
		return *this;
	}

	D3DXINLINE Quaternion &Quaternion::operator -=(const Quaternion &_quat)
	{
		*this = *this - _quat;
		return *this;
	}
	D3DXINLINE Quaternion &Quaternion::operator *=(const Quaternion &_quat)
	{
		*this = *this * _quat;
		return *this;
	}

	D3DXINLINE Quaternion &Quaternion::operator *=(float scalar)
	{
		*this = *this * scalar;
		return *this;
	}

	D3DXINLINE Quaternion &Quaternion::operator /=(float scalar)
	{
		*this = *this / scalar;
		return *this;
	}

	D3DXINLINE const Quaternion Quaternion::operator -() const
	{
		return Quaternion(-x, -y, -z, -w);
	}

	//Accessor
	D3DXINLINE float Quaternion::EulerX(void) const
	{
		return atan2f(2 * (y * z + w * x), 1 - (2 * (x * x + y * y)));
	}

	D3DXINLINE float Quaternion::EulerY(void) const
	{
		return asinf(-2 * (x * z - w * y));
	}
	D3DXINLINE float Quaternion::EulerZ(void) const
	{
		return atan2f(2 * (x * y + w * z), 1 - (2 * (y * y + z * z)));
	}


	//Functions
	D3DXINLINE const Quaternion operator *(float scalar, const Quaternion &quat)
	{
		return quat * scalar;
	}

	D3DXINLINE const Vector3 Rotate(const Quaternion &unitQuat, const Vector3 &vec)
	{
		float tempX, tempY, tempZ, tempW;
		tempX = (((unitQuat.w * vec.x) + (unitQuat.y * vec.z)) - (unitQuat.z * vec.y));
		tempY = (((unitQuat.w * vec.y) + (unitQuat.z * vec.x)) - (unitQuat.x * vec.z));
		tempZ = (((unitQuat.w * vec.z) + (unitQuat.x * vec.y)) - (unitQuat.y * vec.x));
		tempW = (((unitQuat.x * vec.x) + (unitQuat.y * vec.y)) + (unitQuat.z * vec.z));
		return Vector3(
			((((tempW * unitQuat.x) + (tempX * unitQuat.w)) - (tempY * unitQuat.z)) + (tempZ * unitQuat.y)),
			((((tempW * unitQuat.y) + (tempY * unitQuat.w)) - (tempZ * unitQuat.x)) + (tempX * unitQuat.z)),
			((((tempW * unitQuat.z) + (tempZ * unitQuat.w)) - (tempX * unitQuat.y)) + (tempY * unitQuat.x))
		);
	}

	D3DXINLINE float Dot(const Quaternion &quat0, const Quaternion &quat1)
	{
		float result;
		result = (quat0.x * quat1.x);
		result = (result + (quat0.y * quat1.y));
		result = (result + (quat0.z * quat1.z));
		result = (result + (quat0.w * quat1.w));
		return result;
	}

	D3DXINLINE float Norm(const Quaternion &quat)
	{
		float result;
		result = (quat.x * quat.x);
		result = (result + (quat.y * quat.y));
		result = (result + (quat.z * quat.z));
		result = (result + (quat.w * quat.w));
		return result;
	}

	D3DXINLINE float Length(const Quaternion &quat)
	{
		return ::sqrtf(Norm(quat));
	}

	D3DXINLINE const Quaternion Normalize(const Quaternion &quat)
	{
		float lenSqr, lenInv;
		lenSqr = Norm(quat);
		lenInv = (1.0f / sqrtf(lenSqr));
		return Quaternion(
			(quat.x * lenInv),
			(quat.y * lenInv),
			(quat.z * lenInv),
			(quat.w * lenInv)
		);
	}

	D3DXINLINE const Quaternion Lerp(float t, const Quaternion &start, const Quaternion &end, bool useClamp)
	{
		if (!useClamp)
			return (start + ((end - start) * t));
		else
			return (t < 0.0f ? start : (t > 1.0f ? end : (start + ((end - start) * t))));
	}

	D3DXINLINE const Quaternion Slerp(float t, const Quaternion &unitQuat0, const Quaternion &unitQuat1, bool useClamp)
	{
		Quaternion start;
		float recipSinAngle, scale0, scale1, cosAngle, angle;
		cosAngle = Dot(unitQuat0, unitQuat1);
		if (cosAngle < 0.0f) {
			cosAngle = -cosAngle;
			start = (-unitQuat0);
		}
		else {
			start = unitQuat0;
		}
		if (cosAngle < SLERP_TOL) {
			angle = acosf(cosAngle);
			recipSinAngle = (1.0f / sinf(angle));
			scale0 = (sinf(((1.0f - t) * angle)) * recipSinAngle);
			scale1 = (sinf((t * angle)) * recipSinAngle);
		}
		else {
			scale0 = (1.0f - t);
			scale1 = t;
		}

		if (!useClamp)
			return ((start * scale0) + (unitQuat1 * scale1));
		else
			return (t < 0.0f ? unitQuat0 : (t > 1.0f ? unitQuat1 : ((start * scale0) + (unitQuat1 * scale1))));
	}

}

#endif
