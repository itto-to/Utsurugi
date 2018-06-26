//==========================================================
// 概要  :衝突判定フィルタ
// Author:Ittoto
// Copyright(c) Utsurugi.All right reserved.
//==========================================================
#ifndef _BASE_PHYSICS_COLLISIONFILTER_H_
#define _BASE_PHYSICS_COLLISIONFILTER_H_

enum CollisionFilter
{
	kNone   = 1 << 0,
	kPlayer = 1 << 1,
	kShadow = 1 << 2,
	kEnemy  = 1 << 3,
	kClimb  = 1 << 4,
};

#endif //_BASE_PHYSICS_COLLISIONFILTER_H_