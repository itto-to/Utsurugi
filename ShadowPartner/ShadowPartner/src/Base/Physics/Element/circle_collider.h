//==========================================================
// 概要  :円形の当たり判定
// Author:Itsuki Namito
// Copyright(c) Utsurugi.All right reserved.
//==========================================================

#ifndef _BASE_PHYSICS_ELEMENT_CIRCLE_COLLIDER_H_
#define _BASE_PHYSICS_ELEMENT_CIRCLE_COLLIDER_H_

//**********************************************************
// インクルードファイル
//**********************************************************
#include "collider.h"

using namespace shadowpartner;

namespace physics
{
	//
	struct CircleInitializer
	{
		Vector2 pos_;		// 位置
		Vector2 offset_;
		float radius_;
		bool is_static_;	// 静止オブジェクトかどうか
		float density_;		// 密度
		float friction_;	// 摩擦係数
		float bounciness_;	// 反発係数

		CircleInitializer()
			:pos_(Vector2::zero())
			, offset_(Vector2::zero())
			, radius_(1.0f)
			, is_static_(true)
			, density_(1.0f)
			, friction_(0.6f)
			, bounciness_(0.0f)
		{
		}
	};

	//==========================================================
	// 概要  :全コライダーの基底クラス
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