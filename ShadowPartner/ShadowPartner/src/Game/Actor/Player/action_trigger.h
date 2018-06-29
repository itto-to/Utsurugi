//==========================================================
// �T�v  :�M�~�b�N�ւ̃A�N�V�����p�g���K�[
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

		void SetOffset(const Vector2 &offset);	// �E�������I�t�Z�b�g���Z�b�g

	protected:
		std::vector<GameObject*> gimmick_objects_;
		Actor *actor_;

		Vector2 offset_facing_right_;	// �E�������I�t�Z�b�g
	};
}

#endif