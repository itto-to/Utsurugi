//==========================================================
// 概要  :ジャンプステート
// Author:Ittoto
// Copyright(c) Utsurugi.All right reserved.
//==========================================================

#ifndef _GAME_ACTOR_PLAYER_JUMPSTATE_H_
#define _GAME_ACTOR_PLAYER_JUMPSTATE_H_

#include "../Common/actor_state.h"

namespace shadowpartner
{

class JumpState : public ActorState {
public:
	JumpState(Actor *owner) : ActorState(owner) {}
	void Execute() override;
};

}

#endif