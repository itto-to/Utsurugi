//==========================================================
// �T�v  :�e�N�X�`���N���X
// Author:Itsuki Namito
// Copyright(c) Utsurugi.All right reserved.
//==========================================================
#include "tile.h"

namespace shadowpartner
{
	//**********************************************************
	// �}�N��
	//**********************************************************

	//**********************************************************
	// �萔
	//**********************************************************

	// �R���X�g���N�^
	Tile::Tile(const char *file_name,char no, 
		unsigned devide_horizontal, unsigned devide_vertical,
		unsigned cell_horizontal, unsigned cell_vertical,
		GameObject &game_object
	)
	{
		// tile�u���Ȃ��ꍇ
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

		////pos��stage�̃C���X�g���N�^�[�̒��Őݒ�

	}


	Tile::~Tile()
	{
		if (texture_ != nullptr)
		{
			delete texture_;
		}
	}

	//==========================================================
	// �T�v  :�e�N�X�`���[��uv���W�̍����ݒ肵�܂��B
	// ����  :����̍��W
	//==========================================================
	void Tile::SetUvOffset(const Vector2 &offset)
	{
		uv_offset_ = offset;
	}

	//==========================================================
	// �T�v  :uv�̑傫����ݒ肵�܂��B
	// ����  :�e�N�X�`���[��uv���W�̍��ォ��E���܂ł̃x�N�g��
	//==========================================================
	void Tile::SetUvSize(const Vector2 &size)
	{
		uv_size_ = size;
	}


}

