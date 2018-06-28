//==========================================================
// 概要  :ジョイントの基底クラス
// Author:Itsuki Namito
// Copyright(c) Utsurugi.All right reserved.
//==========================================================

#ifndef _BASE_PHYSICS_JOINT_JOINT_H_
#define _BASE_PHYSICS_JOINT_JOINT_H_

//**********************************************************
// インクルードファイル
//**********************************************************
#include "../Element/collider.h"

#include "../../Element/component.h"

using namespace shadowpartner;

namespace physics
{
	enum JointType
	{
		kRevolute,	// ヒンジジョイント
	};

	//==========================================================
	// 概要  :全コライダーの基底クラス
	//==========================================================
	class Joint : public Component
	{
	public:
		Joint();
		virtual ~Joint();

		// variables
		JointType type_;	
		int index_;			// ワールドに紐づけられたインデックス
		Collider *collider_a_;
		Collider *collider_b_;
		// methods
		//virtual void SetActive(bool is_active) override;

		friend class PhysicsWorld;

	protected:
		// variables
		b2Joint *joint_;

		// methods
		void Start() {};

	private:
		// variables
		// methods

	};
}

#endif