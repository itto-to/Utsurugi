//==========================================================
// 概要  :スリープステート
// Author:Ittoto
// Copyright(c) Utsurugi.All right reserved.
//==========================================================
#ifndef _GAME_ACTOR_PLAYER_SLEEPSTATE_H_
#define _GAME_ACTOR_PLAYER_SLEEPSTATE_H_

#include "../Common/actor_state.h"


namespace shadowpartner
{
	class SleepState : public ActorState
	{
	public:
		SleepState(Actor *owner);
		void Enter() override;
		virtual void ExecuteState() override;

	protected:


	private:

	};

}	// namespace shadowpartner
#endif // !_GAME_ACTOR_PLAYER_SLEEPSTATE_H_