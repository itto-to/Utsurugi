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
		SetCollider(ini);
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

	void BoxCollider::SetCollider(const BoxInitializer &ini) {
		shape_ = PhysicsShape::kBox;

		b2BodyDef box_body_def;

		switch (ini.body_type_)
		{
		case kDynamicBody:
			box_body_def.type = b2_dynamicBody;
			break;
		case kKinematicBody:
			box_body_def.type = b2_kinematicBody;
			break;
		case kStaticBody:
			box_body_def.type = b2_staticBody;
			break;
		}

		box_body_def.position.Set(ini.pos_.x, ini.pos_.y);
		box_body_def.fixedRotation = ini.fixed_rotation_;

		body_ = PhysicsWorld::CreateBody(this, &box_body_def);
		body_->SetUserData(this);

		b2PolygonShape box;
		box.SetAsBox(ini.width_ / 2.0f, ini.height_ / 2.0f, b2Vec2(ini.offset_.x, ini.offset_.y), 0.0f);


		b2FixtureDef box_fixture_def;
		box_fixture_def.isSensor = ini.is_trigger_;
		box_fixture_def.shape = &box;

		if (ini.body_type_ == kStaticBody)
		{
			box_fixture_def.density = 0.0f;
		}
		else
		{
			box_fixture_def.density = ini.density_;
		}
		box_fixture_def.friction = ini.friction_;

		// フィルタ設定
		box_fixture_def.filter.categoryBits = ini.category_bits_;
		box_fixture_def.filter.maskBits = ini.mask_bits_;

		body_->CreateFixture(&box_fixture_def);

		size_ = Vector2(ini.width_, ini.height_);
	}

	//==========================================================
	// 概要  :
	// 引数  :
	//==========================================================
	void BoxCollider::ReSet(const BoxInitializer &ini)
	{
		PhysicsWorld::DestroyBody(index_, body_);
		SetCollider(ini);

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


	void BoxCollider::SetOffset(const Vector2 &offset)
	{
		offset_ = offset;

		b2PolygonShape *box = (b2PolygonShape *)body_->GetFixtureList()->GetShape();

		box->SetAsBox(size_.x, size_.y, b2Vec2(offset.x, offset.y), 0.0f);
	}
}
