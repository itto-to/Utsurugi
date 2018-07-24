//==========================================================
// �T�v  :Vector2�N���X�̎���
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

	D3DXINLINE void MulPerElem(Vector2 &out, const Vector2 &vec0, const Vector2 &vec1)	//�Ή�����e�v�f���|����
	{
		out.x = vec0.x * vec1.x;
		out.y = vec0.y * vec1.y;
	}

	D3DXINLINE const Vector2 MulPerElem(const Vector2 & vec0, const Vector2 & vec1)	//�Ή�����e�v�f���|����
	{
		return Vector2
		(
			(vec0.x * vec1.x),
			(vec0.y * vec1.y)
		);
	}

	D3DXINLINE void DivPerElem(Vector2 &out, const Vector2 &vec0, const Vector2 &vec1)	//�Ή�����e�v�f������
	{
		out.x = vec0.x / vec1.x;
		out.y = vec0.y / vec1.y;
	}

	D3DXINLINE const Vector2 DivPerElem(const Vector2 &vec0, const Vector2 &vec1)		//�Ή�����e�v�f������
	{
		return Vector2
		(
			(vec0.x / vec1.x),
			(vec0.y / vec1.y)
		);
	}

	D3DXINLINE void AbsPerElem(Vector2 &out, const Vector2 &vec)	//�e�v�f�̐�Βl�����߂�
	{
		out.x = fabsf(vec.x);
		out.y = fabsf(vec.y);
	}

	D3DXINLINE const Vector2 AbsPerElem(const Vector2 &vec)			//�e�v�f�̐�Βl�����߂�
	{
		return Vector2
		(
			fabsf(vec.x),
			fabsf(vec.y)
		);
	}

	D3DXINLINE const Vector2 MaxPerElem(const Vector2 &vec0, const Vector2 &vec1)	//2�̍s��̊e�v�f�̑傫���������
	{
		return Vector2(
			(vec0.x > vec1.x) ? vec0.x : vec1.x,
			(vec0.y > vec1.y) ? vec0.y : vec1.y
		);
	}

	D3DXINLINE const Vector2 MinPerElem(const Vector2 &vec0, const Vector2 &vec1)	//2�̍s��̊e�v�f�̏������������
	{
		return Vector2(
			(vec0.x < vec1.x) ? vec0.x : vec1.x,
			(vec0.y < vec1.y) ? vec0.y : vec1.y
		);
	}

	D3DXINLINE float MaxElem(const Vector2 &vec)	//x,y,z�̒��̍ő�l�����߂�
	{
		return (vec.x > vec.y) ? vec.x : vec.y;
	}

	D3DXINLINE float MinElem(const Vector2 &vec)	//x,y,z�̒��̍ŏ��l�����߂�
	{
		return (vec.x < vec.y) ? vec.x : vec.y;
	}

	D3DXINLINE float Sum(const Vector2 &vec)		//x,y,z�̘a
	{
		return (vec.x + vec.y);
	}

	D3DXINLINE float Dot(const Vector2 &vec0, const Vector2 &vec1)					//���ς����߂�
	{
		//return Sum(MulPerElem(vec0, vec1));
		return D3DXVec2Dot(&vec0, &vec1);
	}

	D3DXINLINE float Cross(const Vector2 &vec0, const Vector2 &vec1)		//�O�ς����߂�
	{
		return vec0.x * vec1.y - vec0.y * vec1.x;
	}

	D3DXINLINE float Length(const Vector2 &vec)									//�傫�������߂�
	{
		return D3DXVec2Length(&vec);
	}

	D3DXINLINE double LengthD(const Vector2 &vec)
	{
		return sqrt((double)((vec.x * vec.x) + (vec.y * vec.y)));
	}

	D3DXINLINE float LengthSq(const Vector2 &vec)									//�傫����2������߂�(��̌v�Z���Ȃ�������)
	{
		return D3DXVec2LengthSq(&vec);
	}

	//���K������
	D3DXINLINE void Normalize(Vector2 &out, const Vector2 &vec)
	{
		D3DXVec2Normalize(&out, &vec);
	}

	//���K������
	D3DXINLINE const Vector2 Normalize(const Vector2 &vec)
	{
		Vector2 result;
		Normalize(result, vec);
		return result;
	}

	//���`��Ԃ��s���BuseClamp��true�ɂ���Ɩ߂�l��start��end�����Ԑ�����Ɍ��肳���
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

	//���ʐ��`��Ԃ��s���BuseClamp��true�ɂ���Ɩ߂�l��start�`end�ԂɌ��肳���
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

	//�x�W�G�Ȑ��ŕ�Ԃ���BuseClamp��true�ɂ���Ɩ߂�l��start�`end�ԂɌ��肳���
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

	// ��̃x�N�g�����Ȃ��p�x��Ԃ��܂��B(�s�p�A�ʓx�@)
	D3DXINLINE const float Angle(const Vector2 &vec0, const Vector2 &vec1)
	{
		return acosf(Dot(vec0, vec1) / (Length(vec0) * Length(vec1)));
	}

	// x���������Ƃ̂Ȃ��p�x���ʓx�@�ŕԂ��܂��B
	D3DXINLINE const float Angle(const Vector2 &vec)
	{
		return atan2f(vec.y, vec.x);
	}

	// �x�N�g�����w��̊p�x���A�����v���ɉ�]�����܂�
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