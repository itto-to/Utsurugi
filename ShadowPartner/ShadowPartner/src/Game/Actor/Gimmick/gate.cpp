//==========================================================
// 概要  :ゲートコンポーネント
// Author:Ittoto
// Copyright(c) Utsurugi.All right reserved.
//==========================================================
#include "gate.h"

#include "../../../Base/Element/gameobject.h"
#include "../../Scene/result_scene.h"
#include "../../../Base/System/scene_manager.h"

namespace shadowpartner
{
	void Gate::ActivateGimmick(GameObject *activator)
	{
		if (activator->tag_ == kPlayer && !is_activated_)
		{
			is_activated_ = true;

			// ゴール処理
			SceneManager::LoadScene(new ResultScene());
		}
	}

	void Gate::Start()
	{
		Collider::transform_ = Component::transform_;
		Collider::game_object_ = Component::game_object_;
	}
}	// namespace shadowpartner