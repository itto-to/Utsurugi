//==========================================================
// 概要  :ワールド
// Author:Itsuki Namito
// Copyright(c) Utsurugi.All right reserved.
//==========================================================
#include "physics_world.h"
#include "../Element/contact_listener.h"

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
	const b2Vec2 DEFAULT_GRAVITY = b2Vec2(0.0f, -10.0f);

	// static
	PhysicsWorld *PhysicsWorld::instance_ = nullptr;

	// コンストラクタ
	PhysicsWorld::PhysicsWorld()
		:world_(b2World(DEFAULT_GRAVITY))
		, time_step_(1.0f / 60.0f)
		, velocity_iteration_(10)
		, position_iteration_(10)
#ifdef _DEBUG
		,debug_draw_(nullptr)
#endif
	{
		world_.SetAllowSleeping(true);
		world_.SetWarmStarting(true);
		world_.SetContinuousPhysics(true);
		world_.SetSubStepping(false);
	}

	// 初期化処理
	void PhysicsWorld::Init()
	{
		if (instance_ == nullptr)
		{
			instance_ = new PhysicsWorld();
#ifdef _DEBUG
			instance_->debug_draw_ = new DebugDraw();
#endif
		}
#ifdef _DEBUG
		instance_->debug_draw_->Init();
		instance_->world_.SetDebugDraw(instance_->debug_draw_);
		instance_->debug_draw_->SetFlags(b2Draw::e_shapeBit);
#endif
		ContactListener::Init();
	}

	// 終了処理
	void PhysicsWorld::Uninit()
	{
		ContactListener::Uninit();
#ifdef _DEBUG
		instance_->debug_draw_->Uninit();
#endif

		if (instance_ != nullptr)
		{
#ifdef _DEBUG
			if (instance_->debug_draw_ != nullptr)
			{
				delete instance_->debug_draw_;
				instance_->debug_draw_ = nullptr;
			}
#endif
			delete instance_;
			instance_ = nullptr;
		}
	}

	// 更新処理
	void PhysicsWorld::Step()
	{
		int check = instance_->colliders_.size();
		if (check != 0)
		{
			check = 0;
		}

		for (int i = 0;i < instance_->colliders_.size();++i)
		{
			instance_->colliders_[i]->SetTransform
				(
					instance_->colliders_[i]->transform_->position_ ,
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
			if (!instance_->colliders_[i]->is_trigger_)
			{
				instance_->colliders_[i]->transform_->position_ = 
					instance_->colliders_[i]->GetPosition();

				instance_->colliders_[i]->transform_->rotation_ =
					instance_->colliders_[i]->GetAngle();
			}
		}

	}

#ifdef _DEBUG

	void PhysicsWorld::Draw()
	{
		instance_->world_.DrawDebugData();
		instance_->debug_draw_->Draw();
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

	//==========================================================
	// 概要  :物理エンジンの制御下にあるJointを追加する
	// 引数  :Jointの定義
	//==========================================================
	b2Joint *PhysicsWorld::CreateJoint(Joint *joint, const b2JointDef *joint_def)
	{
		joint->index_ = instance_->joints_.size();
		instance_->joints_.push_back(joint);

		return instance_->world_.CreateJoint(joint_def);
	}

	void PhysicsWorld::DestroyBody(int index,b2Body *body)
	{
		instance_->world_.DestroyBody(body);

		for (int i = index + 1;i < instance_->colliders_.size();++i)
		{
			--instance_->colliders_[i]->index_;
		}

		instance_->colliders_.erase(instance_->colliders_.begin() + index);
	}

	void PhysicsWorld::DestroyJoint(int index, b2Joint *joint)
	{
		b2Joint *j_list = instance_->world_.GetJointList();

		while (j_list != nullptr)
		{
			if (joint == j_list)
			{
				instance_->world_.DestroyJoint(joint);
				break;
			}
			else
			{
				j_list = j_list->GetNext();
			}
		}

		for (int i = index + 1;i < instance_->joints_.size();++i)
		{
			--instance_->joints_[i]->index_;
		}

		instance_->joints_.erase(instance_->joints_.begin() + index);
	}

	void PhysicsWorld::ClearBody()
	{
		for (int i = 0;i < instance_->colliders_.size();++i)
		{
			instance_->world_.DestroyBody(instance_->colliders_[i]->body_);
		}

		instance_->colliders_.clear();
	}

	void PhysicsWorld::ClearJoint()
	{
		for (int i = 0;i < instance_->joints_.size();++i)
		{
			instance_->world_.DestroyJoint(instance_->joints_[i]->joint_);
		}

		instance_->joints_.clear();
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

	int PhysicsWorld::BodyCount()
	{
		return instance_->colliders_.size();
	}
}
