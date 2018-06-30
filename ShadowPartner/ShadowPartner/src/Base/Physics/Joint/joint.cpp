//==========================================================
// 概要  :ヒンジジョイント
// Author:Itsuki Namito
// Copyright(c) Utsurugi.All right reserved.
//==========================================================
#include "revolute_joint.h"
#include "../World/physics_world.h"

namespace physics
{
	//**********************************************************
	// マクロ
	//**********************************************************

	//**********************************************************
	// 定数
	//**********************************************************

	// コンストラクタ
	Joint::Joint()
		:joint_(nullptr)
	{
	}

	Joint::~Joint()
	{

		PhysicsWorld::DestroyJoint(index_, joint_);
	}

	//void Joint::SetActive(bool is_active)
	//{
	//	if (game_object_ == nullptr || !is_active)
	//	{
	//		is_active_ = false;
	//	
	//	}
	//}

}
