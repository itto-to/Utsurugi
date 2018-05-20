//==========================================================
// �T�v  :FPS�̕\���p�I�u�W�F�N�g
// Author:Itsuki Namito
// Copyright(c) Utsurugi.All right reserved.
//==========================================================

#ifndef _TEST_OBJECT_FPS_OBJECT_H_
#define _TEST_OBJECT_FPS_OBJECT_H_

//**********************************************************
// �C���N���[�h�t�@�C��
//**********************************************************
#include "../../Base/Element/component.h"
#include "../../Base/2D/sprite.h"

#include "draw_number.h"

//**********************************************************
// �}�N��
//**********************************************************
#define FPS_DIGIT_NUM (3)

namespace shadowpartner
{

	//==========================================================
	// �T�v  :�`��̃e�X�g�p�I�u�W�F�N�g
	//==========================================================
	class FpsObject:public Component
	{
	public:
		FpsObject();
		virtual ~FpsObject();
		
		// variables

		// methods

	protected:

		// methods
		void Uninit();
		void Start();
		void Update();

	private:
		// variables
		int fps_;
		DrawNumber *fps_digits_[FPS_DIGIT_NUM];

		// methods

		// ���p�֎~
	};
}

#endif