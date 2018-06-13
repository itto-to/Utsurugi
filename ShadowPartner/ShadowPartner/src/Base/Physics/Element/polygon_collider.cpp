//==========================================================
// �T�v  :�|���S���̓����蔻��
// Author:Itsuki Namito
// Copyright(c) Utsurugi.All right reserved.
//==========================================================
#include "polygon_collider.h"
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
	PolygonCollider::PolygonCollider(const PolygonInitializer &ini)
		//:shape(PhysicsShape::Box)
		//,is_trigger_(false)
		//,friction_(0.6f)
		//,bounciness_(0.0f)
	{
		shape_ = PhysicsShape::kPolygon;

		b2BodyDef poly_body_def;
		if (ini.is_static_)
			poly_body_def.type = b2_staticBody;
		else
			poly_body_def.type = b2_dynamicBody;

		poly_body_def.position.Set(ini.pos_.x, ini.pos_.y);

		body_ = PhysicsWorld::CreateBody(this, &poly_body_def);
		body_->SetUserData(this);

		b2PolygonShape poly;

		int poly_count = ini.vertices_.size();
		b2Vec2 *b2_vertices = new b2Vec2[poly_count];

		int i = 0;
		for (Vector2 v : ini.vertices_)
		{
			b2_vertices[i].Set(v.x, v.y);
			i++;
		}
		poly.Set(b2_vertices, poly_count);

		if (ini.is_static_)
		{
			body_->CreateFixture(&poly, 0.0f);
		}
		else
		{
			b2FixtureDef box_fixture_def;
			box_fixture_def.shape = &poly;
			box_fixture_def.density = ini.density_;
			box_fixture_def.friction = ini.friction_;

			body_->CreateFixture(&box_fixture_def);
		}

		delete[] b2_vertices;
		b2_vertices = nullptr;
	}
}
