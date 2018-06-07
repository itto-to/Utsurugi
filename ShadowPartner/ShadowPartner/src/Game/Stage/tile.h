#ifndef _GAME_STAGE_TILE_H_
#define _GAME_STAGE_TILE_H_

//**********************************************************
// インクルードファイル
//**********************************************************
#include "../../Base/2D/sprite.h"
#include "../../Base/2D/texture.h"


//==========================================================
// マクロ
//==========================================================
#define TEST_VERTICAL (4)
#define TEST_HORIZONTAL (3)
namespace shadowpartner
{
	//==========================================================
	// タイルマップクラス
	//==========================================================

	class Tile
	{
	public:

		//Sprite *sprite;

		Tile(const char *file_name, char no);
		Tile(const char *file_name, char no, Layer layer, bool pass) ;
		Tile(const Tile &copy);
		~Tile();

		//variables
		Layer tilelayer_;
		bool is_pass_;
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