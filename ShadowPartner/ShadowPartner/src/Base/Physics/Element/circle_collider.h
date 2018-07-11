//==========================================================
// �T�v  :�~�`�̓����蔻��
// Author:Itsuki Namito
// Copyright(c) Utsurugi.All right reserved.
//==========================================================

#ifndef _BASE_PHYSICS_ELEMENT_CIRCLE_COLLIDER_H_
#define _BASE_PHYSICS_ELEMENT_CIRCLE_COLLIDER_H_

//**********************************************************
// �C���N���[�h�t�@�C��
//**********************************************************
#include "collider.h"

using namespace shadowpartner;

namespace physics
{
	//
	struct CircleInitializer
	{
		Vector2 pos_;		// �ʒu
		Vector2 offset_;
		float radius_;
		BodyType body_type_;// �{�f�B�[�̃^�C�v
		bool is_trigger_;	// �g���K�[���ǂ���
		float density_;		// ���x
		float friction_;	// ���C�W��
		float bounciness_;	// �����W��
		unsigned short category_bits_;	// �����̃t�B���^�[�r�b�g��
		unsigned short mask_bits_;		// �����鑊��̃t�B���^�[�r�b�g��
		float gravity_scale_;

		CircleInitializer()
			:pos_(Vector2::zero())
			, offset_(Vector2::zero())
			, radius_(1.0f)
			, body_type_(kDynamicBody)
			, is_trigger_(false)
			, density_(1.0f)
			, friction_(0.6f)
			, bounciness_(0.0f)
			, category_bits_(CollisionFilter::kDefault)
			, mask_bits_(0xffff)
			, gravity_scale_(1.0f)
		{
		}
	};

	//==========================================================
	// �T�v  :�S�R���C�_�[�̊��N���X
	//==========================================================
	class CircleCollider : public Collider
	{
	public:
		CircleCollider(const CircleInitializer &initializer);
		virtual ~CircleCollider() {};

		// ariables
		// methods

		float GetRadius();

	protected:

		// methods
		void Start();

		virtual void OnCollisionEnter(Collider *hit) {};
		virtual void OnCollisionStay(Collider *hit) {};
		virtual void OnCollisionExit(Collider *hit) {};
		virtual void OnTriggerEnter(Collider *hit) {};
		virtual void OnTriggerStay(Collider *hit) {};
		virtual void OnTriggerExit(Collider *hit) {};

	private:
		// variables
		float radius_;

		// methods

	};
}

#endif