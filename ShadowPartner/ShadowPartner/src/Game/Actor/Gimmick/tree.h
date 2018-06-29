//==========================================================
// 概要  :倒木コンポーネント
// Author:Ittoto
// Copyright(c) Utsurugi.All right reserved.
//==========================================================
#ifndef _GAME_ACTOR_GIMMICK_TREE_H_
#define _GAME_ACTOR_GIMMICK_TREE_H_

#include "../../../Base/Element/component.h"
#include "../Common/gimmick_interface.h"

namespace physics
{
	class Collider;
}

namespace shadowpartner
{

	class Tree : public Component, public GimmickInterface
	{
	public:
		Tree();

		void Start() override;
		void Update() override;
	
		void ActivateGimmick() override;

	protected:
		physics::Collider *collider_;

		bool is_activated_;
	};

}	// namespace shadowpartner

#endif	// _GAME_ACTOR_GIMMICK_TREE_H_