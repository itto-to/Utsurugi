//==========================================================
// 概要  :待機ステート
// Author:Ittoto
// Copyright(c) Utsurugi.All right reserved.
//==========================================================

#include "idle_state.h"

#include "jump_state.h"
#include "walk_state.h"
#include "climb_state.h"
#include "landing_trigger.h"
#include "../Common/actor.h"
#include "../../../Base/Input/input.h"
#include "../../../Base/Physics/physics.h"
#include "player.h"
#include "shadow.h"
#include "../Common/jumper.h"
#include "gimmck_trigger.h"
#include "action_trigger.h"

#ifdef _DEBUG
#include "../../../Base/Debug/debugger.h"
#endif

using namespace physics;

namespace shadowpartner
{
	IdleState::IdleState(Actor *owner) : ActorState(owner)
	{
	}

	void IdleState::Enter()
	{
		player_ = dynamic_cast<Player*>(owner_);
		shadow_ = dynamic_cast<Shadow*>(owner_);
		jumper_ = owner_->GetComponent<Jumper>();
		landing_trigger_ = owner_->GetComponent<LandingTrigger>();
		gimmick_trigger_ = owner_->GetComponent<GimmickTrigger>();
		action_trigger_ = owner_->GetComponent<ActionTrigger>();

#ifdef _DEBUG
		debug::Debug::Log("プレイヤーの状態：待機");
#endif
	}

	void IdleState::ExecuteState()
	{
		if(!landing_trigger_->IsLanding())
		{
			// 空中なら落下
			owner_->ChangeState(new JumpState(owner_));
			return;
		}
		else if ((input::Input::Instance()->GetAxis(input::InputAxis::Horizontal) != 0.0f)  && owner_->IsControllable())
		{
			// 移動
			owner_->ChangeState(new WalkState(owner_));
			return;
		}
		else if (input::Input::Instance()->GetButtonDown(input::InputButton::Jump) && landing_trigger_->IsLanding() && owner_->IsControllable() && jumper_->CanJump())
		{
			// ジャンプ入力
			jumper_->Jump();
			owner_->ChangeState(new JumpState(owner_));
			return;
		}
		else if (input::Input::Instance()->GetButtonDown(input::InputButton::Attack) && owner_->IsControllable())
		{
			if (owner_->tag_ == Tag::kPlayer)
			{
				// 影を作る
				player_->CreateShadow();
			}
			else if (owner_->tag_ == Tag::kShadow)
			{
				const int kCountCanReturnToPlayerShadow = 10;
				// プレイヤーの影に戻る
				if (counter_ > kCountCanReturnToPlayerShadow)
				{
					shadow_->ReturnToPlayerShadow();
				}
			}
		}
		else if ((input::Input::Instance()->GetAxis(input::InputAxis::Vertical) != 0.0f) && gimmick_trigger_->CanClimb() && owner_->IsControllable())
		{
			// ツタを登る
			owner_->ChangeState(new ClimbState(owner_));
			return;
		}
		else if (input::Input::Instance()->GetButtonDown(input::InputButton::Action))
		{
			// アクション
			action_trigger_->Activate();
		}
	}

}	// namespace shadowpartner