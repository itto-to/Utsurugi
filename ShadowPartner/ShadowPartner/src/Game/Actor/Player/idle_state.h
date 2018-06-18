//==========================================================
// 概要  :待機ステート
// Author:Ittoto
// Copyright(c) Utsurugi.All right reserved.
//==========================================================

#ifndef _GAME_ACTOR_PLAYER_IDLESTATE_H_
#define _GAME_ACTOR_PLAYER_IDLESTATE_H_

#include "../Common/actor_state.h"

namespace shadowpartner
{
	class Player;
	
	class IdleState : public ActorState {
	public:
		IdleState(Actor *owner);
		void Execute() override;

	protected:
		Player *player;

	private:
	};
}

#endif