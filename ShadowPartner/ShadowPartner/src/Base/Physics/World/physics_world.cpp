//==========================================================
// 概要  :ワールド
// Author:Itsuki Namito
// Copyright(c) Utsurugi.All right reserved.
//==========================================================
#include "physics_world.h"

#ifdef _DEBUG
#include "../../Debug/debugger.h"
#endif

namespace physics
{
	//**********************************************************
	// マクロ
	//**********************************************************

	//**********************************************************
	// 定数
	//**********************************************************
	const b2Vec2 DEFAULT_GRAVITY = b2Vec2(0.0f, -980.0f);

	// static
	PhysicsWorld *PhysicsWorld::instance_ = nullptr;

	// コンストラクタ
	PhysicsWorld::PhysicsWorld()
		:world_(b2World(DEFAULT_GRAVITY))
		, time_step_(1.0f / 60.0f)
		, velocity_iteration_(6)
		, position_iteration_(2)
	{
		world_.SetAllowSleeping(true);
		world_.SetWarmStarting(true);
		world_.SetContinuousPhysics(true);
		world_.SetSubStepping(true);
	}

	// 初期化処理
	void PhysicsWorld::Init()
	{
		if (instance_ == nullptr)
			instance_ = new PhysicsWorld();

#ifdef _DEBUG
		instance_->debug_draw_.Init();
		instance_->world_.SetDebugDraw(&instance_->debug_draw_);
#endif
	}

	// 終了処理
	void PhysicsWorld::Uninit()
	{
#ifdef _DEBUG
		instance_->debug_draw_.Uninit();
#endif

		if (instance_ != nullptr)
		{
			delete instance_;
			instance_ = nullptr;
		}
	}

	// 更新処理
	void PhysicsWorld::Step()
	{
		for (int i = 0;i < instance_->colliders_.size();++i)
		{
			instance_->colliders_[i]->SetTransform
				(
					instance_->colliders_[i]->transform_->position_,
					instance_->colliders_[i]->transform_->rotation_
					);
		}

		instance_->world_.Step
			(
				instance_->time_step_,
				instance_->velocity_iteration_,
				instance_->position_iteration_
				);

		for (int i = 0;i < instance_->colliders_.size();++i)
		{
			instance_->colliders_[i]->transform_->position_ =
				instance_->colliders_[i]->GetPosition();

			instance_->colliders_[i]->transform_->rotation_ =
				instance_->colliders_[i]->GetAngle();
		}

	}

#ifdef _DEBUG
	void PhysicsWorld::Draw()
	{
		//instance_->world_.DrawDebugData();
		//instance_->debug_draw_.Draw();
	}

#endif

	//==========================================================
	// 概要  :物理エンジンの制御下にあるColliderを追加する
	// 引数  :Colliderの定義へのポインタ
	//==========================================================
	b2Body *PhysicsWorld::CreateBody(Collider *collider,const b2BodyDef *body_def)
	{
		collider->index_ = instance_->colliders_.size();
		instance_->colliders_.push_back(collider);

		return instance_->world_.CreateBody(body_def);
	}

	void PhysicsWorld::DestroyBody(b2Body *body)
	{
		instance_->world_.DestroyBody(body);
	}

	// Accessor・Mutator
	void PhysicsWorld::SetTimeStep(const float &value)
	{
		instance_->time_step_ = value;
	}

	float PhysicsWorld::GetTimeStep()
	{
		return instance_->time_step_;
	}

	void PhysicsWorld::SetVelocityIteration(const int &value)
	{
		instance_->velocity_iteration_ = value;
	}

	int PhysicsWorld::GetVelocityIteration()
	{
		return instance_->velocity_iteration_;
	}

	void PhysicsWorld::SetPositionIteration(const int &value)
	{
		instance_->position_iteration_ = value;
	}

	int PhysicsWorld::GetPositionIteration()
	{
		return instance_->position_iteration_;
	}
}
