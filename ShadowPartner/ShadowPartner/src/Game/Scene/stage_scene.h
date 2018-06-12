//==========================================================
// �T�v  :�X�e�[�W�V�[���̊��N���X
// Author:Itsuki Namito
// Copyright(c) Utsurugi.All right reserved.
//==========================================================

#ifndef _GAME_SCENE_STAGE_SCENE_H_
#define _GAME_SCENE_STAHE_SCENE_H_

//**********************************************************
// �C���N���[�h�t�@�C��
//**********************************************************
#include "../../Base/System/scene.h"

#define STAGE_FASE_MAX (3)

namespace shadowpartner
{
	//==========================================================
	// �T�v  :�X�e�[�W�V�[���̊��N���X
	//==========================================================
	class StageScene:public Scene
	{
	public:
		StageScene();
		virtual ~StageScene();
		
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
		GameObject *stages_[STAGE_FASE_MAX];

		// methods



		// ���p�֎~
	};
}

#endif