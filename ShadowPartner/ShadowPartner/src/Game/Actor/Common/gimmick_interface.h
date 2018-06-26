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
	class GimmickInterface
	{
	public:
		virtual void ActivateGimmick() = 0;
	};
}

#endif