//==========================================================
// 概要  :アクターコンポーネント
// Author:Ittoto
// Copyright(c) Utsurugi.All right reserved.
//==========================================================

#include "actor.h"

namespace shadowpartner {

	Actor::Actor() : state_(nullptr), is_controllable_(true) {}

	Actor::Actor(ActorState* state) : state_(state) , is_controllable_(true) {}

	Actor::~Actor()
	{
		delete state_;
		state_ = nullptr;
	}

	void Actor::SetState(ActorState *state)
	{
		state_ = state;
	}

	void Actor::ChangeState(ActorState *state)
	{
		// 現在のステートをdelete
		delete state_;
		state_ = nullptr;

		state_ = state;
	}

	bool Actor::IsControllable()
	{
		return is_controllable_;
	}

	void Actor::SetIsControllable(bool is_controllable)
	{
		is_controllable_ = is_controllable;
	}

	void Actor::Update()
	{
		state_->Execute();
	}

}