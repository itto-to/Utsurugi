//==========================================================
// �T�v  :�S�R���C�_�[�̊��N���X
// Author:Itsuki Namito
// Copyright(c) Utsurugi.All right reserved.
//==========================================================

#ifndef _BASE_PHYSICS_ELEMENT_COLLIDER_H_
#define _BASE_PHYSICS_ELEMENT_COLLIDER_H_

//**********************************************************
// �C���N���[�h�t�@�C��
//**********************************************************
#include <Box2D\Box2D.h>
#include "../../Element/component.h"
#include <windows.h>
#include <typeinfo>

using namespace shadowpartner;

namespace physics
{
	enum PhysicsShape
	{
		Box,
		Circle,
		Polygon,
		Edge,
		ShapeCount
	};

	// �N���X�錾
	class Collider;

	//==========================================================
	// �T�v  :�Փˏ���n�����߂̃N���X
	//==========================================================
	class Collision
	{
	public:
		Collider collider_;
		
	private:

	};

	//==========================================================
	// �T�v  :�S�R���C�_�[�̊��N���X
	//==========================================================
	class Collider : public Component
	{
	public:
		Collider();
		Collider(Collider &copy);
		virtual ~Collider() {};
		
		// variables
		PhysicsShape shape;
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