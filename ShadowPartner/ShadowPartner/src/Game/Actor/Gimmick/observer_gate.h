//==========================================================
// 概要  :とげのゲート
// Author:Ittoto
// Copyright(c) Utsurugi.All right reserved.
//==========================================================
#ifndef _GAME_ACTOR_GIMMICK_OBSERVER_GATE_H_
#define _GAME_ACTOR_GIMMICK_OBSERVER_GATE_H_

#include "../../../Base/Element/component.h"

namespace shadowpartner
{
	class ObservableSwitch;

	class ObserverGate : public Component
	{
	public:
		ObserverGate();

		void Notify();	// 観測対象に変更があったことを通知する
		void SetOpenPos(Vector2 pos);
		void SetClosePos(Vector2 pos);
		void AddTarget(ObservableSwitch *target);
	protected:
		void Update() override;
	private:
		bool is_achieved_;
		float opening_rate_;	// ゲートの開き度合い
		std::vector<ObservableSwitch *> observation_targets_;
		Vector2 open_pos_;
		Vector2 close_pos_;
	};

}	// namespace shadowpartner

#endif	// _GAME_ACTOR_GIMMICK_TREE_H_