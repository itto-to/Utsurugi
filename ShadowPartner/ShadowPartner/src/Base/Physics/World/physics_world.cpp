//==========================================================
// �T�v  :���[���h
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
	// �}�N��
	//**********************************************************

	//**********************************************************
	// �萔
	//**********************************************************
	const b2Vec2 DEFAULT_GRAVITY = b2Vec2(0.0f, -10.0f);

	// static
	PhysicsWorld *PhysicsWorld::instance_ = nullptr;

	// �R���X�g���N�^
	PhysicsWorld::PhysicsWorld()
		:world_(b2World(DEFAULT_GRAVITY))
		, time_step_(0.016f)
		, velocity_iteration_(10)
		, position_iteration_(10)
	{

	}

	// ����������
	void PhysicsWorld::Init()
	{
		if (instance_ == nullptr)
			instance_ = new PhysicsWorld();
	}

	// �I������
	void PhysicsWorld::Uninit()
	{
		if (instance_ != nullptr)
		{
			delete instance_;
			instance_ = nullptr;
		}
	}

	// �X�V����
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
	}

	//==========================================================
	// �T�v  :�����G���W���̐��䉺�ɂ���Collider��ǉ�����
	// ����  :Collider�̒�`�ւ̃|�C���^
	//==========================================================
	b2Body *PhysicsWorld::CreateBody(const b2BodyDef *body_def)
	{
		return instance_->world_.CreateBody(body_def);
	}

	// Accessor�EMutator
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
