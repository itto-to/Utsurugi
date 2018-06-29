//==========================================================
// 概要  :プレイヤーコンポーネント
// Author:Ittoto
// Copyright(c) Utsurugi.All right reserved.
//==========================================================

#include "player.h"
#include "idle_state.h"
#include "landing_trigger.h"
#include "gimmck_trigger.h"
#include "sleep_state.h"
#include "../../../Base/2D/sprite.h"
#include "shadow.h"
#include "../../../Base/Physics/Element/collider.h"

#ifdef _DEBUG
#include "../../../Base/Physics/Debug/debug_draw.h"
#endif

using namespace physics;

namespace shadowpartner
{

	Player::Player()
	{
		state_ = new IdleState(this);
	}

	Player::Player(ActorState* state) : 
		Actor(state)
	{
	}

	Player::~Player()
	{
		delete state_;
		state_ = nullptr;
	}

	void Player::Start()
	{
		gimmick_trigger_ = game_object_->GetComponent<GimmickTrigger>();

		state_->Enter();
	}

	void Player::Update()
	{
		state_->Execute();

		SetShadowSize();	

		// リスポーン
		if (transform_->position_.y < -10.0f)
			Respawn();
	}

	void Player::SetShadowSize()
	{
		Shadow *shadow = shadow_object_->GetComponent<Shadow>();

		LightType light_type = gimmick_trigger_->HittingLightType();

		switch (light_type)
		{
		case kLarge:
			shadow->SetShadowSize(Shadow::ShadowSize::kLargeShadow);
			break;
		case kMiddle:
			shadow->SetShadowSize(Shadow::ShadowSize::kMiddleShadow);
			break;
		case kSmall:
			shadow->SetShadowSize(Shadow::ShadowSize::kSmallShadow);
			break;
		case kLightNone:
			shadow->SetShadowSize(Shadow::ShadowSize::kMiddleShadow);
			break;
		default:
			break;
		}
	}

	void Player::CreateShadow()
	{
		LightType light_type = gimmick_trigger_->HittingLightType();

		switch (light_type)
		{
		case kLarge:
			shadow_object_->GetComponent<Shadow>()->CreateLargeShadow();
			SetControllable(false);
			break;
		case kMiddle:
			shadow_object_->GetComponent<Shadow>()->CreateMiddleShadow();
			SetControllable(false);
			break;
		case kSmall:
			shadow_object_->GetComponent<Shadow>()->CreateSmallShadow();
			SetControllable(false);
			break;
		case kLightNone:
			return;
		}
		//shadow_object_->GetComponentInherit<Collider>()->SetActive(true);

		is_controllable_ = false;
		ChangeState(new SleepState(this));
	}

	void Player::SetRespawnPoint(Vector2 respawn_point)
	{
		respawn_point_ = respawn_point;
	}

	Vector2 Player::RespawnPoint()
	{
		return respawn_point_;
	}

	void Player::Respawn()
	{
		game_object_->transform_->position_ = respawn_point_;
	}
}