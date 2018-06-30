//==========================================================
// 概要  :ギミック作動用インターフェース
// Author:Ittoto
// Copyright(c) Utsurugi.All right reserved.
//==========================================================
#ifndef _GAME_ACTOR_COMMON_GIMMICKINTERFACE_H_
#define _GAME_ACTOR_COMMON_GIMMICKINTERFACE_H_

#include "../../../Base/Element/component.h"

namespace shadowpartner
{
	class GameObject;

	class GimmickInterface
	{
	public:
		GimmickInterface() : is_activated_(false) {}
		virtual void ActivateGimmick(GameObject *activator) = 0;
		bool IsActivated() {return is_activated_;}

	protected:
		bool is_activated_;
	};
}

#endif