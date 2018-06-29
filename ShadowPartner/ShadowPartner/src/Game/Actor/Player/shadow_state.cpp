#include "shadow_state.h"

#include "shadow.h"
#include "player.h"
#include "../../../Base/Physics/Element/collider.h"
#include "../../../Base/2D/sprite.h"

using namespace physics;

namespace shadowpartner
{
	class GameObject;

	ShadowState::ShadowState(Actor * owner)	:
		ActorState(owner),
		player_(nullptr),
		collider_(nullptr)
	{
	}

	void ShadowState::ExecuteState()
	{
		if (player_ == nullptr)
		{
			// プレイヤーコンポーネント取得
			player_ = static_cast<Shadow*>(owner_)->GetPlayerObject()->GetComponent<Player>();
		}

		if (collider_ == nullptr)
		{
			// コライダーコンポーネント取得
			collider_ = owner_->GetComponentInherit<Collider>();
		}

		// オブジェクトとコライダーを移動
		owner_->transform_->position_ = player_->transform_->position_ + Vector2::down() * 1.0f;
		collider_->SetTransform(owner_->transform_->position_, owner_->transform_->rotation_);
		
		// 
		if (owner_->GetDirection() != player_->GetDirection())
		{
			owner_->SetDirection(player_->GetDirection());
			if (owner_->GetDirection() == ActorDirection::kRight)
			{
				// 右移動なら
				owner_->GetComponent<Sprite>()->SetUvInvertY();
			}
			else
			{	
				// 左移動なら
				owner_->GetComponent<Sprite>()->SetUvInvertXY();
			}
		}
	}

}	// namespace shadowpartner