//==========================================================
// 概要  :Vector2クラスの実装
// Author:Itsuki Namito
//==========================================================

#ifndef _BASE_MATH_VECTOR2_H_
#define _BASE_MATH_VECTOR2_H_

//Constants
#define SLERP_TOL (0.999f)

namespace math
{
	//Constructers
	D3DXINLINE Vector2::Vector2(const Vector2 &vec)
	{
		*this = vec;
	}

	D3DXINLINE Vector2::Vector2(float _x, float _y)
	{
		x = _x;
		y = _y;
	}

	D3DXINLINE Vector2::Vector2(float scalar)
	{
		x = scalar;
		y = scalar;
	}

	//Static construct
	D3DXINLINE const Vector2 Vector2::zero()
	{
		return Vector2(0.0f, 0.0f);
	}

	D3DXINLINE const Vector2 Vector2::one()
	{
		return Vector2(1.0f, 1.0f);
	}

	D3DXINLINE const Vector2 Vector2::right()
	{
		return Vector2(1.0f, 0.0f);
	}

	D3DXINLINE const Vector2 Vector2::left()
	{
		return Vector2(-1.0f, 0.0f);
	}

	D3DXINLINE const Vector2 Vector2::up()
	{
		return Vector2(0.0f, 1.0f);
	}

	D3DXINLINE const Vector2 Vector2::down()
	{
		return Vector2(0.0f, -1.0f);
	}

	//Operator
	D3DXINLINE Vector2 &Vector2::operator =(const Vector2 & vec)
	{
		x = vec.x;
		y = vec.y;
		return *this;
	}

	D3DXINLINE float &Vector2::operator [](int idx)
	{
		return *(&x + idx);
	}

	D3DXINLINE float Vector2::operator [](int idx) const
	{
		return *(&x + idx);
	}


	D3DXINLINE const Vector2 Vector2::operator +(const Vector2 & vec) const
	{
		return Vector2
		(
			(x + vec.x),
			(y + vec.y)
		);
	}

	D3DXINLINE const Vector2 Vector2::operator -(const Vector2 & vec) const
	{
		return Vector2
		(
			(x - vec.x),
			(y - vec.y)
		);
	}

	D3DXINLINE const Vector2 Vector2::operator *(float scalar) const
	{
		return Vector2
		(
			(x * scalar),
			(y * scalar)
		);
	}

	D3DXINLINE const Vector2 Vector2::operator /(float scalar) const
	{
		return Vector2
		(
			(x / scalar),
			(y / scalar)
		);
	}

	D3DXINLINE Vector2 &Vector2::operator +=(const Vector2 & vec)
	{
		*this = *this + vec;
		return *this;
	}

	D3DXINLINE Vector2 &Vector2::operator -=(const Vector2 & vec)
	{
		*this = *this - vec;
		return *this;
	}

	D3DXINLINE Vector2 &Vector2::operator *=(float scalar)
	{
		*this = *this * scalar;
		return *this;
	}

	D3DXINLINE Vector2 &Vector2::operator /=(float scalar)
	{
		*this = *this / scalar;
		return *this;
	}

	D3DXINLINE const Vector2 Vector2::operator -() const
	{
		return Vector2
		(
			-x,
			-y
		);
	}

	D3DXINLINE Vector2::operator b2Vec2()
	{
		return b2Vec2(x, y);
	}

	//Accessor
	D3DXINLINE Vector2 &Vector2::element(int idx, float value)
	{
		*(&x + idx) = value;
		return *this;
	}

	D3DXINLINE float Vector2::element(int idx) const
	{
		return *(&x + idx);
	}

	// Member Functions
	D3DXINLINE void Vector2::Normalize(void)
	{
		D3DXVec2Normalize(this, this);
	}

	//Functions
	D3DXINLINE const Vector2 operator *(float scalar, const Vector2 &vec)
	{
		return vec * scalar;
	}

	D3DXINLINE void MulPerElem(Vector2 &out, const Vector2 &vec0, const Vector2 &vec1)	//対応する各要素を掛ける
	{
		out.x = vec0.x * vec1.x;
		out.y = vec0.y * vec1.y;
	}

	D3DXINLINE const Vector2 MulPerElem(const Vector2 & vec0, const Vector2 & vec1)	//対応する各要素を掛ける
	{
		return Vector2
		(
			(vec0.x * vec1.x),
			(vec0.y * vec1.y)
		);
	}

	D3DXINLINE void DivPerElem(Vector2 &out, const Vector2 &vec0, const Vector2 &vec1)	//対応する各要素を割る
	{
		out.x = vec0.x / vec1.x;
		out.y = vec0.y / vec1.y;
	}

	D3DXINLINE const Vector2 DivPerElem(const Vector2 &vec0, const Vector2 &vec1)		//対応する各要素を割る
	{
		return Vector2
		(
			(vec0.x / vec1.x),
			(vec0.y / vec1.y)
		);
	}

	D3DXINLINE void AbsPerElem(Vector2 &out, const Vector2 &vec)	//各要素の絶対値を求める
	{
		out.x = fabsf(vec.x);
		out.y = fabsf(vec.y);
	}

	D3DXINLINE const Vector2 AbsPerElem(const Vector2 &vec)			//各要素の絶対値を求める
	{
		return Vector2
		(
			fabsf(vec.x),
			fabsf(vec.y)
		);
	}

	D3DXINLINE const Vector2 MaxPerElem(const Vector2 &vec0, const Vector2 &vec1)	//2つの行列の各要素の大きい方を取る
	{
		return Vector2(
			(vec0.x > vec1.x) ? vec0.x : vec1.x,
			(vec0.y > vec1.y) ? vec0.y : vec1.y
		);
	}

	D3DXINLINE const Vector2 MinPerElem(const Vector2 &vec0, const Vector2 &vec1)	//2つの行列の各要素の小さい方を取る
	{
		return Vector2(
			(vec0.x < vec1.x) ? vec0.x : vec1.x,
			(vec0.y < vec1.y) ? vec0.y : vec1.y
		);
	}

	D3DXINLINE float MaxElem(const Vector2 &vec)	//x,y,zの中の最大値を求める
	{
		return (vec.x > vec.y) ? vec.x : vec.y;
	}

	D3DXINLINE float MinElem(const Vector2 &vec)	//x,y,zの中の最小値を求める
	{
		return (vec.x < vec.y) ? vec.x : vec.y;
	}

	D3DXINLINE float Sum(const Vector2 &vec)		//x,y,zの和
	{
		return (vec.x + vec.y);
	}

	D3DXINLINE float Dot(const Vector2 &vec0, const Vector2 &vec1)					//内積を求める
	{
		//return Sum(MulPerElem(vec0, vec1));
		return D3DXVec2Dot(&vec0, &vec1);
	}

	D3DXINLINE float Cross(const Vector2 &vec0, const Vector2 &vec1)		//外積を求める
	{
		return vec0.x * vec1.y - vec0.y * vec1.x;
	}

	D3DXINLINE float Length(const Vector2 &vec)									//大きさを求める
	{
		return D3DXVec2Length(&vec);
	}

	D3DXINLINE double LengthD(const Vector2 &vec)
	{
		return sqrt((double)((vec.x * vec.x) + (vec.y * vec.y)));
	}

	D3DXINLINE float LengthSq(const Vector2 &vec)									//大きさの2乗を求める(√の計算がない分高速)
	{
		return D3DXVec2LengthSq(&vec);
	}

	//正規化する
	D3DXINLINE void Normalize(Vector2 &out, const Vector2 &vec)
	{
		D3DXVec2Normalize(&out, &vec);
	}

	//正規化する
	D3DXINLINE const Vector2 Normalize(const Vector2 &vec)
	{
		Vector2 result;
		Normalize(result, vec);
		return result;
	}

	//線形補間を行う。useClampをtrueにすると戻り値はstartとendを結ぶ線分上に限定される
	D3DXINLINE const Vector2 Lerp(float t, const Vector2 &start, const Vector2 &end, bool useClamp)
	{
		Vector2 result;

		result = t * end + (1.0f - t) * start;

		if (useClamp)
		{
			result = (t < 0.0f) ? start : result;
			result = (t > 1.0f) ? end : result;
		}

		return result;
	}

	//球面線形補間を行う。useClampをtrueにすると戻り値はstart～end間に限定される
	D3DXINLINE const Vector2 Slerp(float t, const Vector2 &start, const Vector2 &end, bool useClamp)
	{
		Vector2 result;

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
	D3DXINLINE const Vector2 Bezier(float t, const Vector2 &sp, const Vector2 &cp0, const Vector2 &cp1, const Vector2 &ep, bool useClamp)
	{
		Vector2 result;
		result = (powf(t, 3) * sp) + (powf(t, 2) * (1.0f - t) * cp0) +
			(t * powf((1.0f - t), 2) * cp1) + (powf((1.0f - t), 3) * ep);

		if (useClamp)
		{
			result = (t < 0.0f) ? sp : result;
			result = (t > 1.0f) ? ep : result;
		}

		return result;
	}

	// 二つのベクトルがなす角度を返します。(鋭角、弧度法)
	D3DXINLINE const float Angle(const Vector2 &vec0, const Vector2 &vec1)
	{
		return acosf(Dot(vec0, vec1) / (Length(vec0) * Length(vec1)));
	}

	// x軸正方向とのなす角度を弧度法で返します。
	D3DXINLINE const float Angle(const Vector2 &vec)
	{
		return atan2f(vec.y, vec.x);
	}

	// ベクトルを指定の角度分、反時計回りに回転させます
	D3DXINLINE const Vector2 Rotate(const Vector2 &vec, const float &degree)
	{
		float rad = D3DXToRadian(degree);
		float cos = cosf(rad), sin = sinf(rad);

		return Vector2(vec.x * cos - vec.y * sin, vec.x * sin + vec.y * cos);
	}

	D3DXINLINE const bool InFan(const Vector2 &checked, float min, float max)
	{
		float angle = Angle(checked);

		return (angle < min) ? false :
			(angle > max) ? false : true;
	}
}

#endif