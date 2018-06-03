//==========================================================
// 概要  :ライトのテストシーン
// Author:Itsuki Namito
// Copyright(c) Utsurugi.All right reserved.
//==========================================================

#ifndef _TEST_SCENE_LIGHT_TEST_SCENE_H_
#define _TEST_SCENE_LIGHT_TEST_SCENE_H_

//**********************************************************
// インクルードファイル
//**********************************************************
#include "../../Base/System/scene.h"

namespace shadowpartner
{
	//==========================================================
	// 概要  :描画のテスト用シーン
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



		// 利用禁止
	};
}

#endif