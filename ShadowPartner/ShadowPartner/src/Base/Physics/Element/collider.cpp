//==========================================================
// �T�v  :�S�R���C�_�[�̊��N���X
// Author:Itsuki Namito
// Copyright(c) Utsurugi.All right reserved.
//==========================================================
#include "collider.h"
#include "../World/physics_world.h"

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
		:shape_(PhysicsShape::kBox)
		,is_trigger_(false)
		,friction_(0.6f)
		,bounciness_(0.0f)
		,index_(0)
		,offset_(Vector2::zero())
	{

	}

	Collider::Collider(Collider &copy)
	{
		*this = copy;
	}

	Collider::~Collider()
	{
		PhysicsWorld::DestroyBody(index_,body_);
	}

	void Collider::SetActive(bool is_active)
	{
		// GameObject�ɃA�^�b�`����Ă��Ȃ���Δ񊈐�
		if (game_object_ == nullptr || !is_active)
		{
			is_active_ = false;
			if (body_ != nullptr)
			{
				body_->SetActive(false);
			}
		}
		else if (!is_active_ && is_active)
		{
			is_active_ = true;
			if (body_ != nullptr)
			{
				body_->SetActive(true);
			}
			Start();
		}
	}

	// �Փ˔��荂�����̂��߂�Sleep��������
	void Collider::SetSleepingAllowed(bool flag)
	{
		body_->SetSleepingAllowed(flag);
	}

	void Collider::SetTransform(const Vector2 &pos, const float &ori)
	{
		body_->SetTransform(b2Vec2(pos.x, pos.y), -D3DXToRadian(ori));
	}

	void Collider::FixedUpdate()
	{
		transform_->position_ = Vector2(body_->GetPosition().x,body_->GetPosition().y);
		transform_->rotation_ = body_->GetAngle();
	}

	Vector2 Collider::GetPosition()
	{
		b2Vec2 pos = body_->GetPosition();
		return Vector2(pos.x, pos.y);
	}

	float Collider::GetAngle()
	{
		return -D3DXToDegree(body_->GetAngle());
	}

	void Collider::AddForce(const Vector2 &force)
	{
		body_->ApplyForceToCenter(b2Vec2(force.x,force.y),true);
	}

	void Collider::AddForceToPoint(const Vector2 &force, const Vector2 &point)
	{
		body_->ApplyForce(b2Vec2(force.x, force.y), b2Vec2(point.x, point.y), true);
	}

	void Collider::AddTorque(const float torque)
	{
		body_->ApplyTorque(torque, true);
	}

	void Collider::Move(const Vector2 &move)
	{
		game_object_->transform_->position_ += move;
		SetTransform(transform_->position_, transform_->rotation_);
	}

	Vector2 Collider::Velocity() const
	{
		b2Vec2 v = body_->GetLinearVelocity();
		return Vector2(v.x, v.y);
	}

	void Collider::SetVelocity(const Vector2 &velo)
	{
		body_->SetLinearVelocity(b2Vec2(velo.x, velo.y));
	}

	float Collider::VelocityX() const
	{
		return body_->GetLinearVelocity().x;
	}

	void Collider::SetVelocityX(float x)
	{
		body_->SetLinearVelocity(b2Vec2(x, body_->GetLinearVelocity().y));
	}

	float Collider::VelocityY() const
	{
		return body_->GetLinearVelocity().y;
	}

	void Collider::SetVelocityY(float y)
	{
		body_->SetLinearVelocity(b2Vec2(body_->GetLinearVelocity().x, y));
	}

	float Collider::GravityScale() const
	{
		return body_->GetGravityScale();
	}

	void Collider::SetGravityScale(float scale)
	{
		body_->SetGravityScale(scale);
	}

	void Collider::Stop()
	{
		body_->SetLinearVelocity(b2Vec2_zero);
	}

	void Collider::SetAwake(bool flag)
	{
		body_->SetAwake(flag);
	}
}
