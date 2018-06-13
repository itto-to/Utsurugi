//==========================================================
// 概要  :歩行ステート
// Author:Ittoto
// Copyright(c) Utsurugi.All right reserved.
//==========================================================
#include "walk_state.h"

#include "jump_state.h"
#include "idle_state.h"
#include "../../../Base/Element/gameobject.h"
#include "../Common/actor.h"
#include "../../../Base/Input/input.h"
#include "../../../Base/Physics/physics.h"

using namespace physics;

namespace shadowpartner
{
	namespace{
		float kMoveSpeed = 10.0f;
	}

	void WalkState::Execute()
	{
		float move = input::Input::Instance()->GetAxis(input::InputAxis::Horizontal);
		owner_->game_object_->transform_->position_.x += move * kMoveSpeed;

		if (move == 0.0f) {
			// 停止
			owner_->ChangeState(new IdleState(owner_));
		}
		else if (input::Input::Instance()->GetButtonDown(input::InputButton::Jump)) {
			// ジャンプ入力
			BoxCollider *box_collider = owner_->GetComponent<BoxCollider>();
			box_collider->AddForce(Vector2::up() * 700000000.0f);
			owner_->ChangeState(new JumpState(owner_));
		}
	}
}