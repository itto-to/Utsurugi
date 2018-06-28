//==========================================================
// 概要  :ヒンジジョイント
// Author:Itsuki Namito
// Copyright(c) Utsurugi.All right reserved.
//==========================================================

#ifndef _BASE_PHYSICS_JOINT_REVOLUTE_JOINT_H_
#define _BASE_PHYSICS_JOINT_REVOLUTE_JOINT_H_

//**********************************************************
// インクルードファイル
//**********************************************************
#include "../Element/collider.h"
#include "joint.h"

using namespace shadowpartner;

namespace physics
{
	struct RevoluteInitializer
	{
		Collider *collider_a_;	// ジョイントするオブジェクト一つ目
		Vector2 local_anchor_a_;
		Collider *collider_b_;	// ジョイントするオブジェクト二つ目
		Vector2 local_anchor_b_;

		Vector2 world_pos_;		// ジョイントのワールド座標

		bool enable_limit_;		// 回転を制限する
		float lower_angle_;		// 回転の最小値(度数)
		float upper_angle_;		// 回転の最大値(度数)

		RevoluteInitializer()
			:collider_a_(nullptr)
			,local_anchor_a_(Vector2::zero())
			,collider_b_(nullptr)
			,local_anchor_b_(Vector2::zero())
			,world_pos_(Vector2::zero())
			,enable_limit_(false)
			,lower_angle_(0.0f)
			,upper_angle_(0.0f)
		{
		}
	};

	//==========================================================
	// 概要  :全コライダーの基底クラス
	//==========================================================
	class RevoluteJoint : public Joint
	{
	public:
		RevoluteJoint(const RevoluteInitializer &initializer);
		virtual ~RevoluteJoint() {};

		// variables
		// methods
		
		void SetLimitAngles(float lower, float upper);
		void EnableLimit(bool flag);

	protected:

		// methods

	private:
		// variables
		b2RevoluteJoint *revolute_joint_;
		// methods

	};
}

#endif