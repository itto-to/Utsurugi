#ifndef _GAME_STAGE_TILE_H_
#define _GAME_STAGE_TILE_H_

//**********************************************************
// インクルードファイル
//**********************************************************
#include "../Application/application.h"
#include "../../Base/2D/sprite.h"
#include "../../Base/2D/texture.h"
#include "../../Base/Physics/Element/circle_collider.h"
#include "../../Base/Physics/Physics.h"

using namespace physics;

namespace shadowpartner
{
	//==========================================================
	// タイルマップクラス
	//==========================================================

	class Tile
	{
	public:

		//Sprite *sprite;

		Tile(const char *file_name, char no, 
			unsigned devide_horizontal, unsigned devide_vertical,
			unsigned cell_horizontal, unsigned cell_vertical);
		~Tile();

		//variables
		//Layer tilelayer_;
		BoxCollider *box_collider;
		Texture *texture_;
		Vertex2D vertices_[NUM_TEXTURE_VERTEX];
		Vector2 uv_offset_;		// テクスチャーのuv座標の左上
		Vector2 uv_size_;		// テクスチャーのuv座標の左上から右下までのベクトル

		//methods
		void SetUvOffset(const Vector2 &offset);
		void SetUvSize(const Vector2 &size);

	private:
		//variables
		char number_;		// 0-127 タイルマップコマ番号

	};

}

#endif