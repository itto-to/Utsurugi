//==========================================================
// 概要  :リザルトシーン
// Author:Ittoto
// Copyright(c) Utsurugi.All right reserved.
//==========================================================


#ifndef _GAME_SCENE_RESULTSCENE_H_
#define _GAME_SCENE_RESULTSCENE_H_

//**********************************************************
// インクルードファイル
//**********************************************************
#include "../../Base/System/scene.h"

namespace shadowpartner
{
	//==========================================================
	// 概要  :リザルトシーン
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



		// 利用禁止
	};
}

#endif