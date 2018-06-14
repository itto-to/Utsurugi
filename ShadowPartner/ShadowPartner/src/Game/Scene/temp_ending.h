//==========================================================
// 概要  :タイトルシーン
// Author:Itsuki Namito
// Copyright(c) Utsurugi.All right reserved.
//==========================================================

#ifndef _GAME_SCENE_TEMP_ENDING_SCENE_H_
#define _GAME_SCENE_TEMP_ENDING_SCENE_H_

//**********************************************************
// インクルードファイル
//**********************************************************
#include "../../Base/System/scene.h"

namespace shadowpartner
{
	//==========================================================
	// 概要  :タイトルシーン
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



		// 利用禁止
	};
}

#endif