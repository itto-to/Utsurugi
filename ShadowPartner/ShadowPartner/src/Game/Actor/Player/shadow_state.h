//==========================================================
// 概要  :シャドウステート
// Author:Ittoto
// Copyright(c) Utsurugi.All right reserved.
//==========================================================

#ifndef _GAME_ACTOR_PLAYER_SHADOWSTATE_H_
#define _GAME_ACTOR_PLAYER_SHADOWSTATE_H_

#include "../Common/actor_state.h"

namespace physics
{
	class Collider;
}

namespace shadowpartner
{
	class GameObject;
	class Player;

	class ShadowState : public ActorState
	{
	public:
		ShadowState(Actor *owner);

	protected:
		virtual void ExecuteState() override;
		Player *player_;
		physics::Collider *collider_;
	};

}	// namespace shadowpartner

#endif