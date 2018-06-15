//==========================================================
// �T�v  :�^�C�g���V�[��
// Author:Itsuki Namito
// Copyright(c) Utsurugi.All right reserved.
//==========================================================

#ifndef _GAME_SCENE_TEMP_ENDING_SCENE_H_
#define _GAME_SCENE_TEMP_ENDING_SCENE_H_

//**********************************************************
// �C���N���[�h�t�@�C��
//**********************************************************
#include "../../Base/System/scene.h"

namespace shadowpartner
{
	//==========================================================
	// �T�v  :�^�C�g���V�[��
	//==========================================================
	class TempEndingScene:public Scene
	{
	public:
		TempEndingScene();
		virtual ~TempEndingScene();
		
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
		GameObject *ending_image_;

		//GameObject 

		// methods



		// ���p�֎~
	};
}

#endif