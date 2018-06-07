//==========================================================
// 概要  :プレイヤーのテストシーン
// Author:Ittoto
// Copyright(c) Utsurugi.All right reserved.
//==========================================================

#ifndef _TEST_SCENE_PLAYERTESTSCENE_H_
#define _TEST_SCENE_PLAYERTESTSCENE_H_

//**********************************************************
// インクルードファイル
//**********************************************************
#include "../../Base/System/scene.h"

namespace shadowpartner
{
	//==========================================================
	// 概要  :プレイヤーのテスト用シーン
	//==========================================================
	class PlayerTestScene : public Scene
	{
	public:
		PlayerTestScene();
		virtual ~PlayerTestScene();

	protected:

		// methods
		HRESULT Init();
		void Uninit();
		void Update();

	private:
		// variables
		GameObject *player_;
		GameObject *shadow_;
		GameObject *camera_object_;
		GameObject *platform_;
	};

}	// namespace shadowpartner


#endif