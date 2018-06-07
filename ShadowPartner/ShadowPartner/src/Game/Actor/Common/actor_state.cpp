//==========================================================
// 概要  :アクターステート基底クラス
// Author:Ittoto
// Copyright(c) Utsurugi.All right reserved.
//==========================================================
#include "actor_state.h"

#include "actor.h"

namespace shadowpartner {

	ActorState::ActorState(Actor *owner) : owner_(owner) {}

} // namespace shadowpartner