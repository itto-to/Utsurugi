//==========================================================
// 概要  :歩行ステート
// Author:Ittoto
// Copyright(c) Utsurugi.All right reserved.
//==========================================================
#include "walk_state.h"

#include <algorithm>
#include <cmath>
#include <cassert>

#include "../Common/jumper.h"
#include "jump_state.h"
#include "idle_state.h"
#include "../../../Base/2D/sprite.h"
#include "../../../Base/Physics/Element/box_collider.h"
#include "../../../Base/Element/gameobject.h"
#include "../Common/actor.h"
#include "../../../Base/Input/input.h"
#include "../../../Base/Physics/physics.h"

#ifdef _DEBUG
#include "../../../Base/Debug/debugger.h"
#endif

#define CLAMP(x, low, hi)	(min(max((x), (low)), (hi)))

using namespace physics;

namespace shadowpartner
{
	namespace{
		const float kMoveForce = 100.0f;
		const float kMaxSpeedX = 1.0f;
		const float kDampingFactor = 0.8f;
	}

	WalkState::WalkState(Actor *owner) : ActorState(owner)
	{
		Enter();
	}

	void WalkState::Enter()
	{
		collider_ = owner_->GetComponentInherit<Collider>();
		jumper_ = owner_->GetComponent<Jumper>();
		sprite_ = owner_->GetComponent<Sprite>();

#ifdef _DEBUG
		assert(collider_ != nullptr && "WalkStateのEnter処理でcollider_がnullptr");
		debug::Debug::Log("プレイヤーの状態：歩き");
#endif
	}

	void WalkState::ExecuteState()
	{
		// 移動
		float move = input::Input::Instance()->GetAxis(input::InputAxis::Horizontal);
		if (move != 0.0f) {
			if (move > 0.0f) {
				// 右移動なら
				if (owner_->GetDirection() == ActorDirection::kLeft)
				{
					owner_->SetDirection(ActorDirection::kRight);
					owner_->GetComponent<Sprite>()->SetUvNormal();	// スプライトを反転しない
				}
			}
			else
			{
				// 左移動なら
				if (owner_->GetDirection() == ActorDirection::kRight)
				{
					owner_->SetDirection(ActorDirection::kLeft);
					owner_->GetComponent<Sprite>()->SetUvInvertX();	// スプライトを反転しない
				}
			}

			Move(move * kMoveForce);
		}
		else {
			float x = collider_->VelocityX() * kDampingFactor;
			if (fabs(x) < 0.05f) {
				collider_->SetVelocityX(0.0f);
				owner_->ChangeState(new IdleState(owner_));
			}
			else
			{
				collider_->SetVelocityX(x);
			}
		}

		if (input::Input::Instance()->GetButtonDown(input::InputButton::Jump))
		{
			// ジャンプ入力
			jumper_->Jump();
			owner_->ChangeState(new JumpState(owner_));
		}

		// テクスチャアニメーション
		const int kNumDivideX = 4;
		const int kNumDivideY = 4;
		const int kNumAnimPattern = 6;
		const int kCountPerFrame = 10;

		sprite_->SetUvSize(Vector2(0.25f, 0.25f));

		int pattern_no = (counter_ / kCountPerFrame) % kCountPerFrame;

		Vector2 tex_coord;
		tex_coord.x = (pattern_no % kNumDivideX) * 0.25f;
		tex_coord.y = (pattern_no / kNumDivideX) * 0.25f;

		sprite_->SetUvOffset(tex_coord);
	}

	void WalkState::Move(const float move)
	{
		collider_->AddForce(Vector2::right() * move);
		collider_->SetVelocityX(CLAMP(collider_->VelocityX(), -kMaxSpeedX, kMaxSpeedX));
		//collider_->SetTransform(owner_->transform_->position_, owner_->transform_->rotation_);
	}
}