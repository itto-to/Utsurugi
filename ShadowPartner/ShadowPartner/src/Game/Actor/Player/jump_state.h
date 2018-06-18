//==========================================================
// 概要  :ジャンプステート
// Author:Ittoto
// Copyright(c) Utsurugi.All right reserved.
//==========================================================

#ifndef _GAME_ACTOR_PLAYER_JUMPSTATE_H_
#define _GAME_ACTOR_PLAYER_JUMPSTATE_H_

#include "../Common/actor_state.h"

namespace physics
{
	class BoxCollider;
}

namespace shadowpartner
{

class JumpState : public ActorState {
public:
	JumpState(Actor *owner);
	void Enter() override;
	void Execute() override;

private:
	physics::BoxCollider *collider_;

	void Move(float delta);
};

}

#endif