//==========================================================
// �T�v  :�A�N�^�[�R���|�[�l���g
// Author:Ittoto
// Copyright(c) Utsurugi.All right reserved.
//==========================================================

#ifndef _GAME_ACTOR_COMMON_ACTOR_H_
#define _GAME_ACTOR_COMMON_ACTOR_H_

#include "../../../Base/Element/component.h"
#include "../../Actor/Common/actor_state.h"

namespace shadowpartner {

	class Actor : public Component {
	public:
		enum ActorDirection
		{
			kRight,
			kLeft
		};

		Actor();
		Actor(ActorState* state);
		virtual ~Actor();

		// methods
		void SetState(ActorState *state);
		void ChangeState(ActorState *next_state);
		bool IsControllable();
		void SetControllable(bool is_controllable);
		ActorDirection GetDirection();
		void SetDirection(ActorDirection direction);

	protected:

		// methods
		void Update() override;

		// variables
		ActorState *state_;
		bool is_controllable_;	// ����\���ǂ���
		ActorDirection direction_;	// �L�����N�^�[�̌���

	private:

	};

}

#endif 