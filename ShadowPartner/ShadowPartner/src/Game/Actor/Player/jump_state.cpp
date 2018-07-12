//==========================================================
// �T�v  :�W�����v�X�e�[�g
// Author:Ittoto
// Copyright(c) Utsurugi.All right reserved.
//==========================================================

#include "jump_state.h"

#include "idle_state.h"
#include "landing_trigger.h"
#include "walk_state.h"
#include "../../../Base/2D/sprite.h"
#include "../../../Base/Physics/physics.h"
#include "../../../Base/Physics/Func/physics_func.h"
#include "../../../Base/Input/input.h"
#include "../Common/actor.h"

#ifdef _DEBUG
#include "../../../Base/Debug/debugger.h"
#endif

#define CLAMP(x, low, hi)	(min(max((x), (low)), (hi)))

using namespace physics;

namespace shadowpartner
{

namespace
{
	const float kMoveForce    = 100.0f;
	const float kMaxSpeedX    = 2.5f;
	const float kAcceleration = 0.75f;
}


JumpState::JumpState(Actor *owner) : ActorState(owner)
{
}

void JumpState::Enter()
{
	landing_trigger_ = owner_->GetComponent<LandingTrigger>();
	collider_ = owner_->GetComponentInherit<Collider>();
	sprite_ = owner_->GetComponent<Sprite>();

#ifdef _DEBUG
	debug::Debug::Log("�v���C���[�̏�ԁF�W�����v");
#endif

}


void JumpState::ExecuteState()
{
	// �ړ�
	float move = input::Input::Instance()->GetAxis(input::InputAxis::Horizontal);

	if (move != 0.0f)
	{
		if (move > 0.0f)
		{
			// �E�ړ��Ȃ�
			if (owner_->GetDirection() == ActorDirection::kLeft)
			{
				owner_->SetDirection(ActorDirection::kRight);
				sprite_->SetFlipX(false);	// �X�v���C�g�𔽓]���Ȃ�
				sprite_->SetOffset(-sprite_->GetOffset());
			}
		}
		else
		{
			// ���ړ��Ȃ�
			if (owner_->GetDirection() == ActorDirection::kRight)
			{
				owner_->SetDirection(ActorDirection::kLeft);
				sprite_->SetFlipX(true);	// �X�v���C�g�𔽓]����
				sprite_->SetOffset(-sprite_->GetOffset());
			}
		}
		Move(move);
	}

	// ���n����
	if (!IsFalling())	// �㏸���Ȃ璅�n���肵�Ȃ�
		return;

	if (landing_trigger_->IsLanding())
	{
		if (collider_->VelocityX() != 0.0f) {
			owner_->ChangeState(new WalkState(owner_));
			return;
		}
		else
		{
			owner_->ChangeState(new IdleState(owner_));
			return;
		}
	}
}

bool JumpState::IsFalling() const
{
	return collider_->Velocity().y <= 0.0f;
}

void JumpState::Move(const float move)
{
	collider_->SetVelocityX(CLAMP(collider_->VelocityX() + kAcceleration * move, -kMaxSpeedX, kMaxSpeedX));
}

}	// namespace shadowpartner