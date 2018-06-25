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
	class Jumper;
	class LandingTrigger;

	class IdleState : public ActorState {
	public:
		IdleState(Actor *owner);
		void Enter() override;
		virtual void ExecuteState() override;

	protected:
		Player *player_;
		Jumper *jumper_;
		LandingTrigger *landing_trigger_;

	private:
	};
}

#endif