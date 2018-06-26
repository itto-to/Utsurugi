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
#include "../../../Base/Input/input.h"

using namespace physics;

namespace shadowpartner
{
	namespace
	{
		const Vector2 kSmallShadowSize = Vector2(0.5f, 0.5f);
		const Vector2 kMiddleShadowSize = Vector2(1.0f, 1.0f);
		const Vector2 kLargeShadowSize = Vector2(2.0f, 2.0f);
	}

	Shadow::Shadow() :
		hit_large_light_(0),
		hit_middle_light_(0),
		hit_small_light_(0)
	{
		is_controllable_ = false;
	}

	Shadow::Shadow(ActorState* state) : Actor(state), 
		hit_large_light_(0),
		hit_middle_light_(0),
		hit_small_light_(0)
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
		sprite_ = game_object_->GetComponent<Sprite>();
		collider_ = game_object_->GetComponent<physics::BoxCollider>();
		jumper_ = game_object_->GetComponent<Jumper>();
	}

	void Shadow::Update()
	{
		state_->Execute();

		// 光に当たっていないかもう一度ボタンを押すとプレイヤーの元に戻る
		if (!IsHitLight() || input::Input::Instance()->GetButtonDown(input::Attack))
		{
			ReturnToPlayerShadow();
		}
	}

	//void Shadow::BeginContact(b2Contact *contact)
	//{
 //		Component *comp_a = static_cast<Component*>(contact->GetFixtureA()->GetBody()->GetUserData());
	//	Component *comp_b = static_cast<Component*>(contact->GetFixtureB()->GetBody()->GetUserData());

	//	if (comp_a == nullptr || comp_b == nullptr)
	//		return;

	//	GameObject *other = nullptr;
	//	if (comp_a->game_object_ == this->game_object_)
	//	{
	//		other = comp_b->game_object_;

	//	}
	//	else if (comp_b->game_object_ == this->game_object_)
	//	{
	//		other = comp_a->game_object_;
	//	}
	//	else {
	//		return;
	//	}

	//	// 範囲内になったライトの数をプラス
	//	if (other->tag_ == kLargeLight)
	//	{
	//		hit_large_light_++;
	//	}
	//	else if (other->tag_ == kMiddleLight)
	//	{
	//		hit_middle_light_++;
	//	}
	//	else if (other->tag_ == kSmallLight)
	//	{
	//		hit_small_light_++;
	//	}
	//}

	//void Shadow::EndContact(b2Contact *contact)
	//{
	//	Component *comp_a = static_cast<Component*>(contact->GetFixtureA()->GetBody()->GetUserData());
	//	Component *comp_b = static_cast<Component*>(contact->GetFixtureB()->GetBody()->GetUserData());

	//	if (comp_a == nullptr || comp_b == nullptr)
	//		return;

	//	GameObject *other = nullptr;
	//	if (comp_a->game_object_ == this->game_object_)
	//	{
	//		other = comp_b->game_object_;
	//	}
	//	else if (comp_b->game_object_ == this->game_object_)
	//	{
	//		other = comp_a->game_object_;
	//	}
	//	else
	//	{
	//		return;
	//	}

	//	// 範囲外になったライトの数をマイナス
	//	if (other->tag_ == kLargeLight)
	//	{
	//		hit_large_light_--;
	//	}
	//	else if (other->tag_ == kMiddleLight)
	//	{
	//		hit_middle_light_--;
	//	}
	//	else if (other->tag_ == kSmallLight)
	//	{
	//		hit_small_light_--;
	//	}
	//}

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
		sprite_->SetSize(kSmallShadowSize);
		*game_object_->transform_ = *player_object_->transform_;
		game_object_->transform_->position_ += Vector2(0.0f, 5.0f);

		// 待機状態に
		ChangeState(new IdleState(this));
		// 操作可能に
		SetControllable(true);
		// ジャンプ設定
		jumper_->SetCanJump(true);

		// 矩形の当たり判定の設定
		BoxInitializer box_init;
		box_init.width_ = kSmallShadowSize.x;
		box_init.height_ = kSmallShadowSize.y;
		box_init.bounciness_ = 0.0f;
		box_init.category_bits_ = CollisionFilter::kShadow;
		box_init.mask_bits_ = ~CollisionFilter::kPlayer;
		box_init.body_type_ = kDynamicBody;
		box_init.pos_ = game_object_->transform_->position_;

		collider_->ReSet(box_init);

		// 当たり判定オン
		collider_->SetActive(true);
	}

	void Shadow::CreateMiddleShadow()
	{
		sprite_->SetSize(kMiddleShadowSize);
		*game_object_->transform_ = *player_object_->transform_;
		game_object_->transform_->position_ += Vector2(0.0f, 5.0f);

		// 待機状態に
		ChangeState(new IdleState(this));
		// 操作可能に
		SetControllable(true);
		// ジャンプ設定
		jumper_->SetCanJump(false);

		// 矩形の当たり判定の設定
		BoxInitializer box_init;
		box_init.width_ = kMiddleShadowSize.x;
		box_init.height_ = kMiddleShadowSize.y;
		box_init.bounciness_ = 0.0f;
		box_init.category_bits_ = CollisionFilter::kShadow;
		box_init.mask_bits_ = ~CollisionFilter::kPlayer;
		box_init.body_type_ = kDynamicBody;
		box_init.pos_ = game_object_->transform_->position_;

		collider_->ReSet(box_init);
		// 当たり判定オン
		collider_->SetActive(true);
	}

	void Shadow::CreateLargeShadow()
	{
		sprite_->SetSize(kLargeShadowSize);
		*game_object_->transform_ = *player_object_->transform_;

		// 待機状態に
		ChangeState(new IdleState(this));
		// 操作可能に
		SetControllable(true);
		// ジャンプ設定
		jumper_->SetCanJump(false);

		// 矩形の当たり判定の設定
		BoxInitializer box_init;
		box_init.pos_ = this->transform_->position_;
		box_init.width_ = kLargeShadowSize.x;
		box_init.height_ = kLargeShadowSize.y;
		box_init.bounciness_ = 0.0f;
		box_init.category_bits_ = CollisionFilter::kShadow;
		box_init.mask_bits_ = ~CollisionFilter::kPlayer;
		box_init.body_type_ = kDynamicBody;
		box_init.pos_ = game_object_->transform_->position_;

		collider_->ReSet(box_init);

		// 当たり判定オン
		collider_->SetActive(true);
	}

	void Shadow::ReturnToPlayerShadow()
	{
		sprite_->SetSize(kMiddleShadowSize);
		game_object_->transform_->position_ = player_object_->transform_->position_ - Vector2(0.0f, kMiddleShadowSize.y);
		
		// 当たり判定オフ
		collider_->SetActive(false);

		// 影状態に戻る
		ChangeState(new ShadowState(this));
	}

	bool Shadow::IsHitLight()
	{
		if (hit_large_light_ > 0)
			return false;
		if (hit_middle_light_ > 0)
			return false;
		if (hit_small_light_ > 0)
			return false;

		return true;
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
