//==========================================================
// 概要  :スイッチ
// Author:ItsukiNamito
// Copyright(c) Utsurugi.All right reserved.
//==========================================================
#include "observable_switch.h"
#include "observer_gate.h"

#include "../../../Base/Physics/physics.h"
#include "../../../Base/2D/sprite.h"
#include "../../../Base/System/scene.h"

using namespace physics;

namespace shadowpartner
{
	const BoxInitializer DEFAULT_BOX_INIT =
		BoxInitializer(Vector2::zero(), Vector2(0.0f, -0.0f), 1.0f, 1.0f, kStaticBody,
			true, true, 1.0f, 0.6f, 0.0f, CollisionFilter::kGimmickTrigger,
			CollisionFilter::kPlayer, 1.0f);

#define PRESSED_SWITCH_COLOR D3DCOLOR_RGBA(0xff,0xff,0xa0,0xff)
#define UNPRESSED_SWITCH_COLOR D3DCOLOR_RGBA(0xa0,0xa0,0xa0,0xff)

	ObservableSwitch::ObservableSwitch()
		:GimmickInterface(DEFAULT_BOX_INIT)
		, is_pressed_(false)
		, is_achieved_(false)
		, sprite_(nullptr)
	{

	}

	void ObservableSwitch::ActivateGimmick(GameObject *activator)
	{
		// Do nothing
	}

	void ObservableSwitch::StartObservation(ObserverGate *observer)
	{
		observer_ = observer;
		observer_->AddTarget(this);
	}

	bool ObservableSwitch::IsPressed()
	{
		return is_pressed_;
	}

	void ObservableSwitch::Achieve()
	{
		is_achieved_ = true;
		is_pressed_ = true;
	}

	void ObservableSwitch::EnterAction()
	{
		is_pressed_ = true;

		if (observer_ != nullptr)
		{
			observer_->Notify();
		}

		if (sprite_ == nullptr)
		{
			sprite_ = Component::GetComponent<Sprite>();
		}

		sprite_->SetColor(PRESSED_SWITCH_COLOR);
	}

	void ObservableSwitch::ExitAction()
	{
		if (is_achieved_)
			return;

		is_pressed_ = false;

		if (sprite_ == nullptr)
		{
			sprite_ = Component::GetComponent<Sprite>();
		}

		sprite_->SetColor(UNPRESSED_SWITCH_COLOR);
	}

	void ObservableSwitch::Start()
	{
		Collider::transform_ = Component::transform_;
		Collider::game_object_ = Component::game_object_;
	}

}	// namespace shadowpartner