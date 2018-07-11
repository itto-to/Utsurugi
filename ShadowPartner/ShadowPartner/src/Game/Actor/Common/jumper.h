//==========================================================
// �T�v  :�W�����v�R���|�[�l���g
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
	float initial_velocity_;		// �W�����v�̏���
	float gravity_scale_;			// �d�͌W�� 0.0�Ŗ��d�� 1.0�Œʏ�

private:
	Transform *transform_;
};

}	// namespace shadowpartner

#endif