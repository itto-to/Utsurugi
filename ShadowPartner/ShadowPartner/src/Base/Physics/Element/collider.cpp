//==========================================================
// �T�v  :�S�R���C�_�[�̊��N���X
// Author:Itsuki Namito
// Copyright(c) Utsurugi.All right reserved.
//==========================================================
#include "collider.h"

namespace physics
{
	//**********************************************************
	// �}�N��
	//**********************************************************

		//**********************************************************
		// �萔
		//**********************************************************

		// �R���X�g���N�^
	Collider::Collider()
		:shape(PhysicsShape::Box)
		,is_trigger_(false)
		,friction_(0.6f)
		,bounciness_(0.0f)
	{

	}

	Collider::Collider(Collider &copy)
	{
		*this = copy;
	}

	void Collider::SetTransform(const Vector2 &pos, const float &ori)
	{
		body_->SetTransform(b2Vec2(pos.x, pos.y), ori);
	}

	void Collider::FixedUpdate()
	{
		transform_->position_ = Vector2(body_->GetPosition().x,body_->GetPosition().y);
		transform_->rotation_ = body_->GetAngle();
	}
}
