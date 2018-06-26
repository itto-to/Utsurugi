//==========================================================
// 概要  :倒木コンポーネント
// Author:Ittoto
// Copyright(c) Utsurugi.All right reserved.
//==========================================================
#include "tree.h"

#include "../../../Base/Physics/Element/collider.h"

using namespace physics;

namespace shadowpartner
{
	Tree::Tree()
	{

	}

	void Tree::Start()
	{
		collider_ = GetComponentInherit<Collider>();
	}

	void Tree::ActivateGimmick()
	{

	}

}	// namespace shadowpartner