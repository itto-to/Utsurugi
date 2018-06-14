//==========================================================
// 概要  :待機ステート
// Author:Ittoto
// Copyright(c) Utsurugi.All right reserved.
//==========================================================

#include "idle_state.h"

#include "jump_state.h"
#include "walk_state.h"
#include "climb_state.h"
#include "../Common/actor.h"
#include "../../../Base/Input/input.h"
#include "../../../Base/Physics/physics.h"

using namespace physics;

namespace shadowpartner
{

	void IdleState::Execute()
	{
		if (input::Input::Instance()->GetAxis(input::InputAxis::Horizontal) != 0.0f)
		{
			// 移動
			owner_->ChangeState(new WalkState(owner_));
		}
		else if (input::Input::Instance()->GetButtonDown(input::InputButton::Jump))
		{
			// ジャンプ入力
			BoxCollider *box_collider = owner_->GetComponent<BoxCollider>();
			box_collider->AddForce(Vector2::up() * 700000000.0f);
			owner_->ChangeState(new JumpState(owner_));
		}
		else if (input::Input::Instance()->GetButtonDown(input::InputButton::Skill))
		{
			// 影を作る
			
		}
		else if (input::Input::Instance()->GetAxis(input::InputAxis::Vertical) != 0.0f)
		{
			// ツタを登る
			//owner_->ChangeState(new ClimbState(owner_));
		}
	}

}	// namespace shadowpartner