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
	Jumper(bool can_jump, float initial_velocity, float gravity);

	// methods
	void Jump();
	float Force();
	void SetCanJump(bool can_jump);
	bool CanJump();
	void SetInitialVelocity(float initial_velocity);
	float Gravity();
	void SetGravity(float gravity);

protected:
	void Start() override;

	physics::Collider *collider_;
	bool  can_jump_;
	float initial_velocity_;		// ジャンプの初速
	float gravity_scale_;			// 重力係数 0.0で無重力 1.0で通常

private:
	Transform *transform_;
};

}	// namespace shadowpartner

#endif