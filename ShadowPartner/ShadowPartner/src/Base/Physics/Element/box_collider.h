//==========================================================
// �T�v  :��`�̓����蔻��
// Author:Itsuki Namito
// Copyright(c) Utsurugi.All right reserved.
//==========================================================

#ifndef _BASE_PHYSICS_ELEMENT_BOX_COLLIDER_H_
#define _BASE_PHYSICS_ELEMENT_BOX_COLLIDER_H_

//**********************************************************
// �C���N���[�h�t�@�C��
//**********************************************************
#include "collider.h"

using namespace shadowpartner;

namespace physics
{

	struct BoxInitializer
	{
		Vector2 pos_;			// �ʒu
		Vector2 offset_;
		float width_;			// ����
		float height_;			// �c��
		BodyType body_type_;	// �{�f�B�[�̃^�C�v
		bool is_trigger_;		// �g���K�[���ǂ���
		bool fixed_rotation_;	// true�ŉ�]�������Ȃ�
		float density_;			// ���x
		float friction_;		// ���C�W��
		float bounciness_;		// �����W��

		BoxInitializer()
			:pos_(Vector2::zero())
			, offset_(Vector2::zero())
			, width_(1.0f)
			, height_(1.0f)
			, body_type_(kDynamicBody)
			, is_trigger_(false)
			, fixed_rotation_(true)
			, density_(1.0f)
			, friction_(0.6f)
			, bounciness_(0.0f)
		{
		}
	};

	//==========================================================
	// �T�v  :�S�R���C�_�[�̊��N���X
	//==========================================================
	class BoxCollider : public Collider
	{
	public:
		BoxCollider(const BoxInitializer &initializer);
		virtual ~BoxCollider() {};

		// ariables
		// methods
		Vector2 GetSize();

		void ReSet(const BoxInitializer &initializer);

		void SetOffset(const Vector2 &offset);

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
		Vector2 size_;

		// methods

	};
}

#endif