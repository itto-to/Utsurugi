//==========================================================
// �T�v  :�Փ˔���t�B���^
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
	kDefaultMask           = 0xFFFF,	// �S�Ẵt�B�N�X�`���ƏՓ�
};

#endif //_BASE_PHYSICS_COLLISIONFILTER_H_