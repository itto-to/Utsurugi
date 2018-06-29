//==========================================================
// 概要  :ライトの当たり判定
// Author:Ittoto
// Copyright(c) Utsurugi.All right reserved.
//==========================================================
#include "light_collider.h"
#include "../../Element/component.h"
#include "../../Light/light.h"
#include "../World/physics_world.h"
#include "../../2D/texture.h"

namespace physics
{
	LightCollider::LightCollider() : 
		num_triangle_(0),
		body_idx_(0),
		light_(nullptr)
	{
		shape_ = PhysicsShape::kPolygon;
	}

	LightCollider::~LightCollider()
	{
		DestroyLightCollider();
	}

	void LightCollider::Start()
	{
		light_ = this->game_object_->GetComponent<Light>();
	}

	void LightCollider::Update()
	{
		// 前回の当たり判定を削除
		DestroyLightCollider();

		// ライトの頂点から当たり判定を生成
		std::vector<math::Vector2> light_vertices;
		light_->GetVertices(light_vertices);
		b2Vec2 center = b2Vec2(light_vertices[0].x, light_vertices[0].y) / PIXEL_PER_UNIT;

		b2BodyDef light_body_def;
		light_body_def.type         = b2_dynamicBody;
		light_body_def.gravityScale = 0.0f;
		light_body_def.position     = center;

		// ボディを作成
		body_ = PhysicsWorld::CreateBody(this, &light_body_def);

		// フィクスチャを作成
		b2FixtureDef light_fixture_def;
		light_fixture_def.isSensor = true;

		b2Vec2 tri[3];
		tri[0] = b2Vec2(0, 0);	// 中心座標

		num_triangle_  = light_vertices.size() - 2;	// 三角形の数を取得
		for (int i = 0; i < num_triangle_; i++)
		{
			tri[1] = b2Vec2(light_vertices[i + 1].x, light_vertices[i + 1].y) / PIXEL_PER_UNIT - center;
			tri[2] = b2Vec2(light_vertices[i + 2].x, light_vertices[i + 2].y) / PIXEL_PER_UNIT - center;
		
			if (b2Cross(tri[1], tri[2]) == 0.0f)
			{
				b2PolygonShape light_poly;
				light_poly.Set(tri, 3);
				light_fixture_def.shape = &light_poly;
				body_->CreateFixture(&light_fixture_def);
			}
		}
	}

	//void LightCollider::SetTransform(const Vector2 & pos, const float & ori)
	//{
		//bodies_[body_idx_]->SetTransform(b2Vec2(pos.x, pos.y), ori);
		//body_idx_++;
		//if (body_idx_ == num_triangle_)
		//{
		//	body_idx_ = 0;
		//}
	//}

	//Vector2 LightCollider::GetPosition()
	//{
		//b2Vec2 pos = bodies_[body_idx_]->GetPosition();
		//return Vector2(pos.x, pos.y);
	//}

	//float LightCollider::GetAngle()
	//{
		//float angle =  bodies_[body_idx_]->GetAngle();
		//body_idx_++;
		//if (body_idx_ == num_triangle_)
		//{
		//	body_idx_ = 0;
		//}

		//return angle;
	//}

	void LightCollider::DestroyLightCollider()
	{
		if (body_ != nullptr)
			PhysicsWorld::DestroyBody(index_, body_);
	}
}