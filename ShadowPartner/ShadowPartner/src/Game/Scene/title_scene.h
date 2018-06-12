//==========================================================
// 概要  :タイトルシーン
// Author:Itsuki Namito
// Copyright(c) Utsurugi.All right reserved.
//==========================================================

#ifndef _GAME_SCENE_TITLE_SCENE_H_
#define _GAME_SCENE_TITLE_SCENE_H_

//**********************************************************
// インクルードファイル
//**********************************************************
#include "../../Base/System/scene.h"

namespace shadowpartner
{
	//==========================================================
	// 概要  :タイトルシーン
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
		GameObject *title_logo_;

		// methods



		// 利用禁止
	};
}

#endif