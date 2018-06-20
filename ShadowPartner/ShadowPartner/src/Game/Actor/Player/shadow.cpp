//==========================================================
// 概要  :シャドウコンポーネント
// Author:Ittoto
// Copyright(c) Utsurugi.All right reserved.
//==========================================================

#include "shadow.h"

#include "../../../Base/2D/sprite.h"
#include "../../../Base/Physics/Element/box_collider.h"

using namespace physics;

namespace shadowpartner
{
	namespace
	{
		const Vector2 kSmallShadowSize = Vector2(0.5f, 0.5f);
		const Vector2 kMiddleShadowSize = Vector2(1.0f, 1.0f);
		const Vector2 kLargeShadowSize = Vector2(2.0f, 2.0f);
	}

	Shadow::Shadow()
	{
		is_controllable_ = false;
	}

	Shadow::Shadow(ActorState* state) : Actor(state)
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
		sprite = game_object_->GetComponent<Sprite>();
		collider = game_object_->GetComponent<physics::BoxCollider>();
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

	void Shadow::CreateSmallShadow()
	{
		sprite->SetSize(kSmallShadowSize);
		this->game_object_->transform_ = player_object_->transform_;

		// 矩形の当たり判定の設定
		BoxCollider *collider = game_object_->GetComponent<BoxCollider>();

		BoxInitializer box_init;
		box_init.width_ = kSmallShadowSize.x;
		box_init.height_ = kSmallShadowSize.y;
		box_init.body_type_ = kDynamicBody;
		box_init.pos_ = game_object_->transform_->position_;

		collider->ReSet(box_init);
	}

	void Shadow::CreateMiddleShadow()
	{
		sprite->SetSize(kMiddleShadowSize);
		this->game_object_->transform_ = player_object_->transform_;

		// 矩形の当たり判定の設定
		BoxCollider *collider = game_object_->GetComponent<BoxCollider>();

		BoxInitializer box_init;
		box_init.width_ = kMiddleShadowSize.x;
		box_init.height_ = kMiddleShadowSize.y;
		box_init.body_type_ = kDynamicBody;
		box_init.pos_ = game_object_->transform_->position_;

		collider->ReSet(box_init);
	}

	void Shadow::CreateLargeShadow()
	{
		sprite->SetSize(kLargeShadowSize);
		this->game_object_->transform_ = player_object_->transform_;

		// 矩形の当たり判定の設定
		BoxCollider *collider = game_object_->GetComponent<BoxCollider>();

		BoxInitializer box_init;
		box_init.width_ = kLargeShadowSize.x;
		box_init.height_ = kLargeShadowSize.y;
		box_init.body_type_ = kDynamicBody;
		box_init.pos_ = game_object_->transform_->position_;

		collider->ReSet(box_init);
	}

}	// namespace shadowpartner
