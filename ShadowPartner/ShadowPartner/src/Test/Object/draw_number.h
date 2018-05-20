//==========================================================
// �T�v  :�����̃e�N�X�`���[��\�����邾��
// Author:Itsuki Namito
// Copyright(c) Utsurugi.All right reserved.
//==========================================================

#ifndef _TEST_OBJECT_DRAW_NUMBER_H_
#define _TEST_OBJECT_DRAW_NUMBER_H_

//**********************************************************
// �C���N���[�h�t�@�C��
//**********************************************************
#include "../../Base/Element/component.h"
#include "../../Base/2D/sprite.h"

namespace shadowpartner
{

	//==========================================================
	// �T�v  :�����̃e�N�X�`���[��\�����邾��
	//==========================================================
	class DrawNumber:public Component
	{
	public:
		DrawNumber();
		virtual ~DrawNumber();
		
		// variables

		// methods
		void SetNumber(int number);	// ���̃I�u�W�F�N�g�͉����ڂ�`�悷��̂���ݒ肷��

	protected:

		// methods
		void Uninit();
		void Start();
		void Update();
		void Draw();

	private:
		// variables
		int number_;
		Sprite *number_sprite_;

		// methods

		// ���p�֎~
	};
}

#endif