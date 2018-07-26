//==========================================================
// 概要  :ステージ管理
// Author:ItsukiNamito
// Copyright(c) Utsurugi.All right reserved.
//==========================================================
#ifndef _GAME_STAGE_STAGE_MANAGER_H_
#define _GAME_STAGE_STAGE_MANAGER_H_

#include "../../Base/Element/component.h"

namespace shadowpartner
{
	class Sprite;

	class StageManager:public Component
	{
	public:
		static StageManager *main_;

		StageManager();
		~StageManager();

		void StageClear();
		void SetResultScreen(Sprite *screen);

	protected:
		void Update() override;

	private:

		bool is_cleared_;

		Sprite *result_sprite_;
		float result_alpha_;
	};
}

#endif