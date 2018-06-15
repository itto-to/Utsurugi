//==========================================================
// 概要  :凸ポリゴンの当たり判定
// Author:Itsuki Namito
// Copyright(c) Utsurugi.All right reserved.
//==========================================================
#include "polygon_collider.h"
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
	PolygonCollider::PolygonCollider(const PolygonInitializer &ini)
		//:shape(PhysicsShape::Box)
		//,is_trigger_(false)
		//,friction_(0.6f)
		//,bounciness_(0.0f)
	{
		shape_ = PhysicsShape::kPolygon;

		b2BodyDef poly_body_def;
		switch (ini.body_type_)
		{
		case kDynamicBody:
			poly_body_def.type = b2_dynamicBody;
			break;
		case kKinematicBody:
			poly_body_def.type = b2_kinematicBody;
			break;
		case kStaticBody:
			poly_body_def.type = b2_staticBody;
			break;
		}

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

		b2FixtureDef box_fixture_def;
		box_fixture_def.shape = &poly;
		box_fixture_def.friction = ini.friction_;

		if (ini.body_type_ == kStaticBody)
		{
			box_fixture_def.density = ini.density_;
		}
		else
		{
			box_fixture_def.density = 0.0f;
		}
		body_->CreateFixture(&box_fixture_def);

		delete[] b2_vertices;
		b2_vertices = nullptr;
	}
}
