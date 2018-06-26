//==========================================================
// 概要  :ギミックへのアクション用トリガー
// Author:Ittoto
// Copyright(c) Utsurugi.All right reserved.
//==========================================================
#include "action_trigger.h"

#include "../Common/gimmick_interface.h"

using namespace physics;

namespace shadowpartner
{
	ActionTrigger::ActionTrigger(const physics::BoxInitializer & box_init) :
		BoxCollider(box_init)
	{

	}

	void ActionTrigger::OnTriggerEnter(Collider *col)
	{
		gimmick_objects_.push_back(col->game_object_);
	}

	void ActionTrigger::OnTriggerExit(Collider *col)
	{
		for (auto itr = gimmick_objects_.begin(); itr != gimmick_objects_.end(); itr++)
		{
			if (*itr == col->game_object_)
			{
				gimmick_objects_.erase(itr);
				return;
			}
		}
	}

	void ActionTrigger::Activate()
	{
		if (gimmick_objects_.size() > 0)
		{
			GimmickInterface *gimmick = gimmick_objects_[0]->GetComponentInherit<GimmickInterface>();
			if (gimmick != nullptr)
			{
				gimmick->ActivateGimmick();
			}
		}
	}

}	// namespace shadowpartner