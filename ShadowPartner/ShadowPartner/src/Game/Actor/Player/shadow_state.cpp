#include "shadow_state.h"

#include "player.h"

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
		owner_->transform_->position_ = player_->transform_->position_ + Vector2::down() * 100.0f;
	}

}	// namespace shadowpartner