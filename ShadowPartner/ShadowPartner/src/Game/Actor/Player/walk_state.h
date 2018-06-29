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
	class Collider;
}

namespace shadowpartner
{
class Sprite;
class Jumper;

class WalkState : public ActorState {
public:
	WalkState(Actor *owner);
	void Enter() override;
	void ExecuteState() override;

private:
	physics::Collider *collider_;
	Jumper *jumper_;
	Sprite *sprite_;

	void Move(const float move);
};

}

#endif