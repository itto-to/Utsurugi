//==========================================================
// 概要  :アクターコンポーネント
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
		Actor();
		Actor(ActorState* state);
		virtual ~Actor();

		// methods
		void SetState(ActorState *state);
		void ChangeState(ActorState *next_state);
		bool IsControllable();
		void SetIsControllable(bool is_controllable);

	protected:

		// methods
		void Update() override;

		// variables
		ActorState *state_;
		bool is_controllable_;	// 操作可能かどうか

	private:

	};

}

#endif 