//==========================================================
// 概要  :2Dオブジェクトの描画用クラス
// Author:Itsuki Namito
// Copyright(c) Utsurugi.All right reserved.
//==========================================================

#ifndef _BASE_2D_SPRITE_H_
#define _BASE_2D_SPRITE_H_

//**********************************************************
// インクルードファイル
//**********************************************************
#include "texture.h"
#include "../Element/component.h"

//==========================================================
// マクロ
//==========================================================

namespace shadowpartner
{
	//==========================================================
	// 2Dオブジェクトの描画用クラス
	//==========================================================
	class Sprite:public Component
	{
	public:

		enum Anchor
		{
			kUpperRight,
			kUpperCenter,
			kUpperLeft,
			kMiddleRight,
			kMiddleCenter,
			kMiddleLeft,
			kLowerRight,
			kLowerCenter,
			kLowerLeft,
			kAnchorCount
		};

		enum TrapezoidAxis
		{
			kXaxis,
			kYaxis,

		};

		Sprite(const char *file_name);
		Sprite(const Sprite &copy);
		~Sprite();

		//variables

		//methods
		Vector2 Size();
		void SetAnchor(const Anchor &anchor);
		Anchor GetAnchor();
		void SetOffset(const Vector2 &offset);
		Vector2 GetOffset();

		void SetColor(const D3DCOLOR &color);
		void SetSize(const Vector2 &size);
		void SetUvOffset(const Vector2 &offset);
		void SetUvSize(const Vector2 &size);
		void SetOrderInLayer(const int &layer);
		Vector2 UvOffset() const;

		void SetUvNormal();
		void SetUvInvertX();
		void SetUvInvertY();
		void SetUvInvertXY();
		void SetFlipX(bool enable_flip_x);
		void SetFlipY(bool enable_flip_y);
		bool GetFlipX() const;
		bool GetFlipY() const;

		void SetAsTrapezoid(float height, float upper_base, float lower_base, TrapezoidAxis trapezoid_axis = TrapezoidAxis::kYaxis);
		void CustomShape( const Vector2 &p0, const Vector2 &p1, const Vector2 &p2, const Vector2 &p3);
		void EnableSquare();

	protected:
		void Draw();

	private:
		// variables
		Texture *texture_;
		Anchor anchor_;			// transform.positionは画像のどの位置を表しているか
		Vector2 offset_;		// transform.positionからどれだけずらす
		Vector2 uv_offset_;		// テクスチャーのuv座標の左上
		Vector2 uv_size_;		// テクスチャーのuv座標の左上から右下までのベクトル
		Vertex2D vertices_[NUM_TEXTURE_VERTEX];
		Vector2 custom_vertices_[NUM_TEXTURE_VERTEX];
		float custom_rhw_[NUM_TEXTURE_VERTEX];
		int order_in_layer_;
		bool flip_x_;
		bool flip_y_;

		bool is_square_;	// 正方形

		// methods
		void MakeVertex();
		void SetVertex(const Vector3 &center, const float &width,
			const float &height, const float &rotation);
	};
}

#endif