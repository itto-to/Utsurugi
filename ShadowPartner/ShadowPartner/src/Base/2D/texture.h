//==========================================================
// 概要  :テクスチャクラス
// Author:Itsuki Namito
// Copyright(c) Utsurugi.All right reserved.
//==========================================================

#ifndef _BASE_2D_TEXTURE_H_
#define _BASE_2D_TEXTURE_H_

//**********************************************************
// インクルードファイル
//**********************************************************
#include <d3dx9.h>
#include "../Math/math.h"

using namespace math;

//==========================================================
// マクロ
//==========================================================
#define FVF_VERTEX_2D (D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)
#define NUM_TEXTURE_VERTEX (4)
#define NUM_TEXTURE_POLYGON (2)

namespace shadowpartner
{
	struct Vertex2D
	{
		Vector2 vertex_;
		float rhw_;
		D3DCOLOR diffuse_;
		Vector2 tex_coor_;
	};

	//==========================================================
	// 画像を保持するクラス（あとで参照するクラスにする）
	//==========================================================
	class Texture
	{
	public:
		Texture();
		Texture(const char *file_name);
		~Texture();

		//variables

		//methods
		void Load(const char *file_name);

	private:
		// variables
		LPDIRECT3DTEXTURE9 tex_;
	};
}

#endif