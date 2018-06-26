//==========================================================
// 概要  :スリープステート
// Author:Ittoto
// Copyright(c) Utsurugi.All right reserved.
//==========================================================
#include "sleep_state.h"

#ifdef _DEBUG
#include "../../../Base/Debug/debugger.h"
#endif


namespace shadowpartner
{

	SleepState::SleepState(Actor *owner) : ActorState(owner)
	{
	}

	void SleepState::Enter()
	{
#ifdef _DEBUG
		debug::Debug::Log("プレイヤーの状態：スリープ");
#endif
	}

	void SleepState::ExecuteState()
	{

	}

}