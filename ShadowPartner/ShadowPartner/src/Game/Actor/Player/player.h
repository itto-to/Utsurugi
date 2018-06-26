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

	class Player : public Actor
	{
	public:
		enum LightType {
			LargeLight,
			MiddleLight,
			SmallLight,
			LightNone,
		};

		Player();
		Player(ActorState *state);
		virtual ~Player();

		// methods
		void CreateShadow();
		bool CanClimb();

		// variables
		physics::Collider *landing_trigger_;
		GameObject *shadow_;

	protected:

		// variables
		int hit_large_light;
		int hit_middle_light;
		int hit_small_light;
		int hit_climb;
		LightType light_;

		// methods
		void Start() override;
		void Update() override;
		void SetShadowSize();

	private:

	};

}	// namespace shadowpartner

#endif