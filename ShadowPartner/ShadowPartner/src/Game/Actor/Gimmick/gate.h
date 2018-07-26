//==========================================================
// 概要  :ゲートコンポーネント
// Author:Ittoto
// Copyright(c) Utsurugi.All right reserved.
//==========================================================
#ifndef _GAME_ACTOR_GIMMICK_GATE_H_
#define _GAME_ACTOR_GIMMICK_GATE_H_

#include "../../../Base/Element/component.h"
#include "../../../Game/Actor/Common/gimmick_interface.h"

namespace shadowpartner
{
	class GameObject;

	class  Gate : public Component, public GimmickInterface
	{
	public:
		Gate() {}

		void ActivateGimmick(GameObject *activator) override;

	protected:
		void Start() override;
	};

}	// namespace shadowpartner

#endif