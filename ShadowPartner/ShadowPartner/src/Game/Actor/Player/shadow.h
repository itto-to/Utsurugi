//==========================================================
// 概要  :シャドウコンポーネント
// Author:Ittoto
// Copyright(c) Utsurugi.All right reserved.
//==========================================================

#ifndef _GAME_ACTOR_PLAYER_SHADOW_H_
#define _GAME_ACTOR_PLAYER_SHADOW_H_

#include "../Common/actor.h"
#include "../Common/actor_state.h"

namespace shadowpartner
{
	class Player;

	class Shadow : public Actor
	{
	public:
		Shadow();
		Shadow(ActorState* state);
		virtual ~Shadow();

	protected:


	private:

	};

}	// namespace shadowpartner

#endif