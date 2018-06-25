//==========================================================
// 概要  :シャドウステート
// Author:Ittoto
// Copyright(c) Utsurugi.All right reserved.
//==========================================================

#ifndef _GAME_ACTOR_PLAYER_SHADOWSTATE_H_
#define _GAME_ACTOR_PLAYER_SHADOWSTATE_H_

#include "../Common/actor_state.h"

namespace shadowpartner
{
	class GameObject;

	class ShadowState : public ActorState
	{
	public:
		ShadowState(Actor *owner);

	protected:
		virtual void ExecuteState() override;

	private:

	};

}	// namespace shadowpartner

#endif