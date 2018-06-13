//==========================================================
// 概要  :プレイヤーコンポーネント
// Author:Ittoto
// Copyright(c) Utsurugi.All right reserved.
//==========================================================

#include "player.h"

#include "../../../Base/2D/sprite.h"

namespace shadowpartner
{

	Player::Player() : 
		hit_large_light(0),
		hit_middle_light(0),
		hit_small_light(0)
	{
	}

	Player::Player(ActorState* state) : 
		Actor(state),
		hit_large_light(0),
		hit_middle_light(0),
		hit_small_light(0)
	{
	}

	Player::~Player()
	{
		delete state_;
		state_ = nullptr;
	}

	void Player::BeginContact(b2Contact *contact)
	{
		Component *comp_a = static_cast<Component*>(contact->GetFixtureA()->GetBody()->GetUserData());
		Component *comp_b = static_cast<Component*>(contact->GetFixtureB()->GetBody()->GetUserData());

		if (comp_a == nullptr || comp_b == nullptr)
			return;

		GameObject *other = nullptr;
		if (comp_a->game_object_ == this->game_object_)
		{
			other = comp_b->game_object_;
		}
		else if (comp_b->game_object_ == this->game_object_)
		{
			other = comp_a->game_object_;
		}

		// 範囲内になったライトの数をプラス
		if (other->tag_ == kLargeLight)
		{
			hit_large_light++;
		}
		else if (other->tag_ == kMiddleLight)
		{
			hit_middle_light++;
		}
		else if (other->tag_ == kSmallLight)
		{
			hit_small_light++;
		}
	}

	void Player::EndContact(b2Contact *contact)
	{
		Component *comp_a = static_cast<Component*>(contact->GetFixtureA()->GetBody()->GetUserData());
		Component *comp_b = static_cast<Component*>(contact->GetFixtureB()->GetBody()->GetUserData());

		if (comp_a == nullptr || comp_b == nullptr)
			return;

		GameObject *other = nullptr;
		if (comp_a->game_object_ == this->game_object_)
		{
			other = comp_b->game_object_;
		}
		else if (comp_b->game_object_ == this->game_object_)
		{
			other = comp_a->game_object_;
		}

		// 範囲外になったライトの数をマイナス
		if (other->tag_ == kLargeLight)
		{
			hit_large_light--;
		}
		else if (other->tag_ == kMiddleLight)
		{
			hit_middle_light--;
		}
		else if (other->tag_ == kSmallLight)
		{
			hit_small_light--;
		}
	}

	void Player::Update()
	{
		state_->Execute();
	}
}