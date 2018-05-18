//==========================================================
// �T�v  :2D�I�u�W�F�N�g�̕`��p�N���X
// Author:Itsuki Namito
// Copyright(c) Utsurugi.All right reserved.
//==========================================================
#include "sprite.h"

namespace shadowpartner
{
//**********************************************************
// �}�N��
//**********************************************************

	//**********************************************************
	// �萔
	//**********************************************************

	// �R���X�g���N�^
	Sprite::Sprite(const char *file_name)
	{
		texture_ = Texture(file_name);
	}

	// �R�s�[�R���X�g���N�^
	Sprite::Sprite(const Sprite &copy)
	{
		*this = copy;
	}

	// �f�X�g���N�^
	Sprite::~Sprite()
	{

	}

	//==========================================================
	// �T�v  :�X�v���C�g�̐F��ύX���܂��B
	// ����  :�ύX�������F�B
	//==========================================================
	void Sprite::SetColor(D3DCOLOR &color)
	{
		for (int i = 0; i < NUM_TEXTURE_VERTEX;++i)
		{
			vertices_[i].diffuse_ = color;
		}
	}

	//==========================================================
	// �T�v  :Transform��scale����Ƃ����傫�����w�肵�܂��B
	// ����  :�L�k�̊���
	//==========================================================
	void Sprite::SetSize(Vector2 &size)
	{
		size_ = size;
	}

	//==========================================================
	// �T�v  :���_���쐬���܂��B
	//==========================================================
	void Sprite::MakeVertex()
	{
		vertices_[0].rhw_ =
			vertices_[1].rhw_ =
			vertices_[2].rhw_ =
			vertices_[3].rhw_ = 1.0f;

		vertices_[0].diffuse_ =
			vertices_[1].diffuse_ =
			vertices_[2].diffuse_ =
			vertices_[3].diffuse_ = D3DCOLOR_RGBA(255, 255, 255, 255);

		vertices_[0].tex_coor_ = Vector2::zero();
		vertices_[1].tex_coor_ = Vector2(1.0f,0.0f);
		vertices_[2].tex_coor_ = Vector2(0.0f,1.0f);
		vertices_[3].tex_coor_ = Vector2::one();
	}

	//==========================================================
	// �T�v  :���_�̐ݒ���s���܂��B
	// ����  :
	//	center  :Sprite�̒��S
	//	width   :����
	//	height  :�c��
	//	rotition:��]
	//==========================================================
	void Sprite::SetVertex(const Vector2 &center, const float &width,
		const float &height, const float &rotation)
	{
		float hw = width / 2.0f, hh = height / 2.0f;

		float rad = D3DXToRadian(rotation);

		float xsin = hw * sinf(rad), xcos = hw * cosf(rad);
		float ysin = hh * sinf(rad), ycos = hh * cosf(rad);

		vertices_[0].vertex_ = center + Vector2(-xcos + ysin, -xsin - ycos);
		vertices_[1].vertex_ = center + Vector2(xcos + ysin, xsin - ycos);
		vertices_[2].vertex_ = center + Vector2(-xcos - ysin, -xsin + ycos);
		vertices_[3].vertex_ = center + Vector2(xcos - ysin, xsin + ycos);
	}

}
