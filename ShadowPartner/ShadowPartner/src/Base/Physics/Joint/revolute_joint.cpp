//==========================================================
// 概要  :ヒンジジョイント
// Author:Itsuki Namito
// Copyright(c) Utsurugi.All right reserved.
//==========================================================
#include "revolute_joint.h"
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
	RevoluteJoint::RevoluteJoint(const RevoluteInitializer &ini)
	{
		type_ = JointType::kRevolute;

		collider_a_ = ini.collider_a_;
		collider_b_ = ini.collider_b_;

		b2RevoluteJointDef rjd;

		rjd.Initialize(ini.collider_a_->body_, ini.collider_b_->body_, b2Vec2(ini.world_pos_.x,ini.world_pos_.y));
		rjd.localAnchorA = b2Vec2(ini.local_anchor_a_.x, ini.local_anchor_a_.y);
		rjd.localAnchorB = b2Vec2(ini.local_anchor_b_.x, ini.local_anchor_b_.y);
		rjd.motorSpeed = 1.0f * b2_pi;
		rjd.maxMotorTorque = 10000.0f;
		rjd.enableMotor = false;

		rjd.lowerAngle = ini.lower_angle_ * (b2_pi / 180.0f);
		rjd.upperAngle = ini.upper_angle_ * (b2_pi / 180.0f);
		
		rjd.enableLimit = ini.enable_limit_;

		rjd.collideConnected = ini.collide_connected_;

		revolute_joint_ = (b2RevoluteJoint *)PhysicsWorld::CreateJoint(this,&rjd);
	}


	void RevoluteJoint::SetLimitAngles(float lower, float upper)
	{
		revolute_joint_->SetLimits(lower, upper);
	}

	void RevoluteJoint::EnableLimit(bool flag)
	{
		revolute_joint_->EnableLimit(flag);
	}
}
