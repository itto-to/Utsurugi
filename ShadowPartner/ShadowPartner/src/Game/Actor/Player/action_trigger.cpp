//==========================================================
// 概要  :ギミックへのアクション用トリガー
// Author:Ittoto
// Copyright(c) Utsurugi.All right reserved.
//==========================================================
#include "action_trigger.h"

#include "../Common/actor.h"
#include "../Common/gimmick_interface.h"

using namespace physics;

namespace shadowpartner
{
	ActionTrigger::ActionTrigger(const physics::BoxInitializer &box_init) :
		BoxCollider(box_init),
		actor_(nullptr)
	{
		offset_facing_right_ = box_init.offset_;
	}

	void ActionTrigger::OnTriggerEnter(Collider *col)
	{
		if (!col->GetComponentInherit<GimmickInterface>()->IsActivated())
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

	void ActionTrigger::Update()
	{
		if (actor_ == nullptr)
		{
			actor_ = GetComponentInherit<Actor>();
		}

		if (actor_->HasChangedDirection())
		{
			if (actor_->GetDirection() == ActorDirection::kRight)
			{
				this->SetOffset(offset_facing_right_);
			}
			else
			{
				Vector2 offset_facing_left = -offset_facing_left;
				this->SetOffset(offset_facing_left);
			}
		}
	}

	void ActionTrigger::SetOffset(const Vector2 &offset)
	{
		offset_facing_right_ = offset;
	}

	void ActionTrigger::Activate()
	{
		if (gimmick_objects_.size() > 0)
		{
			for (auto itr = gimmick_objects_.begin(); itr != gimmick_objects_.end(); itr++)
			{
				GimmickInterface *gimmick = (*itr)->GetComponentInherit<GimmickInterface>();
				if (gimmick != nullptr && !gimmick->IsActivated())
				{
					gimmick->ActivateGimmick(game_object_);
				}
			}
		}
	}

}	// namespace shadowpartner