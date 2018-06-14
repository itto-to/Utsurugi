//==========================================================
// �T�v  :�^�C�g���V�[��
// Author:Itsuki Namito
// Copyright(c) Utsurugi.All right reserved.
//==========================================================

#ifndef _GAME_SCENE_TITLE_SCENE_H_
#define _GAME_SCENE_TITLE_SCENE_H_

//**********************************************************
// �C���N���[�h�t�@�C��
//**********************************************************
#include "../../Base/System/scene.h"

namespace shadowpartner
{
	//==========================================================
	// �T�v  :�^�C�g���V�[��
	//==========================================================
	class TitleScene:public Scene
	{
	public:
		TitleScene();
		virtual ~TitleScene();
		
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
		GameObject *title_background_;

		enum TitleButton
		{
			kNewGame,
			//kContinue,
			//kConfig,
			kExit,
			kTitleButtonCount
		};

		int current_button_index_;
		GameObject *title_command_buttons_[TitleButton::kTitleButtonCount];

		//GameObject 

		// methods



		// ���p�֎~
	};
}

#endif