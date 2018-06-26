//==========================================================
// ŠT—v  :ƒMƒ~ƒbƒN‚Æ‚ÌÕ“ËŒŸo—pƒgƒŠƒK[
// Author:Ittoto
// Copyright(c) Utsurugi.All right reserved.
//==========================================================

#include "gimmck_trigger.h"

#ifdef _DEBUG
#include "../../../Base/Debug/debugger.h"
#endif


namespace shadowpartner
{

	GimmickTrigger::GimmickTrigger(const physics::BoxInitializer &box_init) :
		BoxCollider(box_init),
		small_light_count_(0),
		middle_light_count_(0),
		large_light_count_(0),
		climb_count_(0)
	{
	}

	void GimmickTrigger::OnTriggerEnter(Collider *col)
	{
		switch (col->tag_)
		{
		case Tag::kSmallLight:
			small_light_count_++;
			break;

		case Tag::kMiddleLight:
			middle_light_count_++;
			break;

		case Tag::kLargeLight:
			large_light_count_++;
			break;

		case Tag::kClimb:
			climb_count_++;
			break;
		}
	}

	void GimmickTrigger::OnTriggerExit(Collider *col)
	{
		switch (col->tag_)
		{
		case Tag::kSmallLight:
			small_light_count_--;
			break;

		case Tag::kMiddleLight:
			middle_light_count_--;
			break;

		case Tag::kLargeLight:
			large_light_count_--;
			break;

		case Tag::kClimb:
			climb_count_--;
			break;
		}
	}

	LightType GimmickTrigger::HittingLightType()
	{
		if (small_light_count_ > 0)
			return kSmall;
		if (middle_light_count_ > 0)
			return kMiddle;
		if (large_light_count_ > 0)
			return kLarge;

		return kLightNone;
	}

	bool GimmickTrigger::CanClimb()
	{
		return climb_count_ > 0;
	}

	bool GimmickTrigger::IsHitLight()
	{
		if (small_light_count_ > 0)
			return true;
		if (middle_light_count_ > 0)
			return true;
		if (large_light_count_ > 0)
			return true;

		return false;
	}
}