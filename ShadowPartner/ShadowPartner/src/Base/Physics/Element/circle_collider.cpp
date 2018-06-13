//==========================================================
// 概要  :円形の当たり判定
// Author:Itsuki Namito
// Copyright(c) Utsurugi.All right reserved.
//==========================================================
#include "circle_collider.h"
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
	CircleCollider::CircleCollider(const CircleInitializer &ini)
	{
		shape_ = PhysicsShape::kCircle;

		b2BodyDef circle_body_def;
		if (ini.is_static_)
			circle_body_def.type = b2_staticBody;
		else
			circle_body_def.type = b2_dynamicBody;

		circle_body_def.position.Set(ini.pos_.x, ini.pos_.y);

		body_ = PhysicsWorld::CreateBody(this, &circle_body_def);
		body_->SetUserData(this);

		b2CircleShape circle;
		circle.m_p.Set(0.0f, 0.0f);
		circle.m_radius = ini.radius_;

		b2FixtureDef circle_fixture_def;
		circle_fixture_def.isSensor = ini.is_trigger_;
		circle_fixture_def.shape = &circle;
		if (ini.is_static_)
		{
			circle_fixture_def.density = 0.0f;
			circle_fixture_def.friction = 0.0f;
		}
		else
		{
			circle_fixture_def.density = ini.density_;
			circle_fixture_def.friction = ini.friction_;
		}
		body_->CreateFixture(&circle_fixture_def);

		radius_ = ini.radius_;
	}

	void CircleCollider::Start()
	{
	}

	//==========================================================
	// 概要  :CircleColliderの半径を記録したradius_を返します。
	// 戻り値:当たり判定の半径
	//==========================================================
	float CircleCollider::GetRadius()
	{
		return radius_;
	}
}
