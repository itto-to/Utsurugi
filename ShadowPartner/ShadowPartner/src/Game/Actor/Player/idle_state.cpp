//==========================================================
// �T�v  :�ҋ@�X�e�[�g
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
		player_ = static_cast<Player*>(owner_);
		jumper_ = owner_->GetComponent<Jumper>();
		landing_trigger_ = owner_->GetComponent<LandingTrigger>();
		gimmick_trigger_ = owner_->GetComponent<GimmickTrigger>();
		action_trigger_ = owner_->GetComponent<ActionTrigger>();

#ifdef _DEBUG
		debug::Debug::Log("�v���C���[�̏�ԁF�ҋ@");
#endif
	}

	void IdleState::ExecuteState()
	{

		//RaycastHit hit_info = physics::PhysicsFunc::Raycast(
		//	owner_->transform_->position_ + Vector2::down() * 0.5f,
		//	Vector2::down(), 0.6f);
		//
		//if (hit_info.collider == nullptr || hit_info.collider->is_trigger_)
		if(!landing_trigger_->IsLanding())
		{
			// �󒆂Ȃ痎��
			owner_->ChangeState(new JumpState(owner_));
		}
		else if ((input::Input::Instance()->GetAxis(input::InputAxis::Horizontal) != 0.0f)  && owner_->IsControllable())
		{
			// �ړ�
			owner_->ChangeState(new WalkState(owner_));
		}
		else if (input::Input::Instance()->GetButtonDown(input::InputButton::Jump) && landing_trigger_->IsLanding() && owner_->IsControllable())
		{
			// �W�����v����
			jumper_->Jump();
			owner_->ChangeState(new JumpState(owner_));
		}
		else if (input::Input::Instance()->GetButtonDown(input::InputButton::Attack) && owner_->IsControllable())
		{
			// �e�����
			player_->CreateShadow();
		}
		else if ((input::Input::Instance()->GetAxis(input::InputAxis::Vertical) != 0.0f) && gimmick_trigger_->CanClimb() && owner_->IsControllable())
		{
			// �c�^��o��
			owner_->ChangeState(new ClimbState(owner_));
		}
		else if (input::Input::Instance()->GetButtonDown(input::InputButton::Action))
		{
			// �A�N�V����
			action_trigger_->Activate();
		}
	}

}	// namespace shadowpartner