//==========================================================
// 概要  :描画のテストシーン
// Author:Itsuki Namito
// Copyright(c) Utsurugi.All right reserved.
//==========================================================

#ifndef _TEST_SCENE_DRAW_TEST_SCENE_H_
#define _TEST_SCENE_DRAW_TEST_SCENE_H_

//**********************************************************
// インクルードファイル
//**********************************************************
#include "../../Base/System/scene.h"

namespace shadowpartner
{

	//==========================================================
	// 概要  :描画のテスト用シーン
	//==========================================================
	class DrawTestScene:public Scene
	{
	public:
		DrawTestScene();
		virtual ~DrawTestScene();
		
		// variables

		// methods

	protected:

		// methods
		HRESULT Init();
		void Update();

	private:
		// variables
		GameObject *camera_object;
		GameObject *draw_object;
		GameObject *draw_count_object;
		GameObject *draw_fps_object;


		// methods



		// 利用禁止
	};
}

#endif