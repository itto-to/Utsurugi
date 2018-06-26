#include "shadow_state.h"

#include "shadow.h"
#include "player.h"
#include "../../../Base/Physics/Element/collider.h"

using namespace physics;

namespace shadowpartner
{
	class GameObject;

	ShadowState::ShadowState(Actor * owner)	: ActorState(owner)
	{
	}

	void ShadowState::ExecuteState()
	{
		owner_->transform_->position_ = static_cast<Shadow*>(owner_)->GetPlayerObject()->transform_->position_ + Vector2::down() * 1.0f;
		owner_->GetComponentInherit<Collider>()->SetTransform(owner_->transform_->position_, owner_->transform_->rotation_);
	}

}	// namespace shadowpartner