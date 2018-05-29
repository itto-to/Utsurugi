#ifndef _GAME_STAGE_TILE_H_
#define _GAME_STAGE_TILE_H_

//**********************************************************
// インクルードファイル
//**********************************************************
#include "../../Base/2D/sprite.h"


//==========================================================
// マクロ
//==========================================================
#define TEXT_VERTICAL (20)
#define TEXT_HORIZONTAL (8)
namespace shadowpartner
{
	//==========================================================
	// タイルマップクラス
	//==========================================================

	class Tile
	{
	public:

		Sprite sprite;

		Tile(const char *file_name, char no);
		Tile(const char *file_name, char no, Layer layer, bool pass) ;
		Tile(const Tile &copy);
		~Tile();
		//variables
		Layer tilelayer_;
		bool is_pass_;

		//methods

	private:

		//variables
		char number_;		// 0-127 タイルマップコマ番号

	};

}

#endif