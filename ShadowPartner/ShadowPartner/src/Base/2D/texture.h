//==========================================================
// �T�v  :�e�N�X�`���N���X
// Author:Itsuki Namito
// Copyright(c) Utsurugi.All right reserved.
//==========================================================

#ifndef _BASE_2D_TEXTURE_H_
#define _BASE_2D_TEXTURE_H_

//**********************************************************
// �C���N���[�h�t�@�C��
//**********************************************************
#include <d3dx9.h>
#include "../Math/math.h"

using namespace math;

//==========================================================
// �}�N��
//==========================================================
#define FVF_VERTEX_2D (D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)
#define NUM_TEXTURE_VERTEX (4)
#define NUM_TEXTURE_POLYGON (2)
#define PIXEL_PER_UNIT (100)

namespace shadowpartner
{
	struct Vertex2D
	{
		Vector3 vertex_;
		float rhw_;
		D3DCOLOR diffuse_;
		Vector2 tex_coor_;
	};

	//==========================================================
	// �摜��ێ�����N���X�i���ƂŎQ�Ƃ���N���X�ɂ���j
	//==========================================================
	class Texture
	{
	public:
		Texture();
		Texture(const char *file_name);
		~Texture();

		//variables

		//methods
		void Load(const char *file_name);

		void DrawTriangleStrip(const Vertex2D *vertices);
		void DrawTriangleFan(const Vertex2D *vertices,UINT primitive_count);

		void SetSize(float width, float height);
		void SetWidth(float width);
		float GetWidth();
		void SetHeight(float height);
		float GetHeight();

	private:
		// variables
		LPDIRECT3DTEXTURE9 tex_;
		float width_;	// ���̃e�N�X�`���[�̉���
		float height_;
	};
}

#endif