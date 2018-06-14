//==========================================================
// 概要  :登りステート
// Author:Ittoto
// Copyright(c) Utsurugi.All right reserved.
//==========================================================

#include "../Common/actor.h"
#include "../../../Base/Element/component.h"
#include "../../../Base/Input/input.h"

namespace shadowpartner
{
	class ClimbState : public ActorState
	{

		ClimbState(Actor* owner) : ActorState(owner) {}
 
		void ClimbState::Enter()
		{
			owner_->game_object_->transform_->rotation_ = D3DXToRadian(90);
		}

		void ClimbState::Execute()
		{
			float move = input::Input::Instance()->GetAxis(input::InputAxis::Vertical);
			owner_->game_object_->transform_->position_.y += move;

		}

		void ClimbState::Exit()
		{
			owner_->game_object_->transform_->rotation_ = D3DXToRadian(0);
		}
		
	};

}	// namespace shadowpartner