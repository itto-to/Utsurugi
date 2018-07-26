//==========================================================
// �T�v  :�|�؃R���|�[�l���g
// Author:Ittoto
// Copyright(c) Utsurugi.All right reserved.
//==========================================================
#include "observer_gate.h"
#include "observable_switch.h"

using namespace physics;

namespace shadowpartner
{
#define GATE_OPEN_EXE_TIME (60) // �J���̂ɂ�����t���[����

	ObserverGate::ObserverGate()
		:is_achieved_(false)
		,opening_rate_(0.0f)
	{

	}

	//==========================================================
	// �T�v  :�ύX���������ʒm���󂯁A�ώ@���Ă���S�X�C�b�`�̏�Ԃ�
	//       :�m�F���܂��B
	//==========================================================
	void ObserverGate::Notify()
	{
		bool achieved_flag;

		for (int i = 0;i < observation_targets_.size();++i)
		{
			// ��ł�������Ă��Ȃ��X�C�b�`���������牽���N����Ȃ�
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