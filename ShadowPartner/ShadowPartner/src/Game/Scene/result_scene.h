//==========================================================
// �T�v  :���U���g�V�[��
// Author:Ittoto
// Copyright(c) Utsurugi.All right reserved.
//==========================================================


#ifndef _GAME_SCENE_RESULTSCENE_H_
#define _GAME_SCENE_RESULTSCENE_H_

//**********************************************************
// �C���N���[�h�t�@�C��
//**********************************************************
#include "../../Base/System/scene.h"

namespace shadowpartner
{
	//==========================================================
	// �T�v  :���U���g�V�[��
	//==========================================================
	class ResultScene :public Scene
	{
	public:
		ResultScene();
		virtual ~ResultScene();

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
		GameObject *result_background_;
		GameObject *stage_clear_;


		//GameObject 

		// methods



		// ���p�֎~
	};
}

#endif