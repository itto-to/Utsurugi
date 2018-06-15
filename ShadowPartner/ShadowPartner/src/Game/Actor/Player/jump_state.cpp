//==========================================================
// 概要  :ジャンプステート
// Author:Ittoto
// Copyright(c) Utsurugi.All right reserved.
//==========================================================

#include "jump_state.h"

#include "idle_state.h"
#include "../../../Base/Physics/physics.h"
#include "../../../Base/Physics/Func/physics_func.h"
#include "../../../Base/Input/input.h"
#include "../Common/actor.h"

using namespace physics;

namespace shadowpartner
{

namespace {
	float kMoveSpeed = 10.0f;
}


JumpState::JumpState(Actor *owner) : ActorState(owner)
{
	Enter();
}

void JumpState::Enter()
{
	collider = owner_->game_object_->GetComponent<BoxCollider>();
}


void JumpState::Execute()
{
	// 移動
	float move = input::Input::Instance()->GetAxis(input::InputAxis::Horizontal);
	owner_->game_object_->transform_->position_.x += move * kMoveSpeed;

	// 着地判定
	RaycastHit hit_info = physics::PhysicsFunc::Raycast(
		owner_->transform_->position_ + Vector2::down() * 50.0f,
		Vector2::down(), 0.15f);

	if (hit_info.collider != nullptr)
	{
		//owner_->transform_->position_ = hit_info.hit_point + Vector2::up() * 50.0f;
		owner_->ChangeState(new IdleState(owner_));
	}
}

void JumpState::Move(float move)
{
	owner_->transform_->position_.x += move * kMoveSpeed;
	collider->SetTransform(owner_->transform_->position_, owner_->transform_->rotation_);
}

}