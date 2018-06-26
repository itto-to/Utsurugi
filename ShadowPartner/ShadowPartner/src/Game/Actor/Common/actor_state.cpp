//==========================================================
// 概要  :アクターステート基底クラス
// Author:Ittoto
// Copyright(c) Utsurugi.All right reserved.
//==========================================================

#include "actor_state.h"

#include "actor.h"

namespace shadowpartner {

	ActorState::ActorState(Actor *owner) :
		owner_(owner),
		counter_(0)
	{
	}

	ActorState::~ActorState()
	{
		Exit();
	}

	void ActorState::Execute()
	{
		ExecuteState();
		counter_++;
	}

} // namespace shadowpartner