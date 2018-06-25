//==========================================================
// �T�v  :�W�����v�X�e�[�g
// Author:Ittoto
// Copyright(c) Utsurugi.All right reserved.
//==========================================================

#include "jump_state.h"

#include "idle_state.h"
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
	collider_ = owner_->game_object_->GetComponentInherit<Collider>();
#ifdef _DEBUG
	debug::Debug::Log("�v���C���[�̏�ԁF�W�����v");
#endif

}


void JumpState::ExecuteState()
{
	// �ړ�
	float move = input::Input::Instance()->GetAxis(input::InputAxis::Horizontal);
	Vector2 t = Vector2::right() * move * kMoveForce;
	Move(t);

	// ���n����
	if (!IsFalling())	// �㏸���Ȃ璅�n���肵�Ȃ�
		return;

	RaycastHit hit_info = physics::PhysicsFunc::Raycast(
		owner_->transform_->position_ + Vector2::down() * 0.5f,
		Vector2::down(), 0.6f);

	// FIXME:���C�L���X�g�ŕԂ��Ă����R���C�_�[���g���K�[�������ꍇ�ҋ@��ԂɑJ�ڂ��Ȃ��Ȃ��Ă��܂�
	if (hit_info.collider != nullptr && !hit_info.collider->is_trigger_)
	{
		owner_->ChangeState(new IdleState(owner_));
	}
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