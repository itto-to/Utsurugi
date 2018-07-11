//==========================================================
// 概要  :ジャンプコンポーネント
// Author:Ittoto
// Copyright(c) Utsurugi.All right reserved.
//==========================================================
#include "jumper.h"

#include "../../../Base/Physics/Element/collider.h"

using namespace physics;

namespace shadowpartner
{
	namespace
	{
		const float kDefaultInitialVelocity = 2.0f;
		const float kDefaultGravityScale = 1.0f;
	}

	Jumper::Jumper() : 
		can_jump_(true),
		initial_velocity_(kDefaultInitialVelocity),
		gravity_scale_(kDefaultGravityScale)
	{
		initial_velocity_ = kDefaultInitialVelocity;
		gravity_scale_ = kDefaultGravityScale;
	}

	Jumper::Jumper(bool can_jump, float force, float gravity)
	{
		can_jump_ = can_jump;
		initial_velocity_ = force;
		gravity_scale_ = gravity;
	}

	void Jumper::Start()
	{
		collider_ = game_object_->GetComponentInherit<Collider>();
		transform_ = game_object_->GetComponent<Transform>();
	}

	void Jumper::Jump()
	{
		if (can_jump_)
		{
			collider_->SetVelocityY(initial_velocity_);
		}
	}

	float Jumper::Force()
	{
		return initial_velocity_;
	}

	void Jumper::SetCanJump(bool can_jump)
	{
		can_jump_ = can_jump;
	}

	bool Jumper::CanJump()
	{
		return can_jump_;
	}

	void Jumper::SetInitialVelocity(float initial_velocity)
	{
		initial_velocity_ = initial_velocity;
	}

	float Jumper::Gravity()
	{
		return gravity_scale_;
	}

	void Jumper::SetGravity(float gravity)
	{
		gravity_scale_ = gravity;
	}

}	// namespace shadowpartner