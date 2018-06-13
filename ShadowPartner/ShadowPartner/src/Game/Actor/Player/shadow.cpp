//==========================================================
// 概要  :シャドウコンポーネント
// Author:Ittoto
// Copyright(c) Utsurugi.All right reserved.
//==========================================================

#include "shadow.h"

namespace shadowpartner
{

	Shadow::Shadow()
	{
		is_controllable_ = false;
	}

	Shadow::Shadow(ActorState* state) : Actor(state)
	{
		is_controllable_ = false;
	}

	Shadow::~Shadow()
	{
		delete state_;
		state_ = nullptr;
	}

}	// namespace shadowpartner
