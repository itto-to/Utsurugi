#include "landing_trigger.h"

#ifdef _DEBUG
#include "../../../Base/Debug/debugger.h"
#endif


namespace shadowpartner
{

	LandingTrigger::LandingTrigger(const physics::BoxInitializer &box_init) :
		BoxCollider(box_init),
		is_landing_(false),
		landing_count_(0)
	{
	}

	void LandingTrigger::OnTriggerEnter(Collider *col)
	{
		if (!col->is_trigger_)
		{
			landing_count_++;
#ifdef _DEBUG
			debug::Debug::Log("LandingCount:%d", landing_count_);
#endif
		}
	}

	void LandingTrigger::OnTriggerExit(Collider *col)
	{
		if (!col->is_trigger_)
		{
			landing_count_--;
#ifdef _DEBUG
			debug::Debug::Log("LandingCount:%d", landing_count_);
#endif
		}
	}

	bool LandingTrigger::IsLanding()
	{
		return landing_count_ > 0;
	}

}