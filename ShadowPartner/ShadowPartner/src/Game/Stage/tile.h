#ifndef _GAME_STAGE_TILE_H_
#define _GAME_STAGE_TILE_H_

//**********************************************************
// �C���N���[�h�t�@�C��
//**********************************************************
#include "../Application/application.h"
#include "../../Base/2D/sprite.h"
#include "../../Base/2D/texture.h"

namespace shadowpartner
{
	//==========================================================
	// �^�C���}�b�v�N���X
	//==========================================================

	class Tile
	{
	public:

		//Sprite *sprite;

		Tile(const char *file_name, char no, 
			unsigned devide_horizontal, unsigned devide_vertical,
			unsigned cell_horizontal, unsigned cell_vertical,GameObject &game_object);
		~Tile();

		//variables
		Texture *texture_;
		Vertex2D vertices_[NUM_TEXTURE_VERTEX];
		Vector2 uv_offset_;		// �e�N�X�`���[��uv���W�̍���
		Vector2 uv_size_;		// �e�N�X�`���[��uv���W�̍��ォ��E���܂ł̃x�N�g��

		//methods
		void SetUvOffset(const Vector2 &offset);
		void SetUvSize(const Vector2 &size);

	private:
		//variables
		char number_;		// 0-127 �^�C���}�b�v�R�}�ԍ�

	};

}

#endif