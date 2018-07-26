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
		unsigned short category_bits_;	// 自分のフィルタービット列
		unsigned short mask_bits_;		// 当たる相手のフィルタービット列
		float gravity_scale_;	// 重力係数

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
			, category_bits_(CollisionFilter::kDefault)
			, mask_bits_(0xffff)
			, gravity_scale_(1.0f)
		{
		}

		BoxInitializer(
			Vector2 pos, Vector2 offset, float width, float height, BodyType body_type,
			bool is_trigger, bool fixed_rotation, float density, float friction, float bounciness,
			unsigned short category_bits, unsigned short mask_bits, float gravity_scale
			)
			: pos_(pos)
			, offset_(offset)
			, width_(width)
			, height_(height)
			, body_type_(body_type)
			, is_trigger_(is_trigger)
			, fixed_rotation_(fixed_rotation)
			, density_(density)
			, friction_(friction)
			, bounciness_(bounciness)
			, category_bits_(category_bits)
			, mask_bits_(mask_bits)
			, gravity_scale_(gravity_scale)
		{
		}
	};

	//==========================================================
	// 概要  :全コライダーの基底クラス
	//==========================================================
	class BoxCollider : public Collider
	{
	public:
		BoxCollider();
		BoxCollider(const BoxInitializer &initializer);
		virtual ~BoxCollider() {};

		// variables
		// methods
		Vector2 GetSize();

		void ReSet(const BoxInitializer &initializer);

		void SetOffset(const Vector2 &offset);

		void AddFixture(const BoxInitializer& ini);

	protected:

		// methods
		void Start();

		void SetCollider(const BoxInitializer &ini);

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