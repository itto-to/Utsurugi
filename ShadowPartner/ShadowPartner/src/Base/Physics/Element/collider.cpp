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
}
