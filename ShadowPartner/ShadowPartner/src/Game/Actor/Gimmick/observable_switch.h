//==========================================================
// 概要  :スイッチ
// Author:ItsukiNamito
// Copyright(c) Utsurugi.All right reserved.
//==========================================================
#ifndef _GAME_ACTOR_GIMMICK_OBSERVABLE_SWITCH_H_
#define _GAME_ACTOR_GIMMICK_OBSERVABLE_SWITCH_H_

#include "../../../Base/Element/component.h"
#include "../Common/gimmick_interface.h"

namespace shadowpartner
{
	class ObserverGate;
	class Sprite;

	class ObservableSwitch : public Component,public GimmickInterface
	{
	public:
		ObservableSwitch();

		void ActivateGimmick(GameObject *activator) override;

		void StartObservation(ObserverGate *observer);
		bool IsPressed();
		void Achieve();

	protected:
		void EnterAction() override;
		void ExitAction() override;

		void Start() override;
	private:
		bool is_pressed_;
		bool is_achieved_;

		ObserverGate *observer_;
		Sprite *sprite_;
	};

}	// namespace shadowpartner

#endif	// _GAME_ACTOR_GIMMICK_TREE_H_