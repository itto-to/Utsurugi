//==========================================================
// 概要  :アクターコンポーネント
// Author:Ittoto
// Copyright(c) Utsurugi.All right reserved.
//==========================================================
#include "actor.h"

namespace shadowpartner {

	Actor::Actor() : state_(nullptr) {}

	Actor::Actor(ActorState* state) : state_(state) {}

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

	void Actor::Update()
	{
		state_->Execute();
	}

}