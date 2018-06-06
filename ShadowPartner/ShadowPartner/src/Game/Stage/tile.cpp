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
	Tile::Tile(const char *file_name, char no) 
	{
		texture_ = new Texture(file_name);

		number_ = no-1;
		tilelayer_ = kDefault;
		is_pass_ = FALSE;
		char x = number_ % TEST_HORIZONTAL;
		char y = number_ / TEST_HORIZONTAL;
		float sizex_ = 1.0f / TEST_HORIZONTAL;
		float sizey_ = 1.0f / TEST_VERTICAL;

		vertices_[0].rhw_ =
		vertices_[1].rhw_ =
		vertices_[2].rhw_ =
		vertices_[3].rhw_ = 1.0f;


		vertices_[0].diffuse_ =
		vertices_[1].diffuse_ =
		vertices_[2].diffuse_ =
		vertices_[3].diffuse_ = D3DCOLOR_RGBA(255, 255, 255, 255);


		vertices_[0].tex_coor_ = Vector2::zero();
		vertices_[1].tex_coor_ = Vector2(1.0f, 0.0f);
		vertices_[2].tex_coor_ = Vector2(0.0f, 1.0f);
		vertices_[3].tex_coor_ = Vector2::one();

		vertices_[0].vertex_ = Vector3::zero();
		vertices_[1].vertex_ = Vector3::zero();
		vertices_[2].vertex_ = Vector3::zero();
		vertices_[3].vertex_ = Vector3::zero();


		SetUvOffset(Vector2(x* sizex_, y* sizey_));
		SetUvSize(Vector2(sizex_, sizey_));

	}

	Tile::Tile(const char *file_name, char no, Layer layer, bool pass) 
	{
		texture_ = new Texture(file_name);

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

