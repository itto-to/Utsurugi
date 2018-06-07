//==========================================================
// 概要  :ウォークステート
// Author:Ittoto
// Copyright(c) Utsurugi.All right reserved.
//==========================================================
#ifndef _GAME_ACTOR_PLAYER_WALKSTATE_H_
#define _GAME_ACTOR_PLAYER_WALKSTATE_H_

#include "../Common/actor_state.h"

namespace shadowpartner
{

class WalkState : public ActorState {
public:
	WalkState(Actor *owner) : ActorState(owner) {}
	void Execute() override;
};

}

#endif