//==========================================================
// 概要  :2Dオブジェクトの描画用クラス
// Author:Itsuki Namito
// Copyright(c) Utsurugi.All right reserved.
//==========================================================
#include "sprite.h"

namespace shadowpartner
{
//**********************************************************
// マクロ
//**********************************************************

	//**********************************************************
	// 定数
	//**********************************************************

	// コンストラクタ
	Sprite::Sprite(const char *file_name)
	{
		texture_ = Texture(file_name);
	}

	// コピーコンストラクタ
	Sprite::Sprite(const Sprite &copy)
	{
		*this = copy;
	}

	// デストラクタ
	Sprite::~Sprite()
	{

	}

	//==========================================================
	// 概要  :スプライトの色を変更します。
	// 引数  :変更したい色。
	//==========================================================
	void Sprite::SetColor(D3DCOLOR &color)
	{
		for (int i = 0; i < NUM_TEXTURE_VERTEX;++i)
		{
			vertices_[i].diffuse_ = color;
		}
	}

	//==========================================================
	// 概要  :Transformのscaleを基準とした大きさを指定します。
	// 引数  :伸縮の割合
	//==========================================================
	void Sprite::SetSize(Vector2 &size)
	{
		size_ = size;
	}

	//==========================================================
	// 概要  :頂点を作成します。
	//==========================================================
	void Sprite::MakeVertex()
	{
		vertices_[0].rhw_ =
			vertices_[1].rhw_ =
			vertices_[2].rhw_ =
			vertices_[3].rhw_ = 1.0f;

		vertices_[0].diffuse_ =
			vertices_[1].diffuse_ =
			vertices_[2].diffuse_ =
			vertices_[3].diffuse_ = D3DCOLOR_RGBA(255, 255, 255, 255);

		vertices_[0].tex_coor_ = Vector2::zero();
		vertices_[1].tex_coor_ = Vector2(1.0f,0.0f);
		vertices_[2].tex_coor_ = Vector2(0.0f,1.0f);
		vertices_[3].tex_coor_ = Vector2::one();
	}

	//==========================================================
	// 概要  :頂点の設定を行います。
	// 引数  :
	//	center  :Spriteの中心
	//	width   :横幅
	//	height  :縦幅
	//	rotition:回転
	//==========================================================
	void Sprite::SetVertex(const Vector2 &center, const float &width,
		const float &height, const float &rotation)
	{
		float hw = width / 2.0f, hh = height / 2.0f;

		float rad = D3DXToRadian(rotation);

		float xsin = hw * sinf(rad), xcos = hw * cosf(rad);
		float ysin = hh * sinf(rad), ycos = hh * cosf(rad);

		vertices_[0].vertex_ = center + Vector2(-xcos + ysin, -xsin - ycos);
		vertices_[1].vertex_ = center + Vector2(xcos + ysin, xsin - ycos);
		vertices_[2].vertex_ = center + Vector2(-xcos - ysin, -xsin + ycos);
		vertices_[3].vertex_ = center + Vector2(xcos - ysin, xsin + ycos);
	}

}
