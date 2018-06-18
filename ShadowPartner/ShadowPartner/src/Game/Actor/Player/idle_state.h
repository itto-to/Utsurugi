//==========================================================
// 概要  :待機ステート
// Author:Ittoto
// Copyright(c) Utsurugi.All right reserved.
//==========================================================

#ifndef _GAME_ACTOR_PLAYER_IDLESTATE_H_
#define _GAME_ACTOR_PLAYER_IDLESTATE_H_

#include "../Common/actor_state.h"

namespace physics
{
	class BoxCollider;
}

namespace shadowpartner
{
	class Player;
	
	class IdleState : public ActorState {
	public:
		IdleState(Actor *owner);
		void Enter() override;
		void Execute() override;

	protected:
		Player *player_;
		physics::BoxCollider *box_collider_;

	private:
	};
}

#endif