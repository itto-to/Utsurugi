//==========================================================
// 概要  :物理関係の関数
// Author:Itsuki Namito
// Copyright(c) Utsurugi.All right reserved.
//==========================================================
#include "physics_func.h"

#include "../World/physics_world.h"

#ifdef _DEBUG
#include "../../Debug/debugger.h"
#endif

namespace physics
{
	class RayCastClosestCallback : public b2RayCastCallback
	{
	public:
		RayCastClosestCallback()
			:hit_(false)
		{
		}

		float ReportFixture(b2Fixture *fixture, const b2Vec2 &point, const b2Vec2 &normal, float fraction)
		{
			// 現在のfractionを返す
			hit_ = true;
			body_ = fixture->GetBody();
			point_ = Vector2(point.x, point.y);
			normal_ = Vector2(normal.x, normal.y);

			return fraction;
		}

		bool hit_;
		b2Body *body_;
		Vector2 point_;
		Vector2 normal_;
	};

	class RayCastAnyCallback : public b2RayCastCallback
	{
	public:
		RayCastAnyCallback()
			:hit_(false)
		{
		}

		float ReportFixture(b2Fixture *fixture, const b2Vec2 &point, const b2Vec2 &normal, float fraction)
		{
			B2_NOT_USED(fraction);
			// 現在のfractionを返す
			hit_ = true;
			body_ = fixture->GetBody();
			point_ = Vector2(point.x, point.y);
			normal_ = Vector2(normal.x, normal.y);

			return 0.0f;
		}

		bool hit_;
		b2Body *body_;
		Vector2 point_;
		Vector2 normal_;
	};

	class RayCastMultipleCallback : public b2RayCastCallback
	{
	public:
		enum
		{
			kMaxCount = 3
		};

		RayCastMultipleCallback()
			:count_(0)
		{
		}

		float ReportFixture(b2Fixture *fixture, const b2Vec2 &point, const b2Vec2 &normal, float fraction)
		{
			B2_NOT_USED(fraction);
			// 現在のfractionを返す

			b2Assert(count_ < kMaxCount);

			bodies_[count_] = fixture->GetBody();
			points_[count_] = Vector2(point.x, point.y);
			normals_[count_] = Vector2(normal.x, normal.y);
			++count_;

			if (count_ == kMaxCount)
			{
				// バッファが上限に達したら終了する
				return 0.0f;
			}

			// バッファが余っているなら続ける
			return 1.0f;
		}

		b2Body *bodies_[kMaxCount];
		Vector2 points_[kMaxCount];
		Vector2 normals_[kMaxCount];
		int count_;
	};

	//**********************************************************
	// マクロ
	//**********************************************************

	//**********************************************************
	// 定数
	//**********************************************************

	//==========================================================
	// 概要  :光線を飛ばして最初にヒットしたColliderのポインタを返します。
	// 引数  :
	//	start     :光線の発射位置
	//	direction :光線の方向
	//	distance  :光線の長さ
	//	layer_mask:判定をするオブジェクトを決めるためのレイヤー
	//==========================================================
	RaycastHit PhysicsFunc::Raycast(Vector2 start, Vector2 direction,
		float distance, int layer_mask)
	{
		RaycastHit hit_info;

		direction.Normalize();

		b2Vec2 point1 = b2Vec2(start.x, start.y);
		b2Vec2 point2 = point1 + b2Vec2(direction.x, direction.y) * distance;

		RayCastClosestCallback callback;
		PhysicsWorld::instance_->world_.RayCast(&callback, point1, point2);

		if (callback.hit_)
		{
			hit_info.hit_point = callback.point_;

			for (int i = 0;i < PhysicsWorld::instance_->colliders_.size();++i)
			{
				if (PhysicsWorld::instance_->colliders_[i]->body_ == callback.body_)
				{
					hit_info.collider = PhysicsWorld::instance_->colliders_[i];
					break;
				}
			}
		}
		else
		{
			hit_info.collider = nullptr;
		}

		return hit_info;

		//RayCastMultipleCallback callback;
		//PhysicsWorld::instance_->world_.RayCast(&callback, point1, point2);

		//for (int i = 0;(i < callback.count_);++i)
		//{
		//	for (int j = 0;j < PhysicsWorld::instance_->colliders_.size();++j)
		//	{
		//		if (PhysicsWorld::instance_->colliders_[j]->body_ == callback.bodies_[i])
		//		{
		//			Collider *check_collidder = PhysicsWorld::instance_->colliders_[j];

		//			if ((1 << check_collidder->game_object_->layer_) & layer_mask)
		//			{
		//				hit_info.collider = PhysicsWorld::instance_->colliders_[j];
		//				hit_info.hit_point = callback.points_[i];
		//			}
		//			break;
		//		}
		//	}
		//}

		//return hit_info;

	}

	//==========================================================
	// 概要  :ある点にColliderがあるか調べ、あればそのポインタを返します。
	// 引数  :
	//	point     :コライダーがあるかどうか判定する点
	//	layer_mask:判定をするオブジェクトを決めるためのレイヤー
	//==========================================================
	Collider *PhysicsFunc::OverLapPoint(Vector2 point, int layer_mask)
	{
		RaycastHit hit_info;

		b2Vec2 point1 = b2Vec2(point.x, point.y);
		b2Vec2 point2 = b2Vec2(point.x + FLT_MIN, point.y);

		RayCastMultipleCallback callback;
		PhysicsWorld::instance_->world_.RayCast(&callback, point1, point2);

		for (int i = 0;i < callback.count_;++i)
		{
			for (int j = 0;j < PhysicsWorld::instance_->colliders_.size();++i)
			{
				if (PhysicsWorld::instance_->colliders_[i]->body_ == callback.bodies_[i])
				{
					Collider *check_collidder = PhysicsWorld::instance_->colliders_[i];

					if ((1 << check_collidder->game_object_->layer_) & layer_mask)
						return PhysicsWorld::instance_->colliders_[i];
				}
			}
		}

		return nullptr;
	}

}
