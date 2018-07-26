//==========================================================
// 概要  :倒木コンポーネント
// Author:Ittoto
// Copyright(c) Utsurugi.All right reserved.
//==========================================================
#include "observer_gate.h"
#include "observable_switch.h"

using namespace physics;

namespace shadowpartner
{
#define GATE_OPEN_EXE_TIME (60) // 開くのにかかるフレーム数

	ObserverGate::ObserverGate()
		:is_achieved_(false)
		,opening_rate_(0.0f)
	{

	}

	//==========================================================
	// 概要  :変更があった通知を受け、観察している全スイッチの状態を
	//       :確認します。
	//==========================================================
	void ObserverGate::Notify()
	{
		bool achieved_flag;

		for (int i = 0;i < observation_targets_.size();++i)
		{
			// 一つでも押されていないスイッチがあったら何も起こらない
			if (!observation_targets_[i]->IsPressed())
				return;
		}

		is_achieved_ = true;

		for (int i = 0;i < observation_targets_.size();++i)
		{
			observation_targets_[i]->Achieve();
		}
	}

	void ObserverGate::Update()
	{
		if (is_achieved_)
		{
			if (opening_rate_ < 1.0f)
			{
				opening_rate_ += 1.0f / (float)GATE_OPEN_EXE_TIME;

				if (opening_rate_ > 1.0f)
					opening_rate_ = 1.0f;

				transform_->position_ = Lerp(opening_rate_, close_pos_, open_pos_, true);
			}
		}
	}

	void ObserverGate::SetOpenPos(Vector2 pos)
	{
		open_pos_ = pos;
	}

	void ObserverGate::SetClosePos(Vector2 pos)
	{
		close_pos_ = pos;
	}

	void ObserverGate::AddTarget(ObservableSwitch *target)
	{
		observation_targets_.push_back(target);
	}

}	// namespace shadowpartner