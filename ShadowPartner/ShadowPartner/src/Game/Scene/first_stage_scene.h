//==========================================================
// �T�v  :�ŏ��̃X�e�[�W�N���X
// Author:Itsuki Namito
// Copyright(c) Utsurugi.All right reserved.
//==========================================================

#ifndef _GAME_SCENE_FIRST_STAGE_SCENE_H_
#define _GAME_SCENE_FIRST_STAHE_SCENE_H_

//**********************************************************
// �C���N���[�h�t�@�C��
//**********************************************************
#include "stage_scene.h"

namespace shadowpartner
{
	//==========================================================
	// �T�v  :�X�e�[�W�V�[���̊��N���X
	//==========================================================
	class FirstStageScene:public StageScene
	{
	public:
		FirstStageScene(int phase_num);
		virtual ~FirstStageScene();
		
		// variables

		// methods

	protected:

		// methods
		HRESULT Init();
		void Update();
		void Uninit();

	private:
		// variables

		// methods



		// ���p�֎~
	};
}

#endif