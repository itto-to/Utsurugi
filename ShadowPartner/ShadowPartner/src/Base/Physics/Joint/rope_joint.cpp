//==========================================================
// �T�v  :���[�v�W���C���g
// Author:Itsuki Namito
// Copyright(c) Utsurugi.All right reserved.
//==========================================================
#include "rope_joint.h"
#include "../World/physics_world.h"

namespace physics
{
	//**********************************************************
	// �}�N��
	//**********************************************************

	//**********************************************************
	// �萔
	//**********************************************************

	// �R���X�g���N�^
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
	// �T�v  :���[�v�̒����̍ő�l��ݒ肵�܂�
	// ����  :���[�v�̒����̍ő�l
	//==========================================================
	void RopeJoint::SetMaxLength(float length)
	{
		rope_joint_->SetMaxLength(length);
	}

	//==========================================================
	// �T�v  :���[�v�̒����̍ő�l���擾
	// �߂�l:���[�v�̒����̍ő�l
	//==========================================================
	float RopeJoint::GetMaxLength()
	{
		return rope_joint_->GetMaxLength();
	}
}
