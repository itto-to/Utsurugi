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
	Tile::Tile(const char *file_name, char no)
	{
		sprite = new Sprite(file_name);
		number_ = no-1;
		tilelayer_ = kDefault;
		is_pass_ = FALSE;
		char x = number_ % TEST_HORIZONTAL;
		char y = number_ / TEST_HORIZONTAL;
		float sizex_ = 1.0f / TEST_HORIZONTAL;
		float sizey_ = 1.0f / TEST_VERTICAL;
		sprite->SetUvOffset(Vector2((float)(x)* sizex_, (float)(y)* sizey_));
		sprite->SetUvSize(Vector2(sizex_,sizey_));

	}

	Tile::Tile(const char *file_name, char no, Layer layer, bool pass)
	{
		sprite = new Sprite(file_name);
		number_ = no-1;
		tilelayer_ = layer;
		is_pass_ = pass;
		char x = number_ % TEST_HORIZONTAL;
		char y = number_ / TEST_HORIZONTAL;
		float sizex_ = 1.0f / TEST_HORIZONTAL;
		float sizey_ = 1.0f / TEST_VERTICAL;
		sprite->SetUvOffset(Vector2((float)(x)* sizex_, (float)(y)* sizey_));
		sprite->SetUvSize(Vector2(sizex_, sizey_));

	}

	Tile::Tile(const Tile &copy) :sprite(copy.sprite)
	{
		*this = copy;
	}


	Tile::~Tile()
	{

	}

}