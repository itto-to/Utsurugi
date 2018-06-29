//==========================================================
// 概要  :ロープジョイント
// Author:Itsuki Namito
// Copyright(c) Utsurugi.All right reserved.
//==========================================================
#include "rope_joint.h"
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
	RopeJoint::RopeJoint(const RopeInitializer &ini)
	{
		type_ = JointType::kRope;

		collider_a_ = ini.collider_a_;
		collider_b_ = ini.collider_b_;

		b2RopeJointDef rjd;

		rjd.bodyA = ini.collider_a_->body_;
		rjd.bodyB = ini.collider_b_->body_;
		rjd.localAnchorA.Set(ini.local_anchor_a_.x, ini.local_anchor_a_.y);
		rjd.localAnchorB.Set(ini.local_anchor_b_.x, ini.local_anchor_b_.y);
		
		rjd.maxLength = ini.max_length_;
		
		rjd.collideConnected = ini.collide_connected_;

		rope_joint_ = (b2RopeJoint *)PhysicsWorld::CreateJoint(this,&rjd);
	}

	//==========================================================
	// 概要  :ロープの長さの最大値を設定します
	// 引数  :ロープの長さの最大値
	//==========================================================
	void RopeJoint::SetMaxLength(float length)
	{
		rope_joint_->SetMaxLength(length);
	}

	//==========================================================
	// 概要  :ロープの長さの最大値を取得
	// 戻り値:ロープの長さの最大値
	//==========================================================
	float RopeJoint::GetMaxLength()
	{
		return rope_joint_->GetMaxLength();
	}
}
