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
		void SetColor(D3DCOLOR &color);
		void SetSize(Vector2 &size);

	protected:
		void Draw();

	private:
		// variables
		Texture texture_;
		Vector2 size_;
		Vector2 uv_offset_;
		Vector2 uv_size_;
		Vertex2D vertices_[NUM_TEXTURE_VERTEX];

		// methods
		void MakeVertex();
		void SetVertex(const Vector2 &center, const float &width,
			const float &height, const float &rotation);
	};
}

#endif