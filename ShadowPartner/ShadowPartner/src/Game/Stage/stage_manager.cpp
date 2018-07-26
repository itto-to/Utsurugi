//==========================================================
// 概要  :ステージ管理
// Author:ItsukiNamito
// Copyright(c) Utsurugi.All right reserved.
//==========================================================
#include "stage_manager.h"

#include "../../Base/Element/gameobject.h"
#include "../../Base/2D/sprite.h"

#include "../../Base/Input/input.h"
#include "../../Base/System/scene_manager.h"
#include "../Scene/result_scene.h"

using namespace input;

namespace shadowpartner
{
#define RESULT_APPEAR_FRAME (120)

	StageManager *StageManager::main_ = nullptr;

	StageManager::StageManager()
		:result_alpha_(0.0f)
		, is_cleared_(false)
	{
		if (main_ == nullptr)
			main_ = this;
	}

	StageManager::~StageManager()
	{
		if (main_ == this)
			main_ = nullptr;
	}

	void StageManager::SetResultScreen(Sprite *screen)
	{
		result_sprite_ = screen;
	}

	void StageManager::StageClear()
	{
		is_cleared_ = true;
	}

	void StageManager::Update()
	{
		if (is_cleared_)
		{
			if (result_alpha_ < 1.0f)
			{
				result_alpha_ += 1.0f / (float)RESULT_APPEAR_FRAME;

				if (result_alpha_ > 1.0f)
					result_alpha_ = 1.0f;

				result_sprite_->SetColor(D3DCOLOR_RGBA(0xff, 0xff, 0xff, (int)(result_alpha_ * 255.0f)));
			}
			else
				result_sprite_->SetColor(D3DCOLOR_RGBA(0xff, 0xff, 0xff, 0xff));
		}

		if (is_cleared_ && result_alpha_ > 0.9f)
		{
			if (Input::Instance()->GetButtonDown(InputButton::Start))
				SceneManager::LoadScene(new ResultScene());
		}
	}
}