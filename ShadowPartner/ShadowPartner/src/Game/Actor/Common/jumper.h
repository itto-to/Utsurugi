//==========================================================
// 概要  :ジャンプコンポーネント
// Author:Ittoto
// Copyright(c) Utsurugi.All right reserved.
//==========================================================
#ifndef _GAME_ACTOR_COMMON_JUMPER_H_
#define _GAME_ACTOR_COMMON_JUMPER_H_

#include "../../../Base/Element/component.h"
#include "../../../Base/Physics/physics.h"

#include "../../../Base/Element/transform.h"

namespace physics
{
	class Collider;
}

namespace shadowpartner
{

class Jumper : public Component
{
public:
	Jumper();
	Jumper(bool can_jump, float force, float gravity);

	// methods
	void Jump();
	float Force();
	void SetCanJump(bool can_jump);
	bool CanJump();
	void SetForce(float force);
	float Gravity();
	void SetGravity(float gravity);

protected:
	void Start() override;

	physics::Collider *collider_;
	bool can_jump_;
	float force_;
	float gravity_;

private:
	Transform *transform_;
};

}	// namespace shadowpartner

#endif