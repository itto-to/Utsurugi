//==========================================================
// 概要  :Vector3クラスの実装
// Author:Itsuki Namito
//==========================================================

#ifndef _BASE_MATH_VECTOR3_H_
#define _BASE_MATH_VECTOR3_H_

namespace shadowpartner
{
//Constructers
	D3DXINLINE Vector3::Vector3(const Vector3 &vec)
	{
		*this = vec;
	}

	D3DXINLINE Vector3::Vector3(float _x, float _y, float _z)
	{
		x = _x;
		y = _y;
		z = _z;
	}

	D3DXINLINE Vector3::Vector3(const Vector2 xy, float _z)
	{
		x = xy.x;
		y = xy.y;
		z = _z;
	}


	D3DXINLINE Vector3::Vector3(float scalar)
	{
		x = scalar;
		y = scalar;
		z = scalar;
	}

	//Static construct
	D3DXINLINE const Vector3 Vector3::zero()
	{
		return Vector3(0.0f, 0.0f, 0.0f);
	}

	D3DXINLINE const Vector3 Vector3::one()
	{
		return Vector3(1.0f, 1.0f, 1.0f);
	}

	D3DXINLINE const Vector3 Vector3::right()
	{
		return Vector3(1.0f, 0.0f, 0.0f);
	}

	D3DXINLINE const Vector3 Vector3::left()
	{
		return Vector3(-1.0f, 0.0f, 0.0f);
	}

	D3DXINLINE const Vector3 Vector3::up()
	{
		return Vector3(0.0f, 1.0f, 0.0f);
	}

	D3DXINLINE const Vector3 Vector3::down()
	{
		return Vector3(0.0f, -1.0f, 0.0f);
	}

	D3DXINLINE const Vector3 Vector3::forward()
	{
		return Vector3(0.0f, 0.0f, 1.0f);
	}

	D3DXINLINE const Vector3 Vector3::back()
	{
		return Vector3(0.0f, 0.0f, -1.0f);
	}

	//Operator
	D3DXINLINE Vector3 &Vector3::operator =(const Vector3 & vec)
	{
		x = vec.x;
		y = vec.y;
		z = vec.z;
		return *this;
	}

	D3DXINLINE float &Vector3::operator [](int idx)
	{
		return *(&x + idx);
	}

	D3DXINLINE float Vector3::operator [](int idx) const
	{
		return *(&x + idx);
	}


	D3DXINLINE const Vector3 Vector3::operator +(const Vector3 & vec) const
	{
		return Vector3
		(
			(x + vec.x),
			(y + vec.y),
			(z + vec.z)
		);
	}

	D3DXINLINE const Vector3 Vector3::operator -(const Vector3 & vec) const
	{
		return Vector3
		(
			(x - vec.x),
			(y - vec.y),
			(z - vec.z)
		);
	}

	D3DXINLINE const Vector3 Vector3::operator *(float scalar) const
	{
		return Vector3
		(
			(x * scalar),
			(y * scalar),
			(z * scalar)
		);
	}

	D3DXINLINE const Vector3 Vector3::operator /(float scalar) const
	{
		return Vector3
		(
			(x / scalar),
			(y / scalar),
			(z / scalar)
		);
	}

	D3DXINLINE Vector3 &Vector3::operator +=(const Vector3 & vec)
	{
		*this = *this + vec;
		return *this;
	}

	D3DXINLINE Vector3 &Vector3::operator -=(const Vector3 & vec)
	{
		*this = *this - vec;
		return *this;
	}

	D3DXINLINE Vector3 &Vector3::operator *=(float scalar)
	{
		*this = *this * scalar;
		return *this;
	}

	D3DXINLINE Vector3 &Vector3::operator /=(float scalar)
	{
		*this = *this / scalar;
		return *this;
	}

	D3DXINLINE const Vector3 Vector3::operator -() const
	{
		return Vector3
		(
			-x,
			-y,
			-z
		);
	}

	//Accessor

	
	D3DXINLINE Vector3 &Vector3::element(int idx, float value)
	{
		*(&x + idx) = value;
		return *this;
	}

	D3DXINLINE float Vector3::element(int idx) const
	{
		return *(&x + idx);
		
	}

	// Member Functions
	D3DXINLINE void Vector3::Normalize(void)
	{
		D3DXVec3Normalize(this, this);
	}

	//Functions
	D3DXINLINE const Vector3 operator *(float scalar, const Vector3 &vec)
	{
		return vec * scalar;
	}

	D3DXINLINE void MulPerElem(Vector3 &out, const Vector3 &vec0, const Vector3 &vec1)	//対応する各要素を掛ける
	{
		out.x = vec0.x * vec1.x;
		out.y = vec0.y * vec1.y;
		out.z = vec0.z * vec1.z;
	}

	D3DXINLINE const Vector3 MulPerElem(const Vector3 & vec0, const Vector3 & vec1)	//対応する各要素を掛ける
	{
		return Vector3
		(
			(vec0.x * vec1.x),
			(vec0.y * vec1.y),
			(vec0.z * vec1.z)
		);
	}

	D3DXINLINE void DivPerElem(Vector3 &out, const Vector3 &vec0, const Vector3 &vec1)	//対応する各要素を割る
	{
		out.x = vec0.x / vec1.x;
		out.y = vec0.y / vec1.y;
		out.z = vec0.z / vec1.z;
	}

	D3DXINLINE const Vector3 DivPerElem(const Vector3 &vec0, const Vector3 &vec1)		//対応する各要素を割る
	{
		return Vector3
		(
			(vec0.x / vec1.x),
			(vec0.y / vec1.y),
			(vec0.z / vec1.z)
		);
	}

	D3DXINLINE void AbsPerElem(Vector3 &out, const Vector3 &vec)	//各要素の絶対値を求める
	{
		out.x = fabsf(vec.x);
		out.y = fabsf(vec.y);
		out.z = fabsf(vec.z);
	}

	D3DXINLINE const Vector3 AbsPerElem(const Vector3 &vec)			//各要素の絶対値を求める
	{
		return Vector3
		(
			fabsf(vec.x),
			fabsf(vec.y),
			fabsf(vec.z)
		);
	}

	D3DXINLINE const Vector3 MaxPerElem(const Vector3 &vec0, const Vector3 &vec1)	//2つの行列の各要素の大きい方を取る
	{
		return Vector3(
			(vec0.x > vec1.x) ? vec0.x : vec1.x,
			(vec0.y > vec1.y) ? vec0.y : vec1.y,
			(vec0.z > vec1.z) ? vec0.z : vec1.z
		);
	}

	D3DXINLINE const Vector3 MinPerElem(const Vector3 &vec0, const Vector3 &vec1)	//2つの行列の各要素の小さい方を取る
	{
		return Vector3(
			(vec0.x < vec1.x) ? vec0.x : vec1.x,
			(vec0.y < vec1.y) ? vec0.y : vec1.y,
			(vec0.z < vec1.z) ? vec0.z : vec1.z
		);
	}

	D3DXINLINE float MaxElem(const Vector3 &vec)	//x,y,zの中の最大値を求める
	{
		float max;
		max = (vec.x > vec.y) ? vec.x : vec.y;
		max = (vec.z > max) ? vec.z : max;
		return max;
	}

	D3DXINLINE float MinElem(const Vector3 &vec)	//x,y,zの中の最小値を求める
	{
		float min;
		min = (vec.x < vec.y) ? vec.x : vec.y;
		min = (vec.z < min) ? vec.z : min;
		return min;
	}

	D3DXINLINE float Sum(const Vector3 &vec)		//x,y,zの和
	{
		return (vec.x + vec.y + vec.z);
	}

	D3DXINLINE float Dot(const Vector3 &vec0, const Vector3 &vec1)					//内積を求める
	{
		//return Sum(MulPerElem(vec0, vec1));
		return D3DXVec3Dot(&vec0, &vec1);
	}

	D3DXINLINE void Cross(Vector3 &out, const Vector3 &vec0, const Vector3 &vec1)	//外積を求める
	{
		out.x = (vec0.y * vec1.z) - (vec0.z * vec1.y);
		out.y = (vec0.z * vec1.x) - (vec0.x * vec1.z);
		out.z = (vec0.x * vec1.y) - (vec0.y * vec1.x);
	}

	D3DXINLINE const Vector3 Cross(const Vector3 &vec0, const Vector3 &vec1)		//外積を求める
	{
		Vector3 result;
		Cross(result, vec0, vec1);
		return result;
	}

	D3DXINLINE float Length(const Vector3 &vec)									//大きさを求める
	{
		return D3DXVec3Length(&vec);
	}

	D3DXINLINE float LengthSq(const Vector3 &vec)									//大きさの2乗を求める(√の計算がない分高速)
	{
		return D3DXVec3LengthSq(&vec);
	}

	//正規化する
	D3DXINLINE void Normalize(Vector3 &out, const Vector3 &vec)
	{
		D3DXVec3Normalize(&out, &vec);
	}

	//正規化する
	D3DXINLINE const Vector3 Normalize(const Vector3 &vec)
	{
		Vector3 result;
		Normalize(result, vec);
		return result;
	}

	//線形補間を行う。useClampをtrueにすると戻り値はstartとendを結ぶ線分上に限定される
	D3DXINLINE const Vector3 Lerp(float t, const Vector3 &start, const Vector3 &end, bool useClamp)
	{
		Vector3 result;

		result = t * end + (1.0f - t) * start;

		if (useClamp)
		{
			result = (t < 0.0f) ? start : result;
			result = (t > 1.0f) ? end : result;
		}

		return result;
	}

	//球面線形補間を行う。useClampをtrueにすると戻り値はstart～end間に限定される
	D3DXINLINE const Vector3 Slerp(float t, const Vector3 &start, const Vector3 &end, bool useClamp)
	{
		Vector3 result;

		float recipSinAngle, scale0, scale1, conAngle, angle;
		conAngle = Dot(start, end);

		if (conAngle < SLERP_TOL)
		{
			angle = acosf(conAngle);
			recipSinAngle = (1.0f / sinf(angle));
			scale0 = (sinf(((1.0f - t) * angle)) * recipSinAngle);
			scale1 = (sinf((t * angle)) * recipSinAngle);
		}
		else
		{
			scale0 = (1.0f - t);
			scale1 = t;
		}

		result = ((start * scale0) + (end * scale1));

		if (useClamp)
		{
			result = (t < 0.0f) ? start : result;
			result = (t > 1.0f) ? end : result;
		}

		return result;
	}

	//ベジエ曲線で補間する。useClampをtrueにすると戻り値はstart～end間に限定される
	D3DXINLINE const Vector3 Bezier(float t, const Vector3 &sp, const Vector3 &cp0, const Vector3 &cp1, const Vector3 &ep, bool useClamp)
	{
		Vector3 result;
		result = (powf(t, 3) * sp) + (powf(t, 2) * (1.0f - t) * cp0) +
			(t * powf((1.0f - t), 2) * cp1) + (powf((1.0f - t), 3) * ep);

		if (useClamp)
		{
			result = (t < 0.0f) ? sp : result;
			result = (t > 1.0f) ? ep : result;
		}

		return result;
	}

} 

#endif
