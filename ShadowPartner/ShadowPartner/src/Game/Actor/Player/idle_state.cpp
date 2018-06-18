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

using namespace physics;

namespace shadowpartner
{
	IdleState::IdleState(Actor *owner) : ActorState(owner)
	{
		player = dynamic_cast<Player*>(owner_);
	}

	void IdleState::Execute()
	{
		if (input::Input::Instance()->GetAxis(input::InputAxis::Horizontal) != 0.0f)
		{
			// �ړ�
			owner_->ChangeState(new WalkState(owner_));
		}
		else if (input::Input::Instance()->GetButtonDown(input::InputButton::Jump))
		{
			// �W�����v����
			BoxCollider *box_collider = owner_->GetComponent<BoxCollider>();
			box_collider->AddForce(Vector2::up() * 700000000.0f);
			owner_->ChangeState(new JumpState(owner_));
		}
		else if (input::Input::Instance()->GetButtonDown(input::InputButton::Skill))
		{
			// �e�����
			player->CreateShadow();
		}
		else if (input::Input::Instance()->GetAxis(input::InputAxis::Vertical) != 0.0f)
		{
			// �c�^��o��
			//owner_->ChangeState(new ClimbState(owner_));
		}
	}

}	// namespace shadowpartner