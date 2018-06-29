//==========================================================
// �T�v  :���s�X�e�[�g
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
		assert(collider_ != nullptr && "WalkState��Enter������collider_��nullptr");
#ifdef _DEBUG
		debug::Debug::Log("�v���C���[�̏�ԁF����");
#endif
	}

	void WalkState::ExecuteState()
	{
		// �ړ�
		float move = input::Input::Instance()->GetAxis(input::InputAxis::Horizontal);
		if (move != 0.0f) {
			if (move > 0.0f) {
				// �E�ړ��Ȃ�
				if (owner_->GetDirection() == ActorDirection::kLeft)
				{
					owner_->SetDirection(ActorDirection::kRight);
					owner_->GetComponent<Sprite>()->SetUvNormal();	// �X�v���C�g�𔽓]���Ȃ�
				}
			}
			else
			{
				// ���ړ��Ȃ�
				if (owner_->GetDirection() == ActorDirection::kRight)
				{
					owner_->SetDirection(ActorDirection::kLeft);
					owner_->GetComponent<Sprite>()->SetUvInvertX();	// �X�v���C�g�𔽓]���Ȃ�
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
			// �W�����v����
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