//==========================================================
// 概要  :シャドウコンポーネント
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
		landing_trigger_ = GetComponent<LandingTrigger>();
		gimmick_trigger_ = GetComponent<GimmickTrigger>();
		action_trigger_  = GetComponent<ActionTrigger>();
		collider_        = GetComponent<physics::BoxCollider>();
		jumper_          = GetComponent<Jumper>();
	}

	void Shadow::Update()
	{
		// 実体化状態で光に当たっていないならプレイヤーの元に戻る
		if (!is_shadow_state_ && !gimmick_trigger_->IsHitLight() && state_->StateCounter() > 10)
		{
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

		// 待機状態に
		ChangeState(new IdleState(this));
		is_shadow_state_ = false;
		// 操作可能に
		SetControllable(true);
		// ジャンプ設定
		jumper_->SetCanJump(true);

		// 矩形の当たり判定の設定
		BoxInitializer box_init;
		box_init.width_         = kSmallShadowCollisionSize.x;
		box_init.height_        = kSmallShadowCollisionSize.y;
		box_init.bounciness_    = 0.0f;
		box_init.density_       = 1.1f;
		box_init.category_bits_ = CollisionFilter::kShadow;
		box_init.mask_bits_     = ~CollisionFilter::kPlayer;
		box_init.body_type_     = kDynamicBody;
		box_init.pos_           = game_object_->transform_->position_;

		collider_->ReSet(box_init);

		// 当たり判定オン
		collider_->SetActive(true);

		landing_trigger_->SetTransform(transform_->position_, transform_->rotation_);

	}

	void Shadow::CreateMiddleShadow()
	{
		sprite_->SetSize(kMiddleShadowSize);
		sprite_->SetFlipY(false);

		*game_object_->transform_ = *player_object_->transform_;

		// 待機状態に
		ChangeState(new IdleState(this));
		is_shadow_state_ = false;
		// 操作可能に
		SetControllable(true);
		// ジャンプ設定
		jumper_->SetCanJump(true);

		// 矩形の当たり判定の設定
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
		// 当たり判定オン
		collider_->SetActive(true);
	}

	void Shadow::CreateLargeShadow()
	{
		sprite_->SetSize(kLargeShadowSize);
		sprite_->SetFlipY(false);

		*game_object_->transform_ = *player_object_->transform_;
		game_object_->transform_->position_ += Vector2(0.0f, kLargeShadowSize.y / 2.0f - kMiddleShadowSize.y / 2.0f);

		// 待機状態に
		ChangeState(new IdleState(this));
		is_shadow_state_ = false;
		// 操作可能に
		SetControllable(true);
		// ジャンプ設定
		jumper_->SetCanJump(true);

		// 矩形の当たり判定の設定
		BoxInitializer box_init;
		box_init.pos_           = this->transform_->position_;
		box_init.width_         = kLargeShadowCollisionSize.x;
		box_init.height_        = kLargeShadowCollisionSize.y;
		box_init.bounciness_    = 0.0f;
		box_init.category_bits_ = CollisionFilter::kShadow;
		box_init.mask_bits_     = ~CollisionFilter::kPlayer;
		box_init.body_type_     = kDynamicBody;
		box_init.pos_           = game_object_->transform_->position_;

		collider_->ReSet(box_init);

		// 当たり判定オン
		collider_->SetActive(true);
	}

	void Shadow::ReturnToPlayerShadow()
	{
		is_shadow_state_ = true;

		// TODO:当たっている光に合わせて影の座標も決定
		sprite_->SetSize(kMiddleShadowSize);
		game_object_->transform_->position_ = player_object_->transform_->position_ - Vector2(0.0f, kMiddleShadowSize.y);
		
		// スプライト上下反転
		sprite_->SetFlipY(true);

		// 当たり判定オフ
		collider_->SetActive(false);

		// 影状態に戻る
		ChangeState(new ShadowState(this));

		// プレイヤーを待機状態に戻す
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
