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
		Sprite(const char *file_name);
		Sprite(const Sprite &copy);
		~Sprite();

		//variables

		//methods
		Vector2 Size();
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

	protected:
		void Draw();

	private:
		// variables
		Texture *texture_;	
		Vector2 uv_offset_;		// テクスチャーのuv座標の左上
		Vector2 uv_size_;		// テクスチャーのuv座標の左上から右下までのベクトル
		Vertex2D vertices_[NUM_TEXTURE_VERTEX];
		int order_in_layer_;

		// methods
		void MakeVertex();
		void SetVertex(const Vector3 &center, const float &width,
			const float &height, const float &rotation);
	};
}

#endif