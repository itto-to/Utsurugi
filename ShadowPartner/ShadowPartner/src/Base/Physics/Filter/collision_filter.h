//==========================================================
// 概要  :衝突判定フィルタ
// Author:Ittoto
// Copyright(c) Utsurugi.All right reserved.
//==========================================================
#ifndef _BASE_PHYSICS_COLLISIONFILTER_H_
#define _BASE_PHYSICS_COLLISIONFILTER_H_

enum CollisionFilter
{
	kDefaultCategory       = 1 << 0,
	kPlayer                = 1 << 1,
	kShadow                = 1 << 2,
	kEnemy                 = 1 << 3,
	kClimb                 = 1 << 4,
	kActionTrigger         = 1 << 5,
	kActionObject          = 1 << 6,
	kDefaultMask           = 0xFFFF,	// 全てのフィクスチャと衝突
};

#endif //_BASE_PHYSICS_COLLISIONFILTER_H_