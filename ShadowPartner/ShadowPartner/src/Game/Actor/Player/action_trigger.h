//==========================================================
// 概要  :ギミックへのアクション用トリガー
// Author:Ittoto
// Copyright(c) Utsurugi.All right reserved.
//==========================================================
#ifndef _GAME_ACTOR_PLAYER_ACTIONTRIGGER_H_
#define _GAME_ACTOR_PLAYER_ACTIONTRIGGER_H_

#include "../../../Base/Physics/Element/box_collider.h"

namespace shadowpartner
{
	class Actor;

	class ActionTrigger : public physics::BoxCollider
	{
	public:
		ActionTrigger(const physics::BoxInitializer &box_init);

		void Update() override;
		void OnTriggerEnter(Collider *col) override;
		void OnTriggerExit(Collider *col) override;
		
		void Activate();

		void SetOffset(const Vector2 &offset);	// 右向き時オフセットをセット

	protected:
		std::vector<GameObject*> gimmick_objects_;
		Actor *actor_;

		Vector2 offset_facing_right_;	// 右向き時オフセット
	};
}

#endif