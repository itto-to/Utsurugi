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

		enum Anchor
		{
			kUpperRight,
			kUpperCenter,
			kUpperLeft,
			kMiddleRight,
			kMiddleCenter,
			kMiddleLeft,
			kLowerRight,
			kLowerCenter,
			kLowerLeft,
			kAnchorCount
		};

		enum TrapezoidAxis
		{
			kXaxis,
			kYaxis,

		};

		Sprite(const char *file_name);
		Sprite(const Sprite &copy);
		~Sprite();

		//variables

		//methods
		Vector2 Size();
		void SetAnchor(const Anchor &anchor);
		Anchor GetAnchor();
		void SetOffset(const Vector2 &offset);
		Vector2 GetOffset();

		void SetColor(const D3DCOLOR &color);
		void SetSize(const Vector2 &size);
		void SetUvOffset(const Vector2 &offset);
		void SetUvSize(const Vector2 &size);
		void SetOrderInLayer(const int &layer);
		Vector2 UvOffset() const;

		void SetUvNormal();
		void SetUvInvertX();
		void SetUvInvertY();
		void SetUvInvertXY();
		void SetFlipX(bool enable_flip_x);
		void SetFlipY(bool enable_flip_y);
		bool GetFlipX() const;
		bool GetFlipY() const;

		void SetAsTrapezoid(float height, float upper_base, float lower_base, TrapezoidAxis trapezoid_axis = TrapezoidAxis::kYaxis);
		void CustomShape( const Vector2 &p0, const Vector2 &p1, const Vector2 &p2, const Vector2 &p3);
		void EnableSquare();

	protected:
		void Draw();

	private:
		// variables
		Texture *texture_;
		Anchor anchor_;			// transform.position�͉摜�̂ǂ̈ʒu��\���Ă��邩
		Vector2 offset_;		// transform.position����ǂꂾ�����炷
		Vector2 uv_offset_;		// �e�N�X�`���[��uv���W�̍���
		Vector2 uv_size_;		// �e�N�X�`���[��uv���W�̍��ォ��E���܂ł̃x�N�g��
		Vertex2D vertices_[NUM_TEXTURE_VERTEX];
		Vector2 custom_vertices_[NUM_TEXTURE_VERTEX];
		float custom_rhw_[NUM_TEXTURE_VERTEX];
		int order_in_layer_;
		bool flip_x_;
		bool flip_y_;

		bool is_square_;	// �����`

		// methods
		void MakeVertex();
		void SetVertex(const Vector3 &center, const float &width,
			const float &height, const float &rotation);
	};
}

#endif