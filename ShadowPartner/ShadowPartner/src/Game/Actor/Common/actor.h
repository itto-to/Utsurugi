//==========================================================
// �T�v  :�A�N�^�[�R���|�[�l���g
// Author:Ittoto
// Copyright(c) Utsurugi.All right reserved.
//==========================================================

#ifndef _GAME_ACTOR_COMMON_ACTOR_H_
#define _GAME_ACTOR_COMMON_ACTOR_H_

#include "../../../Base/Element/component.h"
#include "../../Actor/Common/actor_state.h"

namespace physics
{
	class Collider;
}

namespace shadowpartner {

	enum ActorDirection
	{
		kRight,
		kLeft
	};

	class Player;
	class Shadow;
	class Jumper;
	class LandingTrigger;
	class GimmickTrigger;
	class ActionTrigger;
	
	class Actor : public Component {
	public:

		Actor();
		Actor(ActorState* state);
		virtual ~Actor();
		void Start() override;

		// methods
		void SetState(ActorState *state);
		void ChangeState(ActorState *next_state);
		bool IsControllable() const;
		void SetControllable(bool is_controllable);
		ActorDirection GetDirection() const;
		void SetDirection(ActorDirection direction);
		bool HasChangedDirection() const;
		int StateCounter();

	protected:

		// methods
		void Update() override;

		// variables
		Player *player_;
		Shadow *shadow_;
		Jumper *jumper_;
		LandingTrigger *landing_trigger_;
		GimmickTrigger *gimmick_trigger_;
		ActionTrigger *action_trigger_;

		physics::Collider *collider_;

		ActorState *state_;
		bool is_controllable_;			// ����\���ǂ���
		ActorDirection direction_;		// �A�N�^�[�̌���
		ActorDirection old_direction_;	// �A�N�^�[�̑O�t���[���̌���

	private:

	};

}

#endif 