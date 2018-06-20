#include "shadow_state.h"

#include "player.h"
#include "../../../Base/Physics/Element/collider.h"

using namespace physics;

namespace shadowpartner
{
	class GameObject;

	ShadowState::ShadowState(Actor * owner)	: ActorState(owner)
	{
	}

	// 親となるプレイヤーをセット
	void ShadowState::SetPlayer(GameObject *player)
	{
		player_ = player;
	}

	void ShadowState::Execute()
	{
		owner_->transform_->position_ = player_->transform_->position_ + Vector2::down() * 1.0f;
		owner_->GetComponentInherit<Collider>()->SetTransform(owner_->transform_->position_, owner_->transform_->rotation_);
	}

}	// namespace shadowpartner