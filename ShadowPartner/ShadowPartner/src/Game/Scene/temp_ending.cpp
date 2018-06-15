//==========================================================
// 概要  :ライトのテスト用シーン
// Author:Itsuki Namito
// Copyright(c) Utsurugi.All right reserved.
//==========================================================
#include "temp_ending.h"
#include "../../Base/2D/camera.h"
#include "../../Base/2D/sprite.h"
#include "../../Base/Input/input.h"
#include "../../Base/System/scene_manager.h"
#include "title_scene.h"

#ifdef _DEBUG
#include "../../Base/Debug/debugger.h"
#endif

#include "../../Base/Time/time.h"

#define TEMP_ENDING_TEXTURE_NAME "Resources/Texture/TempEnding.png"

namespace shadowpartner
{
	// コンストラクタ
	TempEndingScene::TempEndingScene()
	{

	}

	// デストラクタ
	TempEndingScene::~TempEndingScene()
	{

	}

	// 初期化処理
	HRESULT TempEndingScene::Init()
	{
#ifdef _DEBUG
		debug::Debug::Log("シーンの切り替え：タイトル");
#endif
		// カメラオブジェクトを生成
		{
			camera_object_ = new GameObject();
			camera_object_->transform_->position_ = Vector2(0.0f, 0.0f);
			Camera *camera = new Camera();
			camera_object_->AddComponent(camera);

			AddGameObject(camera_object_);
		}

		// タイトル背景のオブジェクト
		{
			ending_image_ = new GameObject();
			ending_image_->transform_->position_ = Vector2(0.0f, 0.0f);

			// スプライトの設定
			Sprite *sprite = new Sprite(TEMP_ENDING_TEXTURE_NAME);
			sprite->SetSize(Vector2(1120, 630));
			sprite->SetColor(D3DCOLOR_RGBA(0xff, 0xff, 0xff, 0xff));
			ending_image_->AddComponent(sprite);

			// シーンにゲームオブジェクトを登録
			AddGameObject(ending_image_);
		}

		return S_OK;
	}

	static int light_radius_scale = 0;

	void TempEndingScene::Update()
	{
		if (input::Input::Instance()->GetButtonDown(input::InputButton::Start))
			SceneManager::LoadScene(new TitleScene());
	}

	void TempEndingScene::Uninit()
	{
	}
}
