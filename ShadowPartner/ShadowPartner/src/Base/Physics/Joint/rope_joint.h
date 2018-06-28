//==========================================================
// 概要  :ロープジョイント
// Author:Itsuki Namito
// Copyright(c) Utsurugi.All right reserved.
//==========================================================

#ifndef _BASE_PHYSICS_JOINT_ROPE_JOINT_H_
#define _BASE_PHYSICS_JOINT_ROPE_JOINT_H_

//**********************************************************
// インクルードファイル
//**********************************************************
#include "../Element/collider.h"
#include "joint.h"

using namespace shadowpartner;

namespace physics
{
	struct RopeInitializer
	{
		Collider *collider_a_;		// ジョイントするオブジェクト一つ目
		Vector2 local_anchor_a_;
		Collider *collider_b_;		// ジョイントするオブジェクト二つ目
		Vector2 local_anchor_b_;

		Vector2 world_pos_;			// ジョイントのワールド座標

		float max_length_;			// ロープの長さの最大値

		bool collide_connected_;	// ジョイントされた者同士で衝突するか

		RopeInitializer()
			:collider_a_(nullptr)
			,local_anchor_a_(Vector2::zero())
			,collider_b_(nullptr)
			,local_anchor_b_(Vector2::zero())
			,world_pos_(Vector2::zero())
			,max_length_(10.0f)
		{
		}
	};

	//==========================================================
	// 概要  :全コライダーの基底クラス
	//==========================================================
	class RopeJoint : public Joint
	{
	public:
		RopeJoint(const RopeInitializer &initializer);
		virtual ~RopeJoint() {};

		// variables
		// methods
		void SetMaxLength(float length);
		float GetMaxLength();

	protected:

		// methods

	private:
		// variables
		b2RopeJoint *rope_joint_;

		// methods

	};
}

#endif