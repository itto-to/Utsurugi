//==========================================================
// �T�v  :�q���W�W���C���g
// Author:Itsuki Namito
// Copyright(c) Utsurugi.All right reserved.
//==========================================================

#ifndef _BASE_PHYSICS_JOINT_REVOLUTE_JOINT_H_
#define _BASE_PHYSICS_JOINT_REVOLUTE_JOINT_H_

//**********************************************************
// �C���N���[�h�t�@�C��
//**********************************************************
#include "../Element/collider.h"
#include "joint.h"

using namespace shadowpartner;

namespace physics
{
	struct RevoluteInitializer
	{
		Collider *collider_a_;	// �W���C���g����I�u�W�F�N�g���
		Vector2 local_anchor_a_;
		Collider *collider_b_;	// �W���C���g����I�u�W�F�N�g���
		Vector2 local_anchor_b_;

		Vector2 world_pos_;		// �W���C���g�̃��[���h���W

		bool enable_limit_;		// ��]�𐧌�����
		float lower_angle_;		// ��]�̍ŏ��l(�x��)
		float upper_angle_;		// ��]�̍ő�l(�x��)

		bool collide_connected_;	// �W���C���g���ꂽ�ғ��m�ŏՓ˂��邩

		RevoluteInitializer()
			:collider_a_(nullptr)
			,local_anchor_a_(Vector2::zero())
			,collider_b_(nullptr)
			,local_anchor_b_(Vector2::zero())
			,world_pos_(Vector2::zero())
			,enable_limit_(false)
			,lower_angle_(0.0f)
			,upper_angle_(0.0f)
		{
		}
	};

	//==========================================================
	// �T�v  :�S�R���C�_�[�̊��N���X
	//==========================================================
	class RevoluteJoint : public Joint
	{
	public:
		RevoluteJoint(const RevoluteInitializer &initializer);
		virtual ~RevoluteJoint() {};

		// variables
		// methods
		
		void SetLimitAngles(float lower, float upper);
		void EnableLimit(bool flag);

	protected:

		// methods

	private:
		// variables
		b2RevoluteJoint *revolute_joint_;
		// methods

	};
}

#endif