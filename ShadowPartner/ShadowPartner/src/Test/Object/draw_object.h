//==========================================================
// �T�v  :�`��̃e�X�g�p�I�u�W�F�N�g
// Author:Itsuki Namito
// Copyright(c) Utsurugi.All right reserved.
//==========================================================

#ifndef _TEST_OBJECT_DRAW_OBJECT_H_
#define _TEST_OBJECT_DRAW_OBJECT_H_

//**********************************************************
// �C���N���[�h�t�@�C��
//**********************************************************
#include "../../Base/Element/component.h"
#include "../../Base/2D/sprite.h"

namespace shadowpartner
{

	//==========================================================
	// �T�v  :�`��̃e�X�g�p�I�u�W�F�N�g
	//==========================================================
	class DrawObject:public Component
	{
	public:
		DrawObject();
		virtual ~DrawObject();
		
		// variables

		// methods

	protected:

		// methods
		void Uninit();
		void Awake();
		void Update();
		void Draw();

	private:
		// variables

		// methods

		// ���p�֎~
	};
}

#endif