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
			// �v���C���[�R���|�[�l���g�擾
			player_ = static_cast<Shadow*>(owner_)->GetPlayerObject()->GetComponent<Player>();
		}

		if (collider_ == nullptr)
		{
			// �R���C�_�[�R���|�[�l���g�擾
			collider_ = owner_->GetComponentInherit<Collider>();
		}

		// �I�u�W�F�N�g�ƃR���C�_�[���ړ�
		owner_->transform_->position_ = player_->transform_->position_ + Vector2::down() * 1.0f;
		collider_->SetTransform(owner_->transform_->position_, owner_->transform_->rotation_);
		
		// 
		if (owner_->GetDirection() != player_->GetDirection())
		{
			owner_->SetDirection(player_->GetDirection());
			if (owner_->GetDirection() == ActorDirection::kRight)
			{
				// �E�ړ��Ȃ�
				owner_->GetComponent<Sprite>()->SetUvInvertY();
			}
			else
			{	
				// ���ړ��Ȃ�
				owner_->GetComponent<Sprite>()->SetUvInvertXY();
			}
		}
	}

}	// namespace shadowpartner