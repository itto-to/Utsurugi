//==========================================================
// �T�v  :�X���[�v�X�e�[�g
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
		debug::Debug::Log("�v���C���[�̏�ԁF�X���[�v");
#endif
	}

	void SleepState::ExecuteState()
	{

	}

}