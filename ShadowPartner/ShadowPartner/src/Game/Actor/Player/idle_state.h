#ifndef _GAME_ACTOR_PLAYER_IDLESTATE_H_
#define _GAME_ACTOR_PLAYER_IDLESTATE_H_

#include "../Common/actor_state.h"

namespace shadowpartner
{
	class IdleState : public ActorState {
	public:
		IdleState(Actor *owner) : ActorState(owner){};
		void Execute() override;
	};
}

#endif