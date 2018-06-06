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

