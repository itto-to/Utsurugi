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
		const float kDefaultForce = 150.0f;
		const float kDefaultGravity = 1.0f;
	}

	Jumper::Jumper() : can_jump_(true)
	{
		force_ = kDefaultForce;
		gravity_ = kDefaultGravity;
	}

	Jumper::Jumper(bool can_jump, float force, float gravity)
	{
		can_jump_ = can_jump;
		force_ = force;
		gravity_ = gravity;
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
			collider_->AddForce(Vector2(0.0f, force_));
		}
	}

	float Jumper::Force()
	{
		return force_;
	}

	void Jumper::SetCanJump(bool can_jump)
	{
		can_jump_ = can_jump;
	}

	bool Jumper::CanJump()
	{
		return can_jump_;
	}

	void Jumper::SetForce(float force)
	{
		force_ = force;
	}

	float Jumper::Gravity()
	{
		return gravity_;
	}

	void Jumper::SetGravity(float gravity)
	{
		gravity_ = gravity;
	}

}	// namespace shadowpartner