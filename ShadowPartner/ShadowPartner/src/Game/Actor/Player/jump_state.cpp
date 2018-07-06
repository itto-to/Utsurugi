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
	const float kMoveForce = 100.0f;
	const float kMaxSpeedX = 1.0f;
}


JumpState::JumpState(Actor *owner) : ActorState(owner)
{
}

void JumpState::Enter()
{
	landing_trigger_ = owner_->GetComponent<LandingTrigger>();
	collider_ = owner_->GetComponentInherit<Collider>();
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
		if (move > 0.0f) {
			// �E�ړ��Ȃ�
			if (owner_->GetDirection() == ActorDirection::kLeft)
			{
				owner_->SetDirection(ActorDirection::kRight);
				owner_->GetComponent<Sprite>()->SetFlipX(false);	// �X�v���C�g�𔽓]���Ȃ�
			}
		}
		else
		{
			// ���ړ��Ȃ�
			if (owner_->GetDirection() == ActorDirection::kRight)
			{
				owner_->SetDirection(ActorDirection::kLeft);
				owner_->GetComponent<Sprite>()->SetFlipX(true);	// �X�v���C�g�𔽓]����
			}
		}

		Vector2 t = Vector2::right() * move * kMoveForce;
		Move(t);
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

	//RaycastHit hit_info = physics::PhysicsFunc::Raycast(
	//	owner_->transform_->position_ + Vector2::down() * 0.5f,
	//	Vector2::down(), 0.6f);

	//// FIXME:���C�L���X�g�ŕԂ��Ă����R���C�_�[���g���K�[�������ꍇ�ҋ@��ԂɑJ�ڂ��Ȃ��Ȃ��Ă��܂�
	//if (hit_info.collider != nullptr && !hit_info.collider->is_trigger_)
	//{
	//	owner_->ChangeState(new IdleState(owner_));
	//}
}

bool JumpState::IsFalling() const
{
	return collider_->Velocity().y <= 0.0f;
}

void JumpState::Move(const math::Vector2 & move)
{
	collider_->AddForce(move);
	collider_->SetVelocityX(CLAMP(collider_->VelocityX(), -kMaxSpeedX, kMaxSpeedX));
}

}	// namespace shadowpartner