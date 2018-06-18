//==========================================================
// 概要  :シャドウコンポーネント
// Author:Ittoto
// Copyright(c) Utsurugi.All right reserved.
//==========================================================

#ifndef _GAME_ACTOR_PLAYER_SHADOW_H_
#define _GAME_ACTOR_PLAYER_SHADOW_H_

#include "../Common/actor.h"
#include "../Common/actor_state.h"

namespace physics
{
	class BoxCollider;
}

namespace shadowpartner
{
	class Sprite;

	class Shadow : public Actor
	{
	public:
		enum ShadowSize
		{
			kLargeShadow,
			kMiddleShadow,
			kSmallShadow,
		};

		Shadow();
		Shadow(ActorState* state);
		virtual ~Shadow();

		// methods
		void Start() override;
		void SetShadowSize(ShadowSize shadow_size);
		void CreateSmallShadow();
		void CreateMiddleShadow();
		void CreateLargeShadow();
	public:
		GameObject *player_object_;

	protected:
		Sprite *sprite;

	private:
		physics::BoxCollider *collider;
	};

}	// namespace shadowpartner

#endif