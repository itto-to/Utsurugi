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
	Tile::Tile(const char *file_name,char no, 
		unsigned devide_horizontal, unsigned devide_vertical,
		unsigned cell_horizontal, unsigned cell_vertical,
		GameObject &game_object
	)
	{
		// tile置かない場合
		if (no ==127)
			texture_ = NULL;
		else
			texture_ = new Texture(file_name);

		number_ = no-1;
		unsigned x = number_ % devide_horizontal;
		unsigned y = number_ / devide_horizontal;
		float sizex_ = 1.0f / devide_horizontal;
		float sizey_ = 1.0f / devide_vertical;

		vertices_[0].rhw_ =
		vertices_[1].rhw_ =
		vertices_[2].rhw_ =
		vertices_[3].rhw_ = 1.0f;


		vertices_[0].diffuse_ =
		vertices_[1].diffuse_ =
		vertices_[2].diffuse_ =
		vertices_[3].diffuse_ = D3DCOLOR_RGBA(255, 255, 255, 255);



		SetUvOffset(Vector2(x* sizex_, y* sizey_));
		SetUvSize(Vector2(sizex_, sizey_));

		//BoxInitializer box_init;
		//box_init.width_ = DEFAULT_SCREEN_WIDTH / cell_horizontal;
		//box_init.height_ = DEFAULT_SCREEN_HEIGHT / cell_vertical;
		////box_init.pos_= Vector2::zero();

		//box_collider_ = new BoxCollider(box_init);

		//game_object.AddComponent(box_collider_);

		////posはstageのインストラクターの中で設定

	}


	Tile::~Tile()
	{
		if (texture_ != nullptr)
		{
			delete texture_;
		}
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

