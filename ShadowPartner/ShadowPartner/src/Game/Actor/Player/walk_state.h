//==========================================================
// 概要  :歩行ステート
// Author:Ittoto
// Copyright(c) Utsurugi.All right reserved.
//==========================================================

#ifndef _GAME_ACTOR_PLAYER_WALKSTATE_H_
#define _GAME_ACTOR_PLAYER_WALKSTATE_H_

#include "../Common/actor_state.h"

namespace physics
{
	class BoxCollider;
}

namespace shadowpartner
{

class WalkState : public ActorState {
public:
	WalkState(Actor *owner);
	void Enter() override;
	void Execute() override;

private:
	physics::BoxCollider *collider;

	void Move(float delta);
};

}

#endif