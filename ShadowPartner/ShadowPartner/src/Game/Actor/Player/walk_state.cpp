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
		float kMoveForce = 100.0f;
		float kMaxSpeedX = 1.0f;
	}

	WalkState::WalkState(Actor *owner) : ActorState(owner)
	{
		Enter();
	}

	void WalkState::Enter()
	{
		collider_ = owner_->GetComponentInherit<Collider>();
		jumper_ = owner_->GetComponent<Jumper>();
		assert(collider_ != nullptr && "WalkStateのEnter処理でcollider_がnullptr");
#ifdef _DEBUG
		debug::Debug::Log("プレイヤーの状態：歩き");
#endif
	}

	void WalkState::ExecuteState()
	{
		// 移動
		float move = input::Input::Instance()->GetAxis(input::InputAxis::Horizontal);
		if (move != 0.0f) {
			Move(move * kMoveForce);
		}
		else {
			float x = collider_->VelocityX() * 0.9f;
			if (fabs(x) < 0.05f) {
				collider_->SetVelocityX(0.0f);
				owner_->ChangeState(new IdleState(owner_));
			}
			else
			{
				collider_->SetVelocityX(x);
			}
		}
		//if (collider_->Velocity().x == 0.0f && move == 0.0f) {
		//	// 停止
		//	owner_->ChangeState(new IdleState(owner_));
		//}
		if (input::Input::Instance()->GetButtonDown(input::InputButton::Jump))
		{
			// ジャンプ入力
			jumper_->Jump();
			owner_->ChangeState(new JumpState(owner_));
		}
	}

	void WalkState::Move(const float move)
	{
		collider_->AddForce(Vector2::right() * move);
		collider_->SetVelocityX(CLAMP(collider_->VelocityX(), -kMaxSpeedX, kMaxSpeedX));
		//collider_->SetTransform(owner_->transform_->position_, owner_->transform_->rotation_);
	}
}