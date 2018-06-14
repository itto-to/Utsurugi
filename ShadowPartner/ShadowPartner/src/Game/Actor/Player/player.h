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

namespace shadowpartner
{

	class Player : public Actor, public physics::ContactListener
	{
	public:
		enum LightSize {
			LargeLight,
			MiddleLight,
			SmallLight,
			LightNone,
		};

		Player();
		Player(ActorState *state);
		virtual ~Player();

	protected:

		// variables
		int hit_large_light;
		int hit_middle_light;
		int hit_small_light;
		LightSize light_;

		// methods
		void Update() override;
		void BeginContact(b2Contact *contact) override;
		void EndContact(b2Contact * contact) override;

	private:

	};

}	// namespace shadowpartner

#endif