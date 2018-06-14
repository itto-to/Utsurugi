//==========================================================
// 概要  :登りステート
// Author:Ittoto
// Copyright(c) Utsurugi.All right reserved.
//==========================================================

#ifndef _GAME_ACTOR_PLAYER_CLIMBSTATE_H_
#define _GAME_ACTOR_PLAYER_CLIMBSTATE_H_

#include "../Common/actor_state.h"

namespace shadowpartner
{
	class Actor;

	class ClimbState : public ActorState
	{
		ClimbState(Actor *owner);
		void ClimbState::Enter() override;
		void ClimbState::Execute() override;
		void ClimbState::Exit() override;
	};

}	// namespace shadowpartner

#endif