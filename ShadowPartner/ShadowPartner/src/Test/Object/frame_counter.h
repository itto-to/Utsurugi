//==========================================================
// �T�v  :�o�߃t���[���\���p
// Author:Itsuki Namito
// Copyright(c) Utsurugi.All right reserved.
//==========================================================

#ifndef _TEST_OBJECT_FRAME_COUNTER_H_
#define _TEST_OBJECT_FRAME_COUNTER_H_

//**********************************************************
// �C���N���[�h�t�@�C��
//**********************************************************
#include "../../Base/Element/component.h"
#include "../../Base/2D/sprite.h"

#include "draw_number.h"

//**********************************************************
// �}�N��
//**********************************************************
#define FRAME_COUNT_DIGIT_MAX (7)	// �t���[�������v������ő包��

namespace shadowpartner
{

	//==========================================================
	// �T�v  :�o�߃t���[���\���p
	//==========================================================
	class FrameCounter :public Component
	{
	public:
		FrameCounter();
		virtual ~FrameCounter();

		// variables

		// methods

	protected:

		// methods
		void Uninit();
		void Start();
		void Update();

	private:
		// variables
		int frame_count_;
		DrawNumber *frame_digits_[FRAME_COUNT_DIGIT_MAX];

		// methods

		// ���p�֎~
	};
}

#endif