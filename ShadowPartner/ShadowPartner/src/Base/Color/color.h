//==========================================================
// 概要  :色関係
// Author:Itsuki Namito
// Copyright(c) Utsurugi.All right reserved.
//==========================================================

#ifndef _BASE_COLOR_COLOR_H_
#define _BASE_COLOR_COLOR_H_

namespace shadowpartner
{

	//**********************************************************
	// インクルードファイル
	//**********************************************************
#include <windows.h>
#include <d3dx9.h>

	//==========================================================
	// 概要  :色関係の処理を行うクラス
	//==========================================================
	class Color
	{
	public:


		// variables
		float r_, g_, b_, a_;

		Color() :r_(1.0f), g_(1.0f), b_(1.0f), a_(1.0f) {}
		Color(float s) :r_(Clamp(s)), g_(Clamp(s)), b_(Clamp(s)), a_(1.0f) {}
		Color(float r, float g, float b, float a)
			:r_(Clamp(r)), g_(Clamp(g)), b_(Clamp(b)), a_(Clamp(a)) {};
		~Color() {}

		// methods
		static Color red() { return Color(1.0f, 0.0f, 0.0f, 1.0f); }
		static Color blue() { return Color(0.0f, 1.0f, 0.0f, 1.0f); }
		static Color green() { return Color(0.0f, 0.0f, 1.0f, 1.0f); }

		static Color cyan() { return Color(0.0f, 1.0f, 1.0f, 1.0f); }
		static Color magenta() { return Color(1.0f, 0.0f, 1.0f, 1.0f); }
		static Color yellow() { return Color(1.0f, 1.0f, 0.0f, 1.0f); }

		static Color clear() { return Color(0.0f, 0.0f, 0.0f, 0.0f); }
		static Color black() { return Color(0.0f, 0.0f, 0.0f, 1.0f); }
		static Color white() { return Color(1.0f, 1.0f, 1.0f, 1.0f); }

		// Operator
		D3DXINLINE operator DWORD()
		{
			return D3DCOLOR_RGBA((int)(0xff * r_), (int)(0xff * g_), (int)(0xff * b_), (int)(0xff * a_));
		}

		D3DXINLINE Color &operator =(const D3DCOLOR & d3d)
		{
			r_ = (d3d >> 16) & 0xff;
			g_ = (d3d >> 8) & 0xff;
			b_ = d3d & 0xff;
			a_ = (d3d >> 24) & 0xff;
			return *this;
		}

		D3DXINLINE const Color operator +(const Color &col) const
		{
			return Color
				(
					Clamp(r_ + col.r_),
					Clamp(g_ + col.g_),
					Clamp(b_ + col.b_),
					Clamp(a_ + col.a_)
					);
		}

		D3DXINLINE const Color operator -(const Color &col) const
		{
			return Color
				(
					Clamp(r_ - col.r_),
					Clamp(g_ - col.g_),
					Clamp(b_ - col.b_),
					Clamp(a_ - col.a_)
					);
		}

		D3DXINLINE const Color operator *(const Color &col) const
		{
			return Color
				(
					Clamp(r_ * col.r_),
					Clamp(g_ * col.g_),
					Clamp(b_ * col.b_),
					Clamp(a_ * col.a_)
					);
		}


	protected:

		// methods

	private:
		// variables


		// methods
		D3DXINLINE const float Clamp(float v) const
		{
			return (v < 0.0f) ? 0.0f :
				(v > 1.0f) ? 1.0f : v;
		}
	};

	//==========================================================
	// 概要  :実数tでaとbの間の色を線形補完します。
	// 引数  :
	//  t:aとbを組み合わせる割合(0.0f ～ 1.0fでクランプされます。)
	//  a:片方の色
	//  b:もう片方の色
	//==========================================================
	D3DXINLINE const Color Lerp(float t, const Color &a, const Color &b)
	{
		t = (t < 0.0f) ? 0.0f : (t > 1.0f) ? 1.0f : t;

		return Color
			(
				(b.r_ * t + (1.0f - t) * a.r_),
				(b.g_ * t + (1.0f - t) * a.g_),
				(b.b_ * t + (1.0f - t) * a.b_),
				(b.a_ * t + (1.0f - t) * a.a_)
				);
	}
}
#endif