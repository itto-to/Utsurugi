//==========================================================
// 概要  :衝突判定フィルタ
// Author:Ittoto
// Copyright(c) Utsurugi.All right reserved.
//==========================================================
#ifndef _BASE_PHYSICS_COLLISIONFILTER_H_
#define _BASE_PHYSICS_COLLISIONFILTER_H_

enum CollisionFilter
{
	kPlatform              = 1 << 0,
	kPlayer                = 1 << 1,
	kShadow                = 1 << 2,
	kEnemy                 = 1 << 3,
	kLight                 = 1 << 4,
	kClimb                 = 1 << 5,
	kLandingTirgger        = 1 << 6,
	kGimmickTrigger        = 1 << 7,
	kActionTrigger         = 1 << 8,
	kActionObject          = 1 << 9,
	kIvy                   = 1 << 10,
	kDefaultMask           = 0xFFFF,	// 全てのフィクスチャと衝突
};

#endif //_BASE_PHYSICS_COLLISIONFILTER_H_