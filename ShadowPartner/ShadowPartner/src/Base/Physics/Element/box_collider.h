//==========================================================
// 概要  :矩形の当たり判定
// Author:Itsuki Namito
// Copyright(c) Utsurugi.All right reserved.
//==========================================================

#ifndef _BASE_PHYSICS_ELEMENT_BOX_COLLIDER_H_
#define _BASE_PHYSICS_ELEMENT_BOX_COLLIDER_H_

//**********************************************************
// インクルードファイル
//**********************************************************
#include "collider.h"

using namespace shadowpartner;

namespace physics
{

	struct BoxInitializer
	{
		Vector2 pos_;			// 位置
		Vector2 offset_;
		float width_;			// 横幅
		float height_;			// 縦幅
		BodyType body_type_;	// ボディーのタイプ
		bool is_trigger_;		// トリガーかどうか
		bool fixed_rotation_;	// trueで回転を許可しない
		float density_;			// 密度
		float friction_;		// 摩擦係数
		float bounciness_;		// 反発係数

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
	// 概要  :全コライダーの基底クラス
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