//==========================================================
// �T�v  :2D�I�u�W�F�N�g�̕`��p�N���X
// Author:Itsuki Namito
// Copyright(c) Utsurugi.All right reserved.
//==========================================================

#ifndef _BASE_2D_SPRITE_H_
#define _BASE_2D_SPRITE_H_

//**********************************************************
// �C���N���[�h�t�@�C��
//**********************************************************
#include "texture.h"
#include "../Element/component.h"

//==========================================================
// �}�N��
//==========================================================

namespace shadowpartner
{
	//==========================================================
	// 2D�I�u�W�F�N�g�̕`��p�N���X
	//==========================================================
	class Sprite:public Component
	{
	public:
		Sprite(const char *file_name);
		Sprite(const Sprite &copy);
		~Sprite();

		//variables

		//methods
		void SetColor(const D3DCOLOR &color);
		void SetSize(const Vector2 &size);
		void SetUvOffset(const Vector2 &offset);
		void SetUvSize(const Vector2 &size);

	protected:
		void Draw();

	private:
		// variables
		Texture texture_;	
		Vector2 uv_offset_;		// �e�N�X�`���[��uv���W�̍���
		Vector2 uv_size_;		// �e�N�X�`���[��uv���W�̍��ォ��E���܂ł̃x�N�g��
		Vertex2D vertices_[NUM_TEXTURE_VERTEX];

		// methods
		void MakeVertex();
		void SetVertex(const Vector3 &center, const float &width,
			const float &height, const float &rotation);
	};
}

#endif