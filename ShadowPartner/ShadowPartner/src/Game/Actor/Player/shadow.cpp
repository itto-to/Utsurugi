//==========================================================
// 概要  :シャドウコンポーネント
// Author:Ittoto
// Copyright(c) Utsurugi.All right reserved.
//==========================================================

#include "shadow.h"

#include "../../../Base/2D/sprite.h"
#include "../../../Base/Physics/Element/box_collider.h"

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

	void Shadow::Start()
	{
		sprite = game_object_->GetComponent<Sprite>();
		collider = game_object_->GetComponent<physics::BoxCollider>();
	}

	void Shadow::CreateShadow(ShadowSize size)
	{
		switch (size)
		{
		case kLargeShadow:
			sprite->SetSize(Vector2(100, 100));
			break;
		case kMiddleShadow:
			sprite->SetSize(Vector2(200, 200));
			break;
		case kSmallShadow:
			sprite->SetSize(Vector2(300, 300));
			break;
		}
	}

}	// namespace shadowpartner
