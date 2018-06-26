//==========================================================
// 概要  :シャドウコンポーネント
// Author:Ittoto
// Copyright(c) Utsurugi.All right reserved.
//==========================================================

#ifndef _GAME_ACTOR_PLAYER_SHADOW_H_
#define _GAME_ACTOR_PLAYER_SHADOW_H_

#include "../Common/actor.h"
#include "../Common/actor_state.h"
#include "../../../Base/Physics/Element/contact_listener.h"

namespace physics
{
	class BoxCollider;
}

namespace shadowpartner
{
	class Player;
	class Sprite;
	class Jumper;

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
		void Update() override;

		void SetShadowSize(ShadowSize shadow_size);
		void CreateSmallShadow();
		void CreateMiddleShadow();
		void CreateLargeShadow();
		void ReturnToPlayerShadow();
		bool IsHitLight();
		void SetPlayerObject(GameObject *player_object);
		GameObject *GetPlayerObject();

	protected:

		// variable
		GameObject *player_object_;
		Sprite *sprite_;
		physics::BoxCollider *collider_;
		Jumper *jumper_;

		int hit_large_light_;
		int hit_middle_light_;
		int hit_small_light_;

	private:

	};

}	// namespace shadowpartner

#endif