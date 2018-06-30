//==========================================================
// 概要  :最初のステージクラス
// Author:Itsuki Namito
// Copyright(c) Utsurugi.All right reserved.
//==========================================================

#ifndef _GAME_SCENE_FIRST_STAGE_SCENE_H_
#define _GAME_SCENE_FIRST_STAHE_SCENE_H_

//**********************************************************
// インクルードファイル
//**********************************************************
#include "stage_scene.h"

namespace shadowpartner
{
	//==========================================================
	// 概要  :ステージシーンの基底クラス
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
		GameObject *clear_gate_;
		GameObject *small_light_;
		GameObject *middle_light_;
		GameObject *tmp_large_light_[4];
		GameObject *gate_;
		GameObject *test_object_;
		GameObject *ivy_chain_;
		GameObject *ivy_joint_;

		GameObject *invisible_wall_;

		// methods


		// 利用禁止
	};
}

#endif