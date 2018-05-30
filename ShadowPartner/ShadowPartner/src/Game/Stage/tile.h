#ifndef _GAME_STAGE_TILE_H_
#define _GAME_STAGE_TILE_H_

//**********************************************************
// �C���N���[�h�t�@�C��
//**********************************************************
#include "../../Base/2D/sprite.h"


//==========================================================
// �}�N��
//==========================================================
#define TEST_VERTICAL (4)
#define TEST_HORIZONTAL (3)
namespace shadowpartner
{
	//==========================================================
	// �^�C���}�b�v�N���X
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
		char number_;		// 0-127 �^�C���}�b�v�R�}�ԍ�

	};

}

#endif