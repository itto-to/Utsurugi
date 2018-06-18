//==========================================================
// �T�v  :�ʃ|���S���̓����蔻��
// Author:Itsuki Namito
// Copyright(c) Utsurugi.All right reserved.
//==========================================================

#ifndef _BASE_PHYSICS_ELEMENT_POLYGONCOLLIDER_H_
#define _BASE_PHYSICS_ELEMENT_POLYGONCOLLIDER_H_

//**********************************************************
// �C���N���[�h�t�@�C��
//**********************************************************
//#include <Box2D\Box2D.h>
//#include "../../Element/component.h"
//#include <windows.h>
//#include <typeinfo>
//
//#ifdef _DEBUG
//#pragma comment (lib,"liquidfun_debug.lib")
//#else
//#pragma comment (lib, "liquidfun_release.lib")
//#endif
#include "collider.h"
#include <vector>

using namespace shadowpartner;

namespace physics
{
	struct PolygonInitializer
	{
		Vector2 pos_;					// �ʒu
		std::vector<Vector2> vertices_;	// ���_�z��
		BodyType body_type_;				// �Î~�I�u�W�F�N�g���ǂ���
		float density_;					// ���x
		float friction_;				// ���C�W��
		float bounciness_;				// �����W��

		PolygonInitializer()
			:pos_(Vector2::zero())
			, body_type_(kStaticBody)
			, density_(1.0f)
			, friction_(0.6f)
			, bounciness_(0.0f)
		{
		}
	};

	//==========================================================
	// �T�v  :�S�R���C�_�[�̊��N���X
	//==========================================================
	class PolygonCollider : public Collider
	{
	public:
		PolygonCollider(const PolygonInitializer &ini);
		virtual ~PolygonCollider() {};

		// variables
		bool is_trigger_;	// �g���K�[�Ƃ��Đݒ肷�邩�ǂ���

		float friction_;	// �����C�W��
		float bounciness_;	// �����W��

		// methods

	protected:

		// methods
		virtual void OnCollisionEnter(Collider *hit) {};
		virtual void OnCollisionStay(Collider *hit) {};
		virtual void OnCollisionExit(Collider *hit) {};
		virtual void OnTriggerEnter(Collider *hit) {};
		virtual void OnTriggerStay(Collider *hit) {};
		virtual void OnTriggerExit(Collider *hit) {};

	private:
		// variables


		// methods

	};
}

#endif