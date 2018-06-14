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
		void Start() override;
		void CreateShadow(ShadowSize size);

	protected:
		Sprite *sprite;

	private:
		physics::BoxCollider *collider;
	};

}	// namespace shadowpartner

#endif