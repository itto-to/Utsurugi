#include "idle_state.h"

#include "jump_state.h"
#include "walk_state.h"
#include "../Common/actor.h"
#include "../../../Base/Input/input.h"
#include "../../../Base/Physics/physics.h"

using namespace physics;

namespace shadowpartner
{

	void IdleState::Execute()
	{
		if (input::Input::Instance()->GetAxis(input::InputAxis::Horizontal) != 0.0f)
		{
			// 移動
			owner_->ChangeState(new WalkState(owner_));
		}
		else if (input::Input::Instance()->GetButton(input::InputButton::Jump))
		{
			// ジャンプ
			// ジャンプ入力
			BoxCollider *box_collider = owner_->GetComponent<BoxCollider>();
			box_collider->AddForce(Vector2::up() * 700000000.0f);
			owner_->ChangeState(new JumpState(owner_));
		}
	}

}	// namespace shadowpartner