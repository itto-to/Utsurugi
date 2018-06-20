//==========================================================
// �T�v  :�ҋ@�X�e�[�g
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
#include "player.h"
#include "../Common/jumper.h"

using namespace physics;

namespace shadowpartner
{
	IdleState::IdleState(Actor *owner) : ActorState(owner)
	{
	}

	void IdleState::Enter()
	{
		player_ = dynamic_cast<Player*>(owner_);
		jumper_ = owner_->GetComponent<Jumper>();
		box_collider_ = owner_->game_object_->GetComponent<BoxCollider>();
	}

	void IdleState::Execute()
	{
		RaycastHit hit_info = physics::PhysicsFunc::Raycast(
			owner_->transform_->position_ + Vector2::down() * 0.5f,
			Vector2::down(), 0.05f);
		
		if (hit_info.collider == nullptr || hit_info.collider->is_trigger_)
		{
			// �󒆂Ȃ痎��
			owner_->ChangeState(new JumpState(owner_));
		}
		else if (input::Input::Instance()->GetAxis(input::InputAxis::Horizontal) != 0.0f)
		{
			// �ړ�
			owner_->ChangeState(new WalkState(owner_));
		}
		else if (input::Input::Instance()->GetButtonDown(input::InputButton::Jump))
		{
			// �W�����v����
			jumper_->Jump();
			//box_collider_->AddForce(Vector2::up() * 100.0f);
			owner_->ChangeState(new JumpState(owner_));
		}
		else if (input::Input::Instance()->GetButtonDown(input::InputButton::Skill))
		{
			// �e�����
			player_->CreateShadow();
		}
		else if (input::Input::Instance()->GetAxis(input::InputAxis::Vertical) != 0.0f)
		{
			// �c�^��o��
			//owner_->ChangeState(new ClimbState(owner_));
		}
	}

}	// namespace shadowpartner