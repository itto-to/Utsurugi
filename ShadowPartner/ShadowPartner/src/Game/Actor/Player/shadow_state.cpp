#include "shadow_state.h"

#include "shadow.h"
#include "player.h"
#include "../Player/gimmck_trigger.h"
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

	void ShadowState::Enter()
	{
	}

	void ShadowState::ExecuteState()
	{
		if (player_ == nullptr)
		{
			// �v���C���[�R���|�[�l���g�擾
			player_ = static_cast<Shadow*>(owner_)->GetPlayerObject()->GetComponent<Player>();
			player_gimmick_trigger_ = player_->GetComponent<GimmickTrigger>();
		}

		if (collider_ == nullptr)
		{
			// �R���C�_�[�R���|�[�l���g�擾
			collider_ = owner_->GetComponentInherit<Collider>();
		}

		// �I�u�W�F�N�g�ƃR���C�_�[���ړ�
		Vector2 offset = Vector2(0.0f, -kMiddleShadowCollisionSize.y / 2.0f);
		switch (player_gimmick_trigger_->HittingLightType())
		{
		case LightType::kLarge:
			offset.y -= kLargeShadowCollisionSize.y / 2.0f;
			break;
		case LightType::kMiddle:
			offset.y -= kMiddleShadowCollisionSize.y / 2.0f;
			break;
		case LightType::kSmall:
			offset.y -= kSmallShadowCollisionSize.y / 2.0f;
			break;
		case LightType::kLightNone:
			offset.y -= kMiddleShadowCollisionSize.y / 2.0f;
			break;
		}
		owner_->transform_->position_ = player_->transform_->position_ + offset;
		collider_->SetTransform(owner_->transform_->position_, owner_->transform_->rotation_);
		
		// �v���C���[��UV���W���e�ɂ��Z�b�g
		Vector2 uv_offset = player_->GetComponent<Sprite>()->UvOffset();
		owner_->GetComponent<Sprite>()->SetUvOffset(uv_offset);

		if (owner_->GetDirection() != player_->GetDirection())
		{
			owner_->SetDirection(player_->GetDirection());
			if (owner_->GetDirection() == ActorDirection::kRight)
			{
				// �E�ړ��Ȃ�
				Sprite *sprite = owner_->GetComponent<Sprite>();
				sprite->SetFlipX(false);
				sprite->SetFlipY(true);
			}
			else
			{	
				// ���ړ��Ȃ�
				Sprite *sprite = owner_->GetComponent<Sprite>();
				sprite->SetFlipX(true);
				sprite->SetFlipY(true);

			}
		}

	}

}	// namespace shadowpartner