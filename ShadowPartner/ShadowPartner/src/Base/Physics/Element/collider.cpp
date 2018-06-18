//==========================================================
// 概要  :全コライダーの基底クラス
// Author:Itsuki Namito
// Copyright(c) Utsurugi.All right reserved.
//==========================================================
#include "collider.h"
#include "../World/physics_world.h"

namespace physics
{
	//**********************************************************
	// マクロ
	//**********************************************************

		//**********************************************************
		// 定数
		//**********************************************************

		// コンストラクタ
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
		// GameObjectにアタッチされていなければ非活性
		if (game_object_ == nullptr || !is_active)
		{
			is_active_ = false;
			body_->SetActive(false);
		}
		else if (!is_active_ && is_active)
		{
			is_active_ = true;
			body_->SetActive(true);
			Start();
		}
	}

	// 衝突判定高速化のためのSleepを許すか
	void Collider::SetSleepingAllowed(bool flag)
	{
		body_->SetSleepingAllowed(flag);
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

	Vector2 Collider::GetPosition()
	{
		b2Vec2 pos = body_->GetPosition();
		return Vector2(pos.x, pos.y);
	}

	float Collider::GetAngle()
	{
		return body_->GetAngle();
	}

	void Collider::AddForce(const Vector2 &force)
	{
		body_->ApplyForceToCenter(b2Vec2(force.x,force.y),true);
	}

	void Collider::SetVelocity(const Vector2 &velo)
	{
		body_->SetLinearVelocity(b2Vec2(velo.x, velo.y));
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
