//==========================================================
// 概要  :テクスチャクラス
// Author:Itsuki Namito
// Copyright(c) Utsurugi.All right reserved.
//==========================================================
#include "tile.h"

namespace shadowpartner
{
	//**********************************************************
	// マクロ
	//**********************************************************

	//**********************************************************
	// 定数
	//**********************************************************

	// コンストラクタ
	Tile::Tile(const char *file_name, char no) :texture_(file_name)
	{
		number_ = no-1;
		tilelayer_ = kDefault;
		is_pass_ = FALSE;
		char x = number_ % TEST_HORIZONTAL;
		char y = number_ / TEST_HORIZONTAL;
		float sizex_ = 1.0f / TEST_HORIZONTAL;
		float sizey_ = 1.0f / TEST_VERTICAL;
		SetUvOffset(Vector2(x* sizex_, y* sizey_));
		SetUvSize(Vector2(sizex_, sizey_));

	}

	Tile::Tile(const char *file_name, char no, Layer layer, bool pass) :texture_(file_name)
	{
		number_ = no-1;
		tilelayer_ = layer;
		is_pass_ = pass;
		char x = number_ % TEST_HORIZONTAL;
		char y = number_ / TEST_HORIZONTAL;
		float sizex_ = 1.0f / TEST_HORIZONTAL;
		float sizey_ = 1.0f / TEST_VERTICAL;
		//sprite->SetUvOffset(Vector2((float)(x)* sizex_, (float)(y)* sizey_));
		SetUvOffset(Vector2(x* sizex_, y* sizey_));
		SetUvSize(Vector2(sizex_, sizey_));

	}

	Tile::Tile(const Tile &copy) :texture_(copy.texture_)
	{
		*this = copy;
	}


	Tile::~Tile()
	{

	}

	//==========================================================
	// 概要  :テクスチャーのuv座標の左上を設定します。
	// 引数  :左上の座標
	//==========================================================
	void Tile::SetUvOffset(const Vector2 &offset)
	{
		uv_offset_ = offset;
	}

	//==========================================================
	// 概要  :uvの大きさを設定します。
	// 引数  :テクスチャーのuv座標の左上から右下までのベクトル
	//==========================================================
	void Tile::SetUvSize(const Vector2 &size)
	{
		uv_size_ = size;
	}


}

