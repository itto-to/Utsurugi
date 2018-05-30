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
	Tile::Tile(const char *file_name, char no) :sprite(file_name)
	{
		number_ = no;
		tilelayer_ = kDefault;
		is_pass_ = FALSE;
		float sizex_ = 1.0f / TEST_HORIZONTAL;
		float sizey_ = 1.0f / TEST_VERTICAL;
		sprite.SetUvOffset(Vector2((no - 1) % TEST_HORIZONTAL*sizex_, (no - 1) / TEST_HORIZONTAL*sizey_));
		sprite.SetUvSize(Vector2(no% TEST_HORIZONTAL*sizex_, no / TEST_HORIZONTAL*sizey_));

	}

	Tile::Tile(const char *file_name, char no, Layer layer, bool pass) :sprite(file_name)
	{
		number_ = no;
		tilelayer_ = layer;
		is_pass_ = pass;
		float sizex_ = 1.0f / TEST_HORIZONTAL;
		float sizey_ = 1.0f / TEST_VERTICAL;
		sprite.SetUvOffset(Vector2((no - 1) % TEST_HORIZONTAL*sizex_, (no - 1) / TEST_HORIZONTAL*sizey_));
		sprite.SetUvSize(Vector2(no% TEST_HORIZONTAL*sizex_, no / TEST_HORIZONTAL*sizey_));

	}

	Tile::Tile(const Tile &copy) :sprite(copy.sprite)
	{
		*this = copy;
	}


	Tile::~Tile()
	{

	}

}