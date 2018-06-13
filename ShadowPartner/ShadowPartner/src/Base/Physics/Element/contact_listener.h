//==========================================================
// 概要  :衝突リスナー
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

		// 接触が始まった時に呼ばれる
		virtual void BeginContact(b2Contact *contact) override {};
		// 接触が終わった時に呼ばれる
		virtual void EndContact(b2Contact *contact) override {};
		// 毎ステップ、衝突の解決処理が行われる直前に呼ばれる
		virtual void PreSolve(b2Contact *contact, const b2Manifold *old_manifold) override {};
		// 毎ステップ、衝突の解決処理が行われた直後に呼ばれる
		virtual void PostSolve(b2Contact *contact, const b2ContactImpulse *impulse) override {};

	private:

	};

}	// namespace physics

#endif