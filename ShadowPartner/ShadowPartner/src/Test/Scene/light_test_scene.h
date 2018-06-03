//==========================================================
// �T�v  :���C�g�̃e�X�g�V�[��
// Author:Itsuki Namito
// Copyright(c) Utsurugi.All right reserved.
//==========================================================

#ifndef _TEST_SCENE_LIGHT_TEST_SCENE_H_
#define _TEST_SCENE_LIGHT_TEST_SCENE_H_

//**********************************************************
// �C���N���[�h�t�@�C��
//**********************************************************
#include "../../Base/System/scene.h"

namespace shadowpartner
{
	//==========================================================
	// �T�v  :�`��̃e�X�g�p�V�[��
	//==========================================================
	class LightTestScene:public Scene
	{
	public:
		LightTestScene();
		virtual ~LightTestScene();
		
		// variables

		// methods

	protected:

		// methods
		HRESULT Init();
		void Update();
		void Uninit();

	private:
		// variables
		GameObject *camera_object_;
		GameObject *light_object_;
		GameObject *player_;
		GameObject *ceiling_;
		GameObject *left_wall_;
		GameObject *right_wall_;
		GameObject *floor_;

		GameObject *block1_;
		GameObject *circles_[11];

		GameObject *pyramids_[15];

		// methods



		// ���p�֎~
	};
}

#endif