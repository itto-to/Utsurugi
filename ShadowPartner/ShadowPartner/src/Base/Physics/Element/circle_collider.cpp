//==========================================================
// �T�v  :�~�`�̓����蔻��
// Author:Itsuki Namito
// Copyright(c) Utsurugi.All right reserved.
//==========================================================
#include "circle_collider.h"
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

		b2CircleShape circle;
		circle.m_p.Set(0.0f, 0.0f);
		circle.m_radius = ini.radius_;

		if (ini.is_static_)
		{
			body_->CreateFixture(&circle, 0.0f);
		}
		else
		{
			b2FixtureDef circle_fixture_def;
			circle_fixture_def.shape = &circle;
			circle_fixture_def.density = ini.density_;
			circle_fixture_def.friction = ini.friction_;

			body_->CreateFixture(&circle_fixture_def);
		}
	}

	void CircleCollider::Start()
	{
	}
}