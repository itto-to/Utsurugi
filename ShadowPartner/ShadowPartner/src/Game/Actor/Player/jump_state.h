//==========================================================
// 概要  :ジャンプステート
// Author:Ittoto
// Copyright(c) Utsurugi.All right reserved.
//==========================================================

#ifndef _GAME_ACTOR_PLAYER_JUMPSTATE_H_
#define _GAME_ACTOR_PLAYER_JUMPSTATE_H_

#include "../Common/actor_state.h"
#include "../../../Base/Math/math.h"

namespace physics
{
	class Collider;
}

namespace shadowpartner
{
	class LandingTrigger;

class JumpState : public ActorState {
public:
	JumpState(Actor *owner);
	void Enter() override;
	virtual void ExecuteState() override;
	bool IsFalling() const;

private:
	physics::Collider *collider_;
	LandingTrigger *landing_trigger_;

	void Move(const math::Vector2 &move);
};

}	// namespace shadowpartner

#endif