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
		switch (shadow_size) {
		case kSmallShadow:
			sprite->SetSize(Vector2(50, 50));
			break;

		case kMiddleShadow:
			sprite->SetSize(Vector2(100, 100));
			break;

		case kLargeShadow:
			sprite->SetSize(Vector2(200, 200));
			break;
		}

	}

	void Shadow::CreateSmallShadow()
	{
		sprite->SetSize(Vector2(50, 50));
		this->game_object_->transform_ = player_object_->transform_;

		// 矩形の当たり判定の設定
		BoxCollider *collider = game_object_->GetComponent<BoxCollider>();

		BoxInitializer box_init;
		box_init.width_ = 50.0f;
		box_init.height_ = 50.0f;
		box_init.body_type_ = kDynamicBody;
		box_init.pos_ = game_object_->transform_->position_;

		collider->ReSet(box_init);
	}

	void Shadow::CreateMiddleShadow()
	{
		sprite->SetSize(Vector2(100, 100));
		this->game_object_->transform_ = player_object_->transform_;

		// 矩形の当たり判定の設定
		BoxCollider *collider = game_object_->GetComponent<BoxCollider>();

		BoxInitializer box_init;
		box_init.width_ = 100.0f;
		box_init.height_ = 100.0f;
		box_init.body_type_ = kDynamicBody;
		box_init.pos_ = game_object_->transform_->position_;

		collider->ReSet(box_init);
	}

	void Shadow::CreateLargeShadow()
	{
		sprite->SetSize(Vector2(200, 200));
		this->game_object_->transform_ = player_object_->transform_;

		// 矩形の当たり判定の設定
		BoxCollider *collider = game_object_->GetComponent<BoxCollider>();

		BoxInitializer box_init;
		box_init.width_ = 200.0f;
		box_init.height_ = 200.0f;
		box_init.body_type_ = kDynamicBody;
		box_init.pos_ = game_object_->transform_->position_;

		collider->ReSet(box_init);
	}

}	// namespace shadowpartner
