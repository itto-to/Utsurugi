//==========================================================
// �T�v  :�Փ˃��X�i�[
// Author:Ittoto
// Copyright(c) Utsurugi.All right reserved.
//==========================================================
#ifndef _BASE_PHYSICS_ELEMENT_CONTACTLISTENER_H_
#define _BASE_PHYSICS_ELEMENT_CONTACTLISTENER_H_

#include "../../../../liquidfun_include/Box2D/Box2D.h"

namespace physics
{

	class ContactListener : public b2ContactListener
	{
	public:
		ContactListener();
		virtual ~ContactListener();

	protected:
		// methods

		// �ڐG���n�܂������ɌĂ΂��
		virtual void BeginContact(b2Contact *contact) override {};
		// �ڐG���I��������ɌĂ΂��
		virtual void EndContact(b2Contact *contact) override {};
		// ���X�e�b�v�A�Փ˂̉����������s���钼�O�ɌĂ΂��
		virtual void PreSolve(b2Contact *contact, const b2Manifold *old_manifold) override {};
		// ���X�e�b�v�A�Փ˂̉����������s��ꂽ����ɌĂ΂��
		virtual void PostSolve(b2Contact *contact, const b2ContactImpulse *impulse) override {};

	private:

	};

}	// namespace physics

#endif