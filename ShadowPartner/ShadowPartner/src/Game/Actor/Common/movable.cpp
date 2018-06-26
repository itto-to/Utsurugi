//==========================================================
// 概要  :移動コンポーネント
// Author:Ittoto
// Copyright(c) Utsurugi.All right reserved.
//==========================================================
#include "movable.h"

#include "../../../Base/Physics/Element/collider.h"

#define CLAMP(x, low, hi)	(min(max((x), (low)), (hi)))

using namespace physics;

namespace shadowpartner
{

	namespace
	{
		const float kDefaultMaxSpeedX = 10.0f;
		const float kDefaultMaxSpeedY = FLT_MAX;
	}

	Movable::Movable()	:
		max_speed_x_(kDefaultMaxSpeedX),
		max_speed_y_(kDefaultMaxSpeedY)
	{
	}
	void Movable::Start()
	{
		collider_ = GetComponentInherit<Collider>();
	}

	void Movable::AddForce(const Vector2 &move)
	{
		collider_->AddForce(move);
		collider_->SetVelocityX(CLAMP(collider_->VelocityX(), -max_speed_x_, max_speed_x_));
		collider_->SetVelocityY(CLAMP(collider_->VelocityY(), -max_speed_y_, max_speed_y_));
	}

	void Movable::Move(const Vector2 &move)
	{
		game_object_->transform_->position_ += move;
		collider_->SetTransform(transform_->position_, transform_->rotation_);
	}

}	// namespace shadowpartner