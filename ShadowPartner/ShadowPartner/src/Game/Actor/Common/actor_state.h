//==========================================================
// 概要  :アクターステート基底クラス
// Author:Ittoto
// Copyright(c) Utsurugi.All right reserved.
//==========================================================
#ifndef _GAME_ACTOR_COMMON_ACTORSTATE_H_
#define _GAME_ACTOR_COMMON_ACTORSTATE_H_

namespace shadowpartner
{
	class Actor;

	class ActorState
	{
	public:
		ActorState(Actor *owner);
		virtual ~ActorState();
		virtual void Enter() {}
		virtual void Exit() {}
		virtual void Execute() final;
		virtual void ExecuteState() {}
	protected:
		Actor *owner_;	// ステートの所有コンポーネント
		int counter_;	// ステート状態のカウンター

	private:
	};
}

#endif 