//==========================================================
// �T�v  :�A�N�^�[�X�e�[�g���N���X
// Author:Ittoto
// Copyright(c) Utsurugi.All right reserved.
//==========================================================
#ifndef _GAME_ACTOR_COMMON_ACTORSTATE_H_
#define _GAME_ACTOR_COMMON_ACTORSTATE_H_

namespace shadowpartner
{
	class Actor;

	class ActorState
	{
	public:
		ActorState(Actor *owner);
		virtual ~ActorState();
		virtual void Execute() {}
		virtual void Enter() {}
		virtual void Exit() {}

	protected:
		Actor *owner_;	// �X�e�[�g�̏��L�R���|�[�l���g
	private:
	};
}

#endif 