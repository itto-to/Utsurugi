//==========================================================
// 概要  :プレイヤーコンポーネント
// Author:Ittoto
// Copyright(c) Utsurugi.All right reserved.
//==========================================================

#ifndef _GAME_ACTOR_PLAYER_PLAYER_H_
#define _GAME_ACTOR_PLAYER_PLAYER_H_

#include "../Common/actor.h"
#include "../../../../liquidfun_include/Box2D/Box2D.h"

#include "../../../Base/Physics/Element/contact_listener.h"

namespace physics
{
	class Collider;
}

namespace shadowpartner
{
	class GimmickTrigger;
	class ActionTrigger;

	class Player : public Actor
	{
	public:

		Player();
		Player(ActorState *state);
		virtual ~Player();

		// methods
		void CreateShadow();
		void SetRespawnPoint(Vector2 respawn_point);
		Vector2 RespawnPoint();
		void Respawn();

		// variables
		physics::Collider *landing_trigger_;
		GameObject *shadow_object_;

	protected:

		// variables
		Vector2 respawn_point_;

		GimmickTrigger *gimmick_trigger_;
		ActionTrigger *action_trigger_;

		// methods
		void Start() override;
		void Update() override;
		void SetShadowSize();


	private:

	};

}	// namespace shadowpartner

#endif