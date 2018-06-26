//==========================================================
// 概要  :プレイヤーコンポーネント
// Author:Ittoto
// Copyright(c) Utsurugi.All right reserved.
//==========================================================

#include "player.h"
#include "idle_state.h"
#include "landing_trigger.h"
#include "sleep_state.h"
#include "../../../Base/2D/sprite.h"
#include "shadow.h"

#ifdef _DEBUG
#include "../../../Base/Physics/Debug/debug_draw.h"
#endif

namespace shadowpartner
{

	Player::Player() : 
		hit_large_light(0),
		hit_middle_light(0),
		hit_small_light(0),
		hit_climb(0)
	{
		state_ = new IdleState(this);
	}

	Player::Player(ActorState* state) : 
		Actor(state),
		hit_large_light(0),
		hit_middle_light(0),
		hit_small_light(0),
		hit_climb(0)
	{
	}

	Player::~Player()
	{
		delete state_;
		state_ = nullptr;
	}

	void Player::Start()
	{
		state_->Enter();
	}

	void Player::Update()
	{
		state_->Execute();
		SetShadowSize();	
	}

	void Player::SetShadowSize()
	{
		Shadow *shadow = shadow_->GetComponent<Shadow>();
		if (hit_small_light > 0)
		{
			shadow->SetShadowSize(Shadow::ShadowSize::kSmallShadow);
		}
		else if (hit_middle_light > 0) 
		{
			shadow->SetShadowSize(Shadow::ShadowSize::kMiddleShadow);
		}
		else if (hit_large_light > 0)
		{
			shadow->SetShadowSize(Shadow::ShadowSize::kLargeShadow);
		}
		else
		{
			shadow->SetShadowSize(Shadow::ShadowSize::kMiddleShadow);
		}
	}

	void Player::CreateShadow()
	{
		if (hit_small_light > 0)
		{
			shadow_->GetComponent<Shadow>()->CreateSmallShadow();
			SetControllable(false);
		}
		else if (hit_middle_light > 0)
		{
			shadow_->GetComponent<Shadow>()->CreateMiddleShadow();
			SetControllable(false);
		}
		else if (hit_large_light > 0)
		{
			shadow_->GetComponent<Shadow>()->CreateLargeShadow();
			SetControllable(false);
		}
		else
		{
			return;
		}

		ChangeState(new SleepState(this));
		is_controllable_ = false;
	}

	bool Player::CanClimb()
	{
		return hit_climb > 0;
	}
}