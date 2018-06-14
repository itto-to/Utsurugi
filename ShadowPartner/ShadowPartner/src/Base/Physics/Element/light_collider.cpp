//==========================================================
// 概要  :ライトの当たり判定
// Author:Ittoto
// Copyright(c) Utsurugi.All right reserved.
//==========================================================
#include "light_collider.h"
#include "../../Element/component.h"
#include "../../Light/light.h"
#include "../World/physics_world.h"

namespace physics
{
	LightCollider::LightCollider() : 
		num_triangle_(0),
		bodies_(nullptr),
		body_idx_(0),
		light_(nullptr)
	{
		shape_ = PhysicsShape::kPolygon;


	}

	LightCollider::~LightCollider()
	{
		DeleteLightCollider();
	}

	void LightCollider::Start()
	{
		light_ = this->game_object_->GetComponent<Light>();
	}

	void LightCollider::Update()
	{
		// 前回の当たり判定を削除
		DeleteLightCollider();

		// ライトの頂点から当たり判定を生成
		std::vector<math::Vector2> light_vertices;
		light_->GetVertices(light_vertices);
		Vector2 center = light_vertices[0];
		num_triangle_ = light_vertices.size() - 2;
		bodies_ = new b2Body*[num_triangle_];

		b2BodyDef light_body_def;
		light_body_def.type = b2_dynamicBody;
		Vector2 light_pos = light_->transform_->position_;
		light_body_def.position.Set(light_pos.x, light_pos.y);

		b2FixtureDef light_fixture_def;
		light_fixture_def.isSensor = false;

		b2Vec2 tri[3];
		tri[0] = b2Vec2(center.x, center.y);
		for (int i = 0; i < num_triangle_; i++)
		{
			bodies_[i] = PhysicsWorld::CreateBody(this, &light_body_def);

			tri[1] = b2Vec2(light_vertices[i + 1].x, light_vertices[i + 1].y);
			tri[2] = b2Vec2(light_vertices[i + 2].x, light_vertices[i + 2].y);
			b2PolygonShape light_poly;
			light_poly.Set(tri, 3);
			light_fixture_def.shape = &light_poly;
			bodies_[i]->CreateFixture(&light_fixture_def);
		}
	}

	void LightCollider::SetTransform(const Vector2 & pos, const float & ori)
	{
		bodies_[body_idx_]->SetTransform(b2Vec2(pos.x, pos.y), ori);
		body_idx_++;
		if (body_idx_ == num_triangle_)
		{
			body_idx_ = 0;
		}
	}

	Vector2 LightCollider::GetPosition()
	{
		b2Vec2 pos = bodies_[body_idx_]->GetPosition();
		return Vector2(pos.x, pos.y);
	}

	float LightCollider::GetAngle()
	{
		float angle =  bodies_[body_idx_]->GetAngle();
		body_idx_++;
		if (body_idx_ == num_triangle_)
		{
			body_idx_ = 0;
		}

		return angle;
	}

	void LightCollider::DeleteLightCollider()
	{
		for (int i = 0; i < num_triangle_; i++)
		{
			PhysicsWorld::DestroyBody(index_, bodies_[i]);
			index_--;
		}
		delete[] bodies_;
		bodies_ = nullptr;
	}
}