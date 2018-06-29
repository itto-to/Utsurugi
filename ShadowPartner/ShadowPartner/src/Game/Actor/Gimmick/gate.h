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

	class  Gate : public Component, public GimmickInterface
	{
	public:
		Gate() : is_activated(false) {}

		void ActivateGimmick() override;

	protected:
		bool is_activated;
	};

}	// namespace shadowpartner

#endif