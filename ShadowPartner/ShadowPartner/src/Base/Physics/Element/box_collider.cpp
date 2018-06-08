//==========================================================
// 概要  :矩形の当たり判定
// Author:Itsuki Namito
// Copyright(c) Utsurugi.All right reserved.
//==========================================================
#include "box_collider.h"
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
	BoxCollider::BoxCollider(const BoxInitializer &ini)
	{
		shape_ = PhysicsShape::kBox;

		b2BodyDef box_body_def;
		if (ini.is_static_)
			box_body_def.type = b2_staticBody;
		else
			box_body_def.type = b2_dynamicBody;

		box_body_def.position.Set(ini.pos_.x, ini.pos_.y);

		body_ = PhysicsWorld::CreateBody(this,&box_body_def);

		b2PolygonShape box;
		box.SetAsBox(ini.width_ / 2.0f, ini.height_ / 2.0f,b2Vec2(ini.offset_.x,ini.offset_.y),0.0f);

		if (ini.is_static_)
		{
			body_->CreateFixture(&box, 0.0f);
		}
		else
		{
			b2FixtureDef box_fixture_def;
			box_fixture_def.shape = &box;
			box_fixture_def.density = ini.density_;
			box_fixture_def.friction = ini.friction_;

			body_->CreateFixture(&box_fixture_def);
		}

		size_ = Vector2(ini.width_, ini.height_);
	}

	void BoxCollider::Start()
	{

	}

	//==========================================================
	// 概要  :BoxColliderの縦横の大きさを記録したsize_を返します。
	// 戻り値:縦横の大きさ
	//==========================================================
	Vector2 BoxCollider::GetSize()
	{
		return size_;
	}

	//==========================================================
	// 概要  :
	// 引数  :
	//==========================================================
	void BoxCollider::ReSet(const BoxInitializer &ini)
	{
		//body_->

		//	b2PolygonShape box;
		//box.SetAsBox(ini.width_ / 2.0f, ini.height_ / 2.0f);

		//if (ini.is_static_)
		//{
		//	body_->CreateFixture(&box, 0.0f);
		//}
		//else
		//{
		//	b2FixtureDef box_fixture_def;
		//	box_fixture_def.shape = &box;
		//	box_fixture_def.density = ini.density_;
		//	box_fixture_def.friction = ini.friction_;

		//	body_->CreateFixture(&box_fixture_def);
		//}

	}
}
