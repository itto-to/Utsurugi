//==========================================================
// 概要  :倒木コンポーネント
// Author:Ittoto
// Copyright(c) Utsurugi.All right reserved.
//==========================================================
#include "tree.h"

#include "../../../Base/Element/gameobject.h"
#include "../../../Base/Physics/Element/collider.h"

using namespace physics;

namespace shadowpartner
{
	Tree::Tree() : is_activated_(false)
	{

	}

	void Tree::Start()
	{
		collider_ = Component::GetComponentInherit<Collider>();

		Collider::transform_ = Component::transform_;
		Collider::game_object_ = Component::game_object_;
	}

	void Tree::Update()
	{
	}

	void Tree::ActivateGimmick(GameObject *activator)
	{
		if (!is_activated_)
		{
			//collider_->AddTorque(-20000);
			//collider_->AddForceToPoint(Vector2(10000.0f, 0.0f), Vector2(0.0f, 5.0f));
			collider_->AddForce(Vector2(10000.0f, 0.0f));
			is_activated_ = true;
		}
	}

}	// namespace shadowpartner