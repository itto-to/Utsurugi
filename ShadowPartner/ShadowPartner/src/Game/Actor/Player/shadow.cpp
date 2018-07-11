//==========================================================
// �T�v  :�V���h�E�R���|�[�l���g
// Author:Ittoto
// Copyright(c) Utsurugi.All right reserved.
//==========================================================

#include "shadow.h"

#include "../../../Base/2D/sprite.h"
#include "../../../Base/Physics/Element/box_collider.h"
#include "./../../../Base/Physics/Filter/collision_filter.h"
#include "../Common/jumper.h"
#include "shadow_state.h"
#include "idle_state.h"
#include "landing_trigger.h"
#include "gimmck_trigger.h"
#include "action_trigger.h"
#include "player.h"
#include "../../../Base/Input/input.h"

using namespace physics;

namespace shadowpartner
{
	namespace
	{
		const float kSmallShadowJumpVelocity  = 7.0f;
		const float kMiddleShadowJumpVelocity = 2.0f;
	}

	Shadow::Shadow() :
		is_shadow_state_(true)
	{
		is_controllable_ = false;
	}

	Shadow::Shadow(ActorState* state) : 
		Actor(state), 
		is_shadow_state_(true)
	{
		is_controllable_ = false;
	}

	Shadow::~Shadow()
	{
		delete state_;
		state_ = nullptr;
	}

	void Shadow::Start()
	{
		sprite_          = GetComponent<Sprite>();
		land_trigger_    = GetComponent<LandingTrigger>();
		gimmick_trigger_ = GetComponent<GimmickTrigger>();
		action_trigger_  = GetComponent<ActionTrigger>();
		collider_        = GetComponent<physics::BoxCollider>();
		jumper_          = GetComponent<Jumper>();
	}

	void Shadow::Update()
	{
		// ���̉���ԂŌ��ɓ������Ă��Ȃ��Ȃ�v���C���[�̌��ɖ߂�
		if (!is_shadow_state_ && !gimmick_trigger_->IsHitLight() && state_->StateCounter() > 10)
		{
			ReturnToPlayerShadow();
		}
		else if (transform_->position_.y < -10.0f)
		{
			// ����������v���C���[�̌��ɖ߂�
			ReturnToPlayerShadow();
		}
		state_->Execute();
	}

	void Shadow::SetShadowSize(ShadowSize shadow_size)
	{
		Sprite *sprite = game_object_->GetComponent<Sprite>();
		switch (shadow_size)
		{
		case kSmallShadow:
			sprite->SetSize(kSmallShadowSize);
			break;

		case kMiddleShadow:
			sprite->SetSize(kMiddleShadowSize);
			break;

		case kLargeShadow:
			sprite->SetSize(kLargeShadowSize);
			break;
		}
	}

	void Shadow::CreateShadow()
	{
	}

	void Shadow::CreateSmallShadow()
	{
		sprite_->SetSize(kSmallShadowSize);
		sprite_->SetFlipY(false);

		*game_object_->transform_ = *player_object_->transform_;
		game_object_->transform_->position_ += Vector2(0.0f, kSmallShadowSize.y / 2.0f - kMiddleShadowSize.y / 2.0f);

		// �ҋ@��Ԃ�
		ChangeState(new IdleState(this));
		is_shadow_state_ = false;
		// ����\��
		SetControllable(true);
		// �W�����v�ݒ�
		jumper_->SetCanJump(true);
		jumper_->SetInitialVelocity(kSmallShadowJumpVelocity);

		// ��`�̓����蔻��̐ݒ�
		BoxInitializer box_init;
		box_init.width_         = kSmallShadowCollisionSize.x;
		box_init.height_        = kSmallShadowCollisionSize.y;
		box_init.bounciness_    = 0.0f;
		box_init.density_       = 1.1f;
		box_init.friction_      = 0.0f;
		box_init.category_bits_ = CollisionFilter::kShadow;
		box_init.mask_bits_     = ~CollisionFilter::kPlayer;
		box_init.body_type_     = kDynamicBody;
		box_init.pos_           = game_object_->transform_->position_;

		collider_->ReSet(box_init);

		// �����蔻��I��
		collider_->SetActive(true);

		land_trigger_->SetTransform(transform_->position_, transform_->rotation_);

		// �ڒn����g���K�[
		BoxInitializer land_init;
		land_init.body_type_     = kDynamicBody;
		land_init.gravity_scale_ = 0.0f;
		land_init.is_trigger_    = true;
		land_init.pos_           = transform_->position_;
		land_init.width_         = kSmallShadowCollisionSize.x - 0.1f;
		land_init.height_        = 0.1f;
		land_init.offset_        = Vector2(0.0f, -kSmallShadowCollisionSize.y / 2.0f);
		land_init.is_trigger_    = true;
		land_init.category_bits_ = CollisionFilter::kLandingTirgger;
		land_init.mask_bits_     = CollisionFilter::kPlatform | CollisionFilter::kClimb | CollisionFilter::kActionObject;
		land_trigger_->ReSet(land_init);
		land_trigger_->SetSleepingAllowed(false);


		// �M�~�b�N�g���K�[�̍Đݒ�
		BoxInitializer gimmick_init;
		gimmick_init.body_type_     = kDynamicBody;
		gimmick_init.gravity_scale_ = 0.0f;
		gimmick_init.pos_           = transform_->position_;
		gimmick_init.width_         = kSmallShadowCollisionSize.x;
		gimmick_init.height_        = kSmallShadowCollisionSize.y;
		gimmick_init.is_trigger_    = true;
		gimmick_init.offset_        = Vector2::zero();
		gimmick_init.category_bits_ = CollisionFilter::kGimmickTrigger;
		gimmick_init.mask_bits_     = CollisionFilter::kLight | CollisionFilter::kClimb;	// ���ƃc�^������������

		gimmick_trigger_->ReSet(gimmick_init);

	}

	void Shadow::CreateMiddleShadow()
	{
		sprite_->SetSize(kMiddleShadowSize);
		sprite_->SetFlipY(false);

		*game_object_->transform_ = *player_object_->transform_;

		// �ҋ@��Ԃ�
		ChangeState(new IdleState(this));
		is_shadow_state_ = false;
		// ����\��
		SetControllable(true);
		// �W�����v�ݒ�
		jumper_->SetCanJump(true);
		jumper_->SetInitialVelocity(kMiddleShadowJumpVelocity);

		// ��`�̓����蔻��̐ݒ�
		BoxInitializer box_init;
		box_init.width_         = kMiddleShadowCollisionSize.x;
		box_init.height_        = kMiddleShadowCollisionSize.y;
		box_init.density_       = 1.0f;
		box_init.friction_      = 0.0f;
		box_init.bounciness_    = 0.0f;
		box_init.category_bits_ = CollisionFilter::kShadow;
		box_init.mask_bits_     = ~CollisionFilter::kPlayer;
		box_init.body_type_     = kDynamicBody;
		box_init.pos_           = game_object_->transform_->position_;

		collider_->ReSet(box_init);
		// �����蔻��I��
		collider_->SetActive(true);

		// �ڒn����g���K�[
		BoxInitializer land_init;
		land_init.body_type_     = kDynamicBody;
		land_init.gravity_scale_ = 0.0f;
		land_init.is_trigger_    = true;
		land_init.pos_           = transform_->position_;
		land_init.width_         = kMiddleShadowCollisionSize.x - 0.1f;
		land_init.height_        = 0.1f;
		land_init.offset_        = Vector2(0.0f, -kMiddleShadowCollisionSize.y / 2.0f);
		land_init.is_trigger_    = true;
		land_init.category_bits_ = CollisionFilter::kLandingTirgger;
		land_init.mask_bits_     = CollisionFilter::kPlatform | CollisionFilter::kClimb | CollisionFilter::kActionObject;
		land_trigger_->ReSet(land_init);
		land_trigger_->SetSleepingAllowed(false);

		// �M�~�b�N�g���K�[�̍Đݒ�
		BoxInitializer gimmick_init;
		gimmick_init.body_type_     = kDynamicBody;
		gimmick_init.gravity_scale_ = 0.0f;
		gimmick_init.pos_           = transform_->position_;
		gimmick_init.width_         = kMiddleShadowCollisionSize.x;
		gimmick_init.height_        = kMiddleShadowCollisionSize.y;
		gimmick_init.is_trigger_    = true;
		gimmick_init.offset_        = Vector2::zero();
		gimmick_init.category_bits_ = CollisionFilter::kGimmickTrigger;
		gimmick_init.mask_bits_     = CollisionFilter::kLight | CollisionFilter::kClimb;	// ���ƃc�^������������

		gimmick_trigger_->ReSet(gimmick_init);
	}

	void Shadow::CreateLargeShadow()
	{
		sprite_->SetSize(kLargeShadowSize);
		sprite_->SetFlipY(false);

		*game_object_->transform_ = *player_object_->transform_;
		game_object_->transform_->position_ += Vector2(0.0f, kLargeShadowSize.y / 2.0f - kMiddleShadowSize.y / 2.0f);

		// �ҋ@��Ԃ�
		ChangeState(new IdleState(this));
		is_shadow_state_ = false;
		// ����\��
		SetControllable(true);
		// �W�����v�ݒ�
		jumper_->SetCanJump(true);

		// ��`�̓����蔻��̐ݒ�
		BoxInitializer box_init;
		box_init.pos_           = this->transform_->position_;
		box_init.width_         = kLargeShadowCollisionSize.x;
		box_init.height_        = kLargeShadowCollisionSize.y;
		box_init.bounciness_    = 0.0f;
		box_init.friction_      = 0.0f;
		box_init.category_bits_ = CollisionFilter::kShadow;
		box_init.mask_bits_     = ~CollisionFilter::kPlayer;
		box_init.body_type_     = kDynamicBody;
		box_init.pos_           = game_object_->transform_->position_;

		collider_->ReSet(box_init);

		// �����蔻��I��
		collider_->SetActive(true);

		// ���n����g���K�[�Đݒ�
		BoxInitializer land_init;
		land_init.body_type_     = kDynamicBody;
		land_init.gravity_scale_ = 0.0f;
		land_init.is_trigger_    = true;
		land_init.pos_           = transform_->position_;
		land_init.width_         = kLargeShadowCollisionSize.x - 0.1f;
		land_init.height_        = 0.1f;
		land_init.offset_        = Vector2(0.0f, -kLargeShadowCollisionSize.y / 2.0f);
		land_init.is_trigger_    = true;
		land_init.category_bits_ = CollisionFilter::kLandingTirgger;
		land_init.mask_bits_     = CollisionFilter::kPlatform | CollisionFilter::kClimb | CollisionFilter::kActionObject;
		land_trigger_->ReSet(land_init);
		land_trigger_->SetSleepingAllowed(false);

		// �M�~�b�N�g���K�[�̍Đݒ�
		BoxInitializer gimmick_init;
		gimmick_init.body_type_     = kDynamicBody;
		gimmick_init.gravity_scale_ = 0.0f;
		gimmick_init.pos_           = transform_->position_;
		gimmick_init.width_         = kLargeShadowCollisionSize.x;
		gimmick_init.height_        = kLargeShadowCollisionSize.y;
		gimmick_init.is_trigger_    = true;
		gimmick_init.offset_        = Vector2::zero();
		gimmick_init.category_bits_ = CollisionFilter::kGimmickTrigger;
		gimmick_init.mask_bits_     = CollisionFilter::kLight | CollisionFilter::kClimb;	// ���ƃc�^������������

		gimmick_trigger_->ReSet(gimmick_init);
	}

	void Shadow::ReturnToPlayerShadow()
	{
		is_shadow_state_ = true;

		// TODO:�������Ă�����ɍ��킹�ĉe�̍��W������
		sprite_->SetSize(kMiddleShadowSize);
		game_object_->transform_->position_ = player_object_->transform_->position_ - Vector2(0.0f, kMiddleShadowSize.y);
		
		// �X�v���C�g�㉺���]
		sprite_->SetFlipY(true);

		// �����蔻��I�t
		collider_->SetActive(false);

		// �e��Ԃɖ߂�
		ChangeState(new ShadowState(this));

		// �v���C���[��ҋ@��Ԃɖ߂�
		Player *player = player_object_->GetComponent<Player>();
		player->ChangeState(new IdleState(player));
		player->SetControllable(true);
	}

	void Shadow::SetPlayerObject(GameObject *player_object)
	{
		player_object_ = player_object;
	}

	GameObject *Shadow::GetPlayerObject()
	{
		return player_object_;
	}

}	// namespace shadowpartner
