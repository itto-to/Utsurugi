//==========================================================
// 概要  :着地判定用トリガー
// Author:Ittoto
// Copyright(c) Utsurugi.All right reserved.
//==========================================================

#ifndef _GAME_ACTOR_PLAYER_LANDINGTRIGGER_H_
#define _GAME_ACTOR_PLAYER_LANDINGTRIGGER_H_

#include "../../../Base/Physics/Element/box_collider.h"

namespace shadowpartner
{

	class LandingTrigger : public physics::BoxCollider
	{
	public:
		LandingTrigger(const physics::BoxInitializer &box_init);
		void OnTriggerEnter(Collider *col) override;
		void OnTriggerExit(Collider *col) override;
		bool IsLanding();

	protected:
		int landing_count_;
		bool is_landing_;
	};

}

#endif