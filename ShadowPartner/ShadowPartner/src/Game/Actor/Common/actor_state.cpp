//==========================================================
// �T�v  :�A�N�^�[�X�e�[�g���N���X
// Author:Ittoto
// Copyright(c) Utsurugi.All right reserved.
//==========================================================
#include "actor_state.h"

#include "actor.h"

namespace shadowpartner {

	ActorState::ActorState(Actor *owner) : owner_(owner)
	{
		Enter();
	}

	ActorState::~ActorState()
	{
		Exit();
	}

} // namespace shadowpartner