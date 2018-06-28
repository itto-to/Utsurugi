//==========================================================
// �T�v  :�W���C���g�̊��N���X
// Author:Itsuki Namito
// Copyright(c) Utsurugi.All right reserved.
//==========================================================

#ifndef _BASE_PHYSICS_JOINT_JOINT_H_
#define _BASE_PHYSICS_JOINT_JOINT_H_

//**********************************************************
// �C���N���[�h�t�@�C��
//**********************************************************
#include "../Element/collider.h"

#include "../../Element/component.h"

using namespace shadowpartner;

namespace physics
{
	enum JointType
	{
		kRevolute,	// �q���W�W���C���g
	};

	//==========================================================
	// �T�v  :�S�R���C�_�[�̊��N���X
	//==========================================================
	class Joint : public Component
	{
	public:
		Joint();
		virtual ~Joint();

		// variables
		JointType type_;	
		int index_;			// ���[���h�ɕR�Â���ꂽ�C���f�b�N�X
		Collider *collider_a_;
		Collider *collider_b_;
		// methods
		//virtual void SetActive(bool is_active) override;

		friend class PhysicsWorld;

	protected:
		// variables
		b2Joint *joint_;

		// methods
		void Start() {};

	private:
		// variables
		// methods

	};
}

#endif