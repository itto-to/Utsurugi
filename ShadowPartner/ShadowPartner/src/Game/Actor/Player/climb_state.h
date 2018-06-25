//==========================================================
// �T�v  :�o��X�e�[�g
// Author:Ittoto
// Copyright(c) Utsurugi.All right reserved.
//==========================================================
#ifndef _GAME_ACTOR_PLAYER_CLIMBSTATE_H_
#define _GAME_ACTOR_PLAYER_CLIMBSTATE_H_

#include "../Common/actor_state.h"

namespace physics
{
	class Collider;
}

namespace shadowpartner
{
	class Player;
	class Actor;
	class Movable;

	class ClimbState : public ActorState
	{
	public:
		ClimbState(Actor *owner);
		void ClimbState::Enter() override;
		void ClimbState::ExecuteState() override;
		void ClimbState::Exit() override;

	protected:
		Player *player_;
		Movable *movable_;
		physics::Collider *collider_;
		float old_gravity_scale_;		// ���Ƃ̏d�̓X�P�[��
	};

}	// namespace shadowpartner

#endif