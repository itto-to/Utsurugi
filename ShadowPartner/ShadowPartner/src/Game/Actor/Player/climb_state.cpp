//==========================================================
// ŠT—v  :“o‚èƒXƒe[ƒg
// Author:Ittoto
// Copyright(c) Utsurugi.All right reserved.
//==========================================================
#include "climb_state.h"

#include "player.h"
#include "jump_state.h"
#include "../Common/actor.h"
#include "../Common/movable.h"
#include "../../../Base/Element/component.h"
#include "../../../Base/Input/input.h"
#include "../../../Base/Physics/Element/collider.h"
#include "gimmck_trigger.h"

using namespace physics;

namespace shadowpartner
{
	namespace
	{
		const float kClimbSpeed = 0.1f;
	}


	ClimbState::ClimbState(Actor* owner) : ActorState(owner), movable_(nullptr), collider_(nullptr), old_gravity_scale_(1.0f) {}
 
	void ClimbState::Enter()
	{
		player_ = owner_->GetComponent<Player>();
		collider_ = owner_->GetComponentInherit<Collider>();
		gimmick_trigger_ = owner_->GetComponent<GimmickTrigger>();

		// ƒLƒƒƒ‰‰ñ“]
		if (owner_->GetDirection() == Actor::ActorDirection::kRight)
		{
			owner_->game_object_->transform_->rotation_ = -90;
		}
		else
		{
			owner_->game_object_->transform_->rotation_ = 90;
		}

		// d—Í‚ðƒ[ƒ‚É
		old_gravity_scale_ = collider_->GravityScale();
		collider_->SetGravityScale(0.0f);
	}

	void ClimbState::ExecuteState()
	{
		Vector2 move;
		move.x = input::Input::Instance()->GetAxis(input::InputAxis::Horizontal) * kClimbSpeed;
		move.y = input::Input::Instance()->GetAxis(input::InputAxis::Vertical) * kClimbSpeed;

		collider_->Move(move);
		//owner_->game_object_->transform_->position_.y += move;

		if (!gimmick_trigger_->CanClimb())
		{
			owner_->ChangeState(new JumpState(owner_));
		}
	}

	void ClimbState::Exit()
	{
		// ‰ñ“]‚ð–ß‚·
		owner_->game_object_->transform_->rotation_ = D3DXToRadian(0);
		// d—Í‚ð–ß‚·
		collider_->SetGravityScale(old_gravity_scale_);
	}

}	// namespace shadowpartner