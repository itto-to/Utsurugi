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

	enum ActorDirection
	{
		kRight,
		kLeft
	};

	class Actor : public Component {
	public:

		Actor();
		Actor(ActorState* state);
		virtual ~Actor();

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
		ActorState *state_;
		bool is_controllable_;			// 操作可能かどうか
		ActorDirection direction_;		// アクターの向き
		ActorDirection old_direction_;	// アクターの前フレームの向き

	private:

	};

}

#endif 