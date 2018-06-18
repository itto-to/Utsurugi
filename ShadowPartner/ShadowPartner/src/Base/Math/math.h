//==========================================================
// 概要  :算術クラス
// Author:Itsuki Namito
//==========================================================

#ifndef _BASE_MATH_MATH_
#define _BASE_MATH_MATH_

#include <d3dx9.h>
#pragma comment (lib,"d3dx9.lib")

namespace math
{
	//*****************************************************************************
	// クラスの宣言
	//*****************************************************************************
	class Vector2;
	class Vector3;
	class Quaternion;
	class Matrix3x3;
	class Matrix4x3;

	//*****************************************************************************
	// Vector2クラスの宣言
	//*****************************************************************************
	class Vector2 : public D3DXVECTOR2
	{
	private:
	public:
		D3DXINLINE Vector2() {};
		D3DXINLINE Vector2(const Vector2 &vec);
		D3DXINLINE Vector2(float _x, float _y);
		D3DXINLINE Vector2(float scalar);

		//Static construct
		static D3DXINLINE const Vector2 zero();
		static D3DXINLINE const Vector2 one();

		static D3DXINLINE const Vector2 right();
		static D3DXINLINE const Vector2 left();
		static D3DXINLINE const Vector2 up();
		static D3DXINLINE const Vector2 down();

		//Operator
		D3DXINLINE Vector2 &operator =(const Vector2 & vec);

		D3DXINLINE float &operator [](int idx);
		D3DXINLINE float operator [](int idx) const;

		D3DXINLINE const Vector2 operator +(const Vector2 & vec) const;
		D3DXINLINE const Vector2 operator -(const Vector2 & vec) const;

		D3DXINLINE const Vector2 operator *(float scalar) const;
		D3DXINLINE const Vector2 operator /(float scalar) const;

		D3DXINLINE Vector2 &operator +=(const Vector2 & vec);
		D3DXINLINE Vector2 &operator -=(const Vector2 & vec);
		D3DXINLINE Vector2 &operator *=(float scalar);
		D3DXINLINE Vector2 &operator /=(float scalar);

		D3DXINLINE const Vector2 operator -() const;

		//Accessor
		D3DXINLINE Vector2 &element(int idx, float value);
		D3DXINLINE float element(int idx) const;

		//Functions
		D3DXINLINE void Normalize(void);

	};

	//Functions
	D3DXINLINE const Vector2 operator *(float scalar, const Vector2 &vec);
	D3DXINLINE void MulPerElem(Vector2 &out, const Vector2 &vec0, const Vector2 &vec1);	//対応する各要素を掛ける
	D3DXINLINE const Vector2 MulPerElem(const Vector2 & vec0, const Vector2 & vec1);	//対応する各要素を掛ける
	D3DXINLINE void DivPerElem(Vector2 &out, const Vector2 &vec0, const Vector2 &vec1);	//対応する各要素を割る
	D3DXINLINE const Vector2 DivPerElem(const Vector2 &vec0, const Vector2 &vec1);		//対応する各要素を割る
	D3DXINLINE void AbsPerElem(Vector2 &out, const Vector2 &vec);	//各要素の絶対値を求める
	D3DXINLINE const Vector2 AbsPerElem(const Vector2 &vec);		//各要素の絶対値を求める
	D3DXINLINE const Vector2 MaxPerElem(const Vector2 &vec0, const Vector2 &vec1);	//2つの行列の各要素の大きい方を取る
	D3DXINLINE const Vector2 MinPerElem(const Vector2 &vec0, const Vector2 &vec1);	//2つの行列の各要素の小さい方を取る
	D3DXINLINE float MaxElem(const Vector2 &vec);	//x,y,zの中の最大値を求める
	D3DXINLINE float MinElem(const Vector2 &vec);	//x,y,zの中の最小値を求める
	D3DXINLINE float Sum(const Vector2 &vec);		//x,y,zの和
	D3DXINLINE float Dot(const Vector2 &vec0, const Vector2 &vec1);					//内積を求める
	D3DXINLINE float Cross(const Vector2 &vec0, const Vector2 &vec1);		//外積を求める
	D3DXINLINE float Length(const Vector2 &vec);									//大きさを求める
	D3DXINLINE double LengthD(const Vector2 &vec);									//doubleで大きさを求める
	D3DXINLINE float LengthSq(const Vector2 &vec);									//大きさの2乗を求める(√の計算がない分高速)
	D3DXINLINE void Normalize(Vector2 &out, const Vector2 &vec);					//正規化する
	D3DXINLINE const Vector2 Normalize(const Vector2 &vec);							//正規化する
	//線形補間を行う。useClampをtrueにすると戻り値はstartとendを結ぶ線分上に限定される
	D3DXINLINE const Vector2 Lerp(float t, const Vector2 &start, const Vector2 &end, bool useClamp = false);
	//球面線形補間を行う。useClampをtrueにすると戻り値はstart～end間に限定される
	D3DXINLINE const Vector2 Slerp(float t, const Vector2 &start, const Vector2 &end, bool useClamp = false);
	//ベジエ曲線で補間する。useClampをtrueにすると戻り値はstart～end間に限定される
	D3DXINLINE const Vector2 Bezier(float t, const Vector2 &sp, const Vector2 &cp0, const Vector2 &cp1, const Vector2 &ep, bool useClamp = false);

	D3DXINLINE const float Angle(const Vector2 &vec0, const Vector2 &vec1);	// 二つのベクトルがなす角度を度数で返します。
	D3DXINLINE const float Angle(const Vector2 &vec);						// x軸正方向とのなす角度を度数で返します。

	D3DXINLINE const Vector2 Rotate(const Vector2 &vec,const float &degree);

	D3DXINLINE const bool InFan(const Vector2 &checked, float min, float max);	// checkedのAngleがminとmax（共に度数）の間にあるか

	//*****************************************************************************
	//*****************************************************************************
	// Vector3クラスの宣言
	//*****************************************************************************
	//*****************************************************************************
	class Vector3 : public D3DXVECTOR3
	{
	private:
	public:
		//Constructers
		D3DXINLINE Vector3() {};
		D3DXINLINE Vector3(const Vector3 &vec);
		D3DXINLINE Vector3(float x, float y, float z);
		D3DXINLINE Vector3(const Vector2 xy, float _z);
		D3DXINLINE Vector3(float scalar);

		//Static construct
		static D3DXINLINE const Vector3 zero();
		static D3DXINLINE const Vector3 one();

		static D3DXINLINE const Vector3 right();
		static D3DXINLINE const Vector3 left();
		static D3DXINLINE const Vector3 up();
		static D3DXINLINE const Vector3 down();
		static D3DXINLINE const Vector3 forward();
		static D3DXINLINE const Vector3 back();

		//Operator
		D3DXINLINE Vector3 &operator =(const Vector3 & vec);

		D3DXINLINE float &operator [](int idx);
		D3DXINLINE float operator [](int idx) const;

		D3DXINLINE const Vector3 operator +(const Vector3 & vec) const;
		D3DXINLINE const Vector3 operator -(const Vector3 & vec) const;

		D3DXINLINE const Vector3 operator *(float scalar) const;
		D3DXINLINE const Vector3 operator /(float scalar) const;

		D3DXINLINE Vector3 &operator +=(const Vector3 & vec);
		D3DXINLINE Vector3 &operator -=(const Vector3 & vec);
		D3DXINLINE Vector3 &operator *=(float scalar);
		D3DXINLINE Vector3 &operator /=(float scalar);

		D3DXINLINE const Vector3 operator -() const;

		//Accessor
		D3DXINLINE Vector3 &element(int idx, float value);
		D3DXINLINE float element(int idx) const;

		//Functions
		D3DXINLINE void Normalize(void);
	};
	//Functions
	D3DXINLINE const Vector3 operator *(float scalar, const Vector3 &vec);
	D3DXINLINE void MulPerElem(Vector3 &out, const Vector3 &vec0, const Vector3 &vec1);	//対応する各要素を掛ける
	D3DXINLINE const Vector3 MulPerElem(const Vector3 & vec0, const Vector3 & vec1);	//対応する各要素を掛ける
	D3DXINLINE void DivPerElem(Vector3 &out, const Vector3 &vec0, const Vector3 &vec1);	//対応する各要素を割る
	D3DXINLINE const Vector3 DivPerElem(const Vector3 &vec0, const Vector3 &vec1);		//対応する各要素を割る
	D3DXINLINE void AbsPerElem(Vector3 &out, const Vector3 &vec);	//各要素の絶対値を求める
	D3DXINLINE const Vector3 AbsPerElem(const Vector3 &vec);		//各要素の絶対値を求める
	D3DXINLINE const Vector3 MaxPerElem(const Vector3 &vec0, const Vector3 &vec1);	//2つの行列の各要素の大きい方を取る
	D3DXINLINE const Vector3 MinPerElem(const Vector3 &vec0, const Vector3 &vec1);	//2つの行列の各要素の小さい方を取る
	D3DXINLINE float MaxElem(const Vector3 &vec);	//x,y,zの中の最大値を求める
	D3DXINLINE float MinElem(const Vector3 &vec);	//x,y,zの中の最小値を求める
	D3DXINLINE float Sum(const Vector3 &vec);		//x,y,zの和
	D3DXINLINE float Dot(const Vector3 &vec0, const Vector3 &vec1);					//内積を求める
	D3DXINLINE void Cross(Vector3 &out, const Vector3 &vec0, const Vector3 &vec1);	//外積を求める
	D3DXINLINE const Vector3 Cross(const Vector3 &vec0, const Vector3 &vec1);		//外積を求める
	D3DXINLINE float Length(const Vector3 &vec);									//大きさを求める
	D3DXINLINE float LengthSq(const Vector3 &vec);									//大きさの2乗を求める(√の計算がない分高速)
	D3DXINLINE void Normalize(Vector3 &out, const Vector3 &vec);					//正規化する
	D3DXINLINE const Vector3 Normalize(const Vector3 &vec);							//正規化する
	D3DXINLINE void CrossMatrix(Matrix3x3 &out, const Vector3 &vec);				//3次元ベクトルを外積する行列
	D3DXINLINE const Matrix3x3 CrossMatrix(const Vector3 &vec);						//3次元ベクトルを外積する行列
																					//線形補間を行う。useClampをtrueにすると戻り値はstartとendを結ぶ線分上に限定される
	D3DXINLINE const Vector3 Lerp(float t, const Vector3 &start, const Vector3 &end, bool useClamp = false);
	//球面線形補間を行う。useClampをtrueにすると戻り値はstart～end間に限定される
	D3DXINLINE const Vector3 Slerp(float t, const Vector3 &start, const Vector3 &end, bool useClamp = false);
	//ベジエ曲線で補間する。useClampをtrueにすると戻り値はstart～end間に限定される
	D3DXINLINE const Vector3 Bezier(float t, const Vector3 &sp, const Vector3 &cp0, const Vector3 &cp1, const Vector3 &ep, bool useClamp = false);

	//*****************************************************************************
	//*****************************************************************************
	// Quaternionクラスの宣言
	//*****************************************************************************
	//*****************************************************************************
	class Quaternion : public D3DXQUATERNION
	{
	private:
	public:
		//Constructor
		D3DXINLINE Quaternion() { };
		D3DXINLINE Quaternion(const Quaternion &_quat);
		D3DXINLINE Quaternion(float x, float y, float z, float w);
		D3DXINLINE Quaternion(const Vector3 &xyz, float w);
		D3DXINLINE Quaternion(const Matrix3x3 &rotMat);	//回転行列で
		D3DXINLINE Quaternion(float scalar);

		//Static construct
		static D3DXINLINE const Quaternion Identity();
		static D3DXINLINE const Quaternion Rotation(const Vector3 &unitVec0, const Vector3 &unitVec1);
		static D3DXINLINE const Quaternion Rotation(float radians, const Vector3 &unitVec);
		static D3DXINLINE const Quaternion RotationX(float radians);
		static D3DXINLINE const Quaternion RotaitonY(float radians);
		static D3DXINLINE const Quaternion RotationZ(float radians);

		//Operator
		D3DXINLINE Quaternion &operator =(const Quaternion &_quat);
		D3DXINLINE float &operator [](int idx);
		D3DXINLINE float operator [](int idx) const;
		D3DXINLINE const Quaternion operator +(const Quaternion &_quat) const;
		D3DXINLINE const Quaternion operator -(const Quaternion &_quat) const;
		D3DXINLINE const Quaternion operator *(const Quaternion &_quat) const;
		D3DXINLINE const Quaternion operator *(float scalar) const;
		D3DXINLINE const Quaternion operator /(float scalar) const;
		D3DXINLINE Quaternion &operator +=(const Quaternion &_quat);
		D3DXINLINE Quaternion &operator -=(const Quaternion &_quat);
		D3DXINLINE Quaternion &operator *=(const Quaternion &_quat);
		D3DXINLINE Quaternion &operator *=(float scalar);
		D3DXINLINE Quaternion &operator /=(float scalar);
		D3DXINLINE const Quaternion operator -() const;

		//Accessor
		D3DXINLINE float EulerX(void) const;
		D3DXINLINE float EulerY(void) const;
		D3DXINLINE float EulerZ(void) const;
	};
	//Functions
	D3DXINLINE const Quaternion operator *(float scalar, const Quaternion &quat);
	D3DXINLINE const Vector3 Rotate(const Quaternion &unitQuat, const Vector3 &vec);
	D3DXINLINE float Dot(const Quaternion &quat0, const Quaternion &quat1);
	D3DXINLINE float Norm(const Quaternion &quat);
	D3DXINLINE float Length(const Quaternion &quat);
	D3DXINLINE const Quaternion Normalize(const Quaternion &quat);
	D3DXINLINE const Quaternion Lerp(float t, const Quaternion &start, const Quaternion &end, bool useClamp = false);
	D3DXINLINE const Quaternion Slerp(float t, const Quaternion &start, const Quaternion &end, bool useClamp = false);

	//*****************************************************************************
	//*****************************************************************************
	// Matrix3x3クラスの宣言
	//*****************************************************************************
	//*****************************************************************************
	class Matrix3x3
	{
	private:

	public:
		// Public Variables
		Vector3 col0;
		Vector3 col1;
		Vector3 col2;

		//Constructor
		D3DXINLINE Matrix3x3() {};
		D3DXINLINE Matrix3x3(const Matrix3x3 &mat);
		D3DXINLINE Matrix3x3(const Vector3 &_col0, const Vector3 &_col1, const Vector3 &_col2);
		D3DXINLINE Matrix3x3(const Quaternion &unitQuat);
		D3DXINLINE Matrix3x3(float scalar);

		//Static construct
		static D3DXINLINE const Matrix3x3 Identity();
		static D3DXINLINE const Matrix3x3 RotationX(float radians);
		static D3DXINLINE const Matrix3x3 RotationY(float radians);
		static D3DXINLINE const Matrix3x3 RotationZ(float radians);
		static D3DXINLINE const Matrix3x3 RotationZYX(const Vector3 &radiansXYZ);
		static D3DXINLINE const Matrix3x3 Rotation(float radians, const Vector3 &unitVec);
		static D3DXINLINE const Matrix3x3 Rotation(const Quaternion &unitQuat);
		static D3DXINLINE const Matrix3x3 Scale(const Vector3 &scaleVec);

		//Operator
		D3DXINLINE Matrix3x3 &operator =(const Matrix3x3 &mat);
		D3DXINLINE Vector3 &operator [](int col);
		D3DXINLINE const Vector3 operator [](int col) const;
		D3DXINLINE const Matrix3x3 operator +(const Matrix3x3 &mat) const;
		D3DXINLINE const Matrix3x3 operator -(const Matrix3x3 &mat) const;
		D3DXINLINE const Matrix3x3 operator -() const;
		D3DXINLINE const Matrix3x3 operator *(float scalar) const;
		D3DXINLINE const Vector3 operator *(const Vector3 &vec) const;
		D3DXINLINE const Matrix3x3 operator *(const Matrix3x3 &mat) const;
		D3DXINLINE Matrix3x3 &operator +=(const Matrix3x3 &mat);
		D3DXINLINE Matrix3x3 &operator -=(const Matrix3x3 &mat);
		D3DXINLINE Matrix3x3 &operator *=(float scalar);
		D3DXINLINE Matrix3x3 &operator *=(const Matrix3x3 &mat);

		//Accessor

		D3DXINLINE Matrix3x3 &col(int col, const Vector3 &vec);
		D3DXINLINE const Vector3 col(int col) const;
		D3DXINLINE Matrix3x3 &row(int row, const Vector3 &vec);
		D3DXINLINE const Vector3 row(int row) const;
		D3DXINLINE Matrix3x3 &element(int col, int row, float val);
		D3DXINLINE float element(int col, int row) const;



	};
	//Functions
	D3DXINLINE const Matrix3x3 operator *(float scalar, const Matrix3x3 &mat);
	D3DXINLINE const Matrix3x3 MulPerElem(const Matrix3x3 &mat0, const Matrix3x3 &mat1);
	D3DXINLINE const Matrix3x3 AbsPerElem(const Matrix3x3 &mat);
	D3DXINLINE const Matrix3x3 Transpose(const Matrix3x3 &mat);
	D3DXINLINE const Matrix3x3 Inverse(const Matrix3x3 &mat);


	//*****************************************************************************
	//*****************************************************************************
	// Matrix4x3クラスの宣言
	//*****************************************************************************
	//*****************************************************************************
	class Matrix4x3
	{
	private:

	public:
		// Public Variables

		Vector3 col0;
		Vector3 col1;
		Vector3 col2;
		Vector3 col3;

		//Constructers
		D3DXINLINE Matrix4x3() {};
		D3DXINLINE Matrix4x3(const Matrix4x3 &tran);
		D3DXINLINE Matrix4x3(const Vector3 &_col0, const Vector3 &_col1, const Vector3 &_col2, const Vector3 &_col3);
		D3DXINLINE Matrix4x3(const Matrix3x3 &tran, const Vector3 &translateVec);
		D3DXINLINE Matrix4x3(const Quaternion &unitQuat, const Vector3 &translateVec);
		D3DXINLINE Matrix4x3(float scalar);

		//Static construct
		static D3DXINLINE const Matrix4x3 Identity();
		static D3DXINLINE const Matrix4x3 RotationX(float radians);
		static D3DXINLINE const Matrix4x3 RotationY(float radians);
		static D3DXINLINE const Matrix4x3 RotationZ(float radians);
		static D3DXINLINE const Matrix4x3 RotationZYX(const Vector3 &radiansXYZ);
		static D3DXINLINE const Matrix4x3 Rotation(float radians, const Vector3 &unitVec);
		static D3DXINLINE const Matrix4x3 Rotation(const Quaternion &unitQuat);
		static D3DXINLINE const Matrix4x3 Scale(const Vector3 &scaleVec);
		static D3DXINLINE const Matrix4x3 Translation(const Vector3 &translateVec);

		//Operator
		D3DXINLINE Matrix4x3 &operator =(const Matrix4x3 &tran);
		D3DXINLINE Vector3 &operator [](int col);
		D3DXINLINE const Vector3 operator [](int col) const;
		D3DXINLINE const Vector3 operator *(const Vector3 &vec) const;
		D3DXINLINE const Matrix4x3 operator *(const Matrix4x3 &tran) const;
		D3DXINLINE Matrix4x3 &operator *=(const Matrix4x3 &tran);

		//Accessor

		D3DXINLINE Matrix4x3 &upper3x3(const Matrix3x3 &tran);
		D3DXINLINE const Matrix3x3 upper3x3(void) const;
		D3DXINLINE Matrix4x3 &translation(const Vector3 &translateVec);
		D3DXINLINE const Vector3 translation(void) const;
		D3DXINLINE Matrix4x3 &col(int col, const Vector3 &vec);
		D3DXINLINE const Vector3 col(int col) const;
		//D3DXINLINE Matrix4x3 &row(int col, const Vector4 &vec);
		//D3DXINLINE const Vector4 row(int col) const;
		D3DXINLINE Matrix4x3 &element(int col, int row, float val);
		D3DXINLINE float element(int col, int row) const;
	};
	//Functions
	D3DXINLINE const Matrix4x3 MulPerElem(const Matrix4x3 &tran0, const Matrix4x3 &tran1);
	D3DXINLINE const Matrix4x3 AbsPerElem(const Matrix4x3 &tran);
	D3DXINLINE const Matrix4x3 Inverse(const Matrix4x3 &tran);
	D3DXINLINE const Matrix4x3 OrthoInverse(const Matrix4x3 &tran);


}

//*****************************************************************************
// 各クラスのヘッダをinclude
//*****************************************************************************
#include "vector2.h"
#include "vector3.h"
#include "quaternion.h"
#include "matrix3x3.h"
#include "matrix4x3.h"

#endif
