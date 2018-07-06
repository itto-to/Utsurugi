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


	const Vector2 kMiddleShadowSize = Vector2(2.0f, 1.0f);

	const float kSmallShadowScale = 0.5f;
	const float kLargeShadowScale = 2.0f;

	const Vector2 kSmallShadowSize = kMiddleShadowSize * kSmallShadowScale;
	const Vector2 kLargeShadowSize = kMiddleShadowSize * kLargeShadowScale;

	const float kShadowCollisionScale = 0.75f;

	const Vector2 kMiddleShadowCollisionSize = kMiddleShadowSize * kShadowCollisionScale;
	const Vector2 kLargeShadowCollisionSize = kLargeShadowSize * kShadowCollisionScale;
	const Vector2 kSmallShadowCollisionSize = kSmallShadowSize * kShadowCollisionScale;


namespace physics
{
	class BoxCollider;
}

namespace shadowpartner
{
	class Player;
	class LandingTrigger;
	class GimmickTrigger;
	class ActionTrigger;
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
		void CreateShadow();
		void CreateSmallShadow();
		void CreateMiddleShadow();
		void CreateLargeShadow();
		void ReturnToPlayerShadow();
		void SetPlayerObject(GameObject *player_object);
		GameObject *GetPlayerObject();

	protected:

		// variable
		GameObject *player_object_;
		Sprite *sprite_;
		physics::BoxCollider *collider_;
		LandingTrigger *land_trigger_;
		GimmickTrigger *gimmick_trigger_;
		ActionTrigger *action_trigger_;
		Jumper *jumper_;

		bool is_shadow_state_;

	private:

	};

}	// namespace shadowpartner

#endif