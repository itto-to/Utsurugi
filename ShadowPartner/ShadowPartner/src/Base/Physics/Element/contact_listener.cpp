//==========================================================
// 概要  :衝突リスナー
// Author:Ittoto
// Copyright(c) Utsurugi.All right reserved.
//==========================================================
#include "contact_listener.h"

#include "../World/physics_world.h"

namespace physics {

ContactListener::ContactListener()
{
	PhysicsWorld::instance_->world_.SetContactListener(this);
}

ContactListener::~ContactListener()
{
}

}