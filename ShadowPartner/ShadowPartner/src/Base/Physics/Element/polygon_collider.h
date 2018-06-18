//==========================================================
// 概要  :凸ポリゴンの当たり判定
// Author:Itsuki Namito
// Copyright(c) Utsurugi.All right reserved.
//==========================================================

#ifndef _BASE_PHYSICS_ELEMENT_POLYGONCOLLIDER_H_
#define _BASE_PHYSICS_ELEMENT_POLYGONCOLLIDER_H_

//**********************************************************
// インクルードファイル
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
		Vector2 pos_;					// 位置
		std::vector<Vector2> vertices_;	// 頂点配列
		BodyType body_type_;				// 静止オブジェクトかどうか
		float density_;					// 密度
		float friction_;				// 摩擦係数
		float bounciness_;				// 反発係数

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
	// 概要  :全コライダーの基底クラス
	//==========================================================
	class PolygonCollider : public Collider
	{
	public:
		PolygonCollider(const PolygonInitializer &ini);
		virtual ~PolygonCollider() {};

		// variables
		bool is_trigger_;	// トリガーとして設定するかどうか

		float friction_;	// 動摩擦係数
		float bounciness_;	// 反発係数

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