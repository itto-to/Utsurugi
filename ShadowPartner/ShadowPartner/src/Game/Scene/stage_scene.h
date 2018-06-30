//==========================================================
// 概要  :ステージシーンの基底クラス
// Author:Itsuki Namito
// Copyright(c) Utsurugi.All right reserved.
//==========================================================

#ifndef _GAME_SCENE_STAGE_SCENE_H_
#define _GAME_SCENE_STAHE_SCENE_H_

//**********************************************************
// インクルードファイル
//**********************************************************
#include "../../Base/System/scene.h"

#define STAGE_FASE_MAX (3)
#define BACK_GROUND_OBJECT_MAX (20)

namespace shadowpartner
{
	//==========================================================
	// 概要  :ステージシーンの基底クラス
	//==========================================================
	class StageScene:public Scene
	{
	public:
		StageScene(int phase_num);
		virtual ~StageScene();
		
		// variables

		// methods

	protected:

		// variables
		GameObject *camera_object_;
		GameObject *back_ground_;
		GameObject *back_ground_objects_[BACK_GROUND_OBJECT_MAX];
		GameObject *stages_[STAGE_FASE_MAX];
		GameObject *moon_light_;
		GameObject *player_;
		GameObject *shadow_;
		GameObject *enemy_;
		GameObject *vine_;
		GameObject *tree_log_;
		GameObject *hinge_joint_;
		GameObject *hinge_joint_base_;

		int phase_num_;
		int current_phase_;					// ステージのフェーズ

		// methods
		HRESULT Init();
		void Update();
		void Uninit();

		void NextPhase();
		void PrevPhase();

		virtual void CreateBackGround();

	private:
		// variables


		// methods
		void CameraAdjustToCurrentPhase();


		// 利用禁止
	};
}

#endif