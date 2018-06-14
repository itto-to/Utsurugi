//==========================================================
// 概要  :最初のシーンクラス
// Author:Itsuki Namito
// Copyright(c) Utsurugi.All right reserved.
//==========================================================
#include "first_stage_scene.h"
#include "../../Base/2D/camera.h"
#include "../../Base/2D/sprite.h"
#include "../../Base/Light/light.h"
#include "../../Base/Input/input.h"
#include "../Stage/stage.h"
#include "../../Base/System/scene_manager.h"

#ifdef _DEBUG
#include "../../Base/Debug/debugger.h"
#endif

#include "../../Base/Physics/physics.h"
#include "../../Base/Time/time.h"

#define LIGHT_TEXTURE_NAME "Resources/Texture/LightBulb.png"
#define BACK_GROUND_TEXTURE_NAME "Resources/Texture/Stage/ForestBackGround.png"

using namespace physics;

namespace shadowpartner
{
	// コンストラクタ
	FirstStageScene::FirstStageScene(int phase_num)
		:StageScene(phase_num)
	{

	}

	// デストラクタ
	FirstStageScene::~FirstStageScene()
	{

	}

	// 初期化処理
	HRESULT FirstStageScene::Init()
	{
#ifdef _DEBUG
		debug::Debug::Log("シーンの切り替え：物理テスト");
#endif
		// 背景
		{
			back_ground_ = new GameObject();
			back_ground_->transform_->position_ = Vector2(1120, 0);

			Sprite *sprite = new Sprite(BACK_GROUND_TEXTURE_NAME);
			sprite->SetSize(Vector2(3360.0f, 630.0f));
			back_ground_->AddComponent(sprite);

			AddGameObject(back_ground_);
		}

		// Stage Fase1
		{
			stages_[0] = new GameObject();
			stages_[0]->transform_->position_ = Vector2(0.0f, 0.0f);

			Stage *stage = new Stage(StageNumber::kTest, *stages_[0], TILE_DATA, STAGE_PASS);
			stages_[0]->AddComponent(stage);

			AddGameObject(stages_[0]);
		}

		StageScene::Init();

		return S_OK;
	}

	void FirstStageScene::Update()
	{
		StageScene::Update();

		if (input::Input::Instance()->GetButtonDown(input::InputButton::Skill))
		{
			NextPhase();
		}
		if (input::Input::Instance()->GetButtonDown(input::InputButton::Cancel))
		{
			PrevPhase();
		}
		if (input::Input::Instance()->GetButtonDown(input::InputButton::Action))
		{
			static int z = 0;
			z = (z + 1) % 3;
			Camera::main_->SetZoom(0.5f + 0.33f * (z + 1));
			debug::Debug::Log("set target_zoom_:%f", 0.5f + 0.33f * (z + 1));
		}

	}

	void FirstStageScene::Uninit()
	{
		StageScene::Uninit();


	}
}
