//==========================================================
// �T�v  :���[�v�W���C���g
// Author:Itsuki Namito
// Copyright(c) Utsurugi.All right reserved.
//==========================================================

#ifndef _BASE_PHYSICS_JOINT_ROPE_JOINT_H_
#define _BASE_PHYSICS_JOINT_ROPE_JOINT_H_

//**********************************************************
// �C���N���[�h�t�@�C��
//**********************************************************
#include "../Element/collider.h"
#include "joint.h"

using namespace shadowpartner;

namespace physics
{
	struct RopeInitializer
	{
		Collider *collider_a_;		// �W���C���g����I�u�W�F�N�g���
		Vector2 local_anchor_a_;
		Collider *collider_b_;		// �W���C���g����I�u�W�F�N�g���
		Vector2 local_anchor_b_;

		Vector2 world_pos_;			// �W���C���g�̃��[���h���W

		float max_length_;			// ���[�v�̒����̍ő�l

		bool collide_connected_;	// �W���C���g���ꂽ�ғ��m�ŏՓ˂��邩

		RopeInitializer()
			:collider_a_(nullptr)
			,local_anchor_a_(Vector2::zero())
			,collider_b_(nullptr)
			,local_anchor_b_(Vector2::zero())
			,world_pos_(Vector2::zero())
			,max_length_(10.0f)
		{
		}
	};

	//==========================================================
	// �T�v  :�S�R���C�_�[�̊��N���X
	//==========================================================
	class RopeJoint : public Joint
	{
	public:
		RopeJoint(const RopeInitializer &initializer);
		virtual ~RopeJoint() {};

		// variables
		// methods
		void SetMaxLength(float length);
		float GetMaxLength();

	protected:

		// methods

	private:
		// variables
		b2RopeJoint *rope_joint_;

		// methods

	};
}

#endif