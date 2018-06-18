//==========================================================
// 概要  :歩行ステート
// Author:Ittoto
// Copyright(c) Utsurugi.All right reserved.
//==========================================================
#include "walk_state.h"

#include "jump_state.h"
#include "idle_state.h"
#include "../../../Base/Physics/Element/box_collider.h"
#include "../../../Base/Element/gameobject.h"
#include "../Common/actor.h"
#include "../../../Base/Input/input.h"
#include "../../../Base/Physics/physics.h"

using namespace physics;

namespace shadowpartner
{
	namespace{
		float kMoveSpeed = 2.0f;
	}

	WalkState::WalkState(Actor * owner) : ActorState(owner)
	{
		Enter();
	}

	void WalkState::Enter()
	{
		collider = owner_->game_object_->GetComponent<BoxCollider>();
	}

	void WalkState::Execute()
	{
		float move = input::Input::Instance()->GetAxis(input::InputAxis::Horizontal);
		//BoxCollider *box_collider = owner_->GetComponent<BoxCollider>();
		Move(move * kMoveSpeed);

		if (move == 0.0f) {
			// 停止
			owner_->ChangeState(new IdleState(owner_));
		}
		else if (input::Input::Instance()->GetButtonDown(input::InputButton::Jump)) {
			// ジャンプ入力
			collider->AddForce(Vector2::up() * 700000000.0f);
			owner_->ChangeState(new JumpState(owner_));
		}
	}

	void WalkState::Move(float move)
	{
		owner_->transform_->position_.x += move * kMoveSpeed;
		collider->SetTransform(owner_->transform_->position_, owner_->transform_->rotation_);
	}
}