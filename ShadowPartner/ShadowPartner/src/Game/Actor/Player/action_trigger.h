//==========================================================
// 概要  :ギミックへのアクション用トリガー
// Author:Ittoto
// Copyright(c) Utsurugi.All right reserved.
//==========================================================
#ifndef _GAME_ACTOR_PLAYER_ACTIONTRIGGER_H_
#define _GAME_ACTOR_PLAYER_ACTIONTRIGGER_H_

#include "../../../Base/Physics/Element/box_collider.h"

namespace shadowpartner
{
	class ActionTrigger : public physics::BoxCollider
	{
	public:
		ActionTrigger(const physics::BoxInitializer &box_init);
		void OnTriggerEnter(Collider *col) override;
		void OnTriggerExit(Collider *col) override;
		
		void Activate();

	protected:
		std::vector<GameObject*> gimmick_objects_;
	};
}

#endif