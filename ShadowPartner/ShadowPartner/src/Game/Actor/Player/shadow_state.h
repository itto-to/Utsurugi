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
	class GimmickTrigger;

	class ShadowState : public ActorState
	{
	public:
		ShadowState(Actor *owner);

	protected:
		void Enter() override;
		virtual void ExecuteState() override;
		Player *player_;
		physics::Collider *collider_;
		GimmickTrigger *player_gimmick_trigger_;
	};

}	// namespace shadowpartner

#endif