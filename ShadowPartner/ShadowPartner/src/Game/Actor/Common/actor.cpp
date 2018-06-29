//==========================================================
// 概要  :アクターコンポーネント
// Author:Ittoto
// Copyright(c) Utsurugi.All right reserved.
//==========================================================
#include "actor.h"

namespace shadowpartner {

	Actor::Actor() :
		state_(nullptr),
		is_controllable_(true),
		direction_(kRight),
		old_direction_(kRight)
	{
	}

	Actor::Actor(ActorState* state) :
		state_(state),
		is_controllable_(true),
		direction_(kRight),
		old_direction_(kRight)
	{
	}

	Actor::~Actor()
	{
		delete state_;
		state_ = nullptr;
	}

	void Actor::Start()
	{
	}

	void Actor::SetState(ActorState *state)
	{
		state_ = state;
	}

	void Actor::ChangeState(ActorState *state)
	{
		state_->Exit();
		// 現在のステートをdelete
		delete state_;
		state_ = nullptr;

		state_ = state;
		state_->Enter();
	}

	bool Actor::IsControllable() const
	{
		return is_controllable_;
	}

	void Actor::SetControllable(bool is_controllable)
	{
		is_controllable_ = is_controllable;
	}

	ActorDirection Actor::GetDirection() const
	{
		return direction_;
	}

	void Actor::SetDirection(ActorDirection direction)
	{
		direction_ = direction;
	}

	int Actor::StateCounter()
	{
		return state_->StateCounter();
	}

	void Actor::Update()
	{
		old_direction_ = direction_;
		state_->Execute();
	}

	bool Actor::HasChangedDirection() const
	{
		return direction_ != old_direction_;
	}

}