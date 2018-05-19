//==========================================================
// 概要  :描画のテスト用シーン
// Author:Itsuki Namito
// Copyright(c) Utsurugi.All right reserved.
//==========================================================
#include "draw_test_scene.h"
#include "../../Base/2D/camera.h"
#include "../../Base/2D/sprite.h"

#define TEST_TEXTURE_NAME "Resources/Texture/Earth.png"

namespace shadowpartner
{
	// コンストラクタ
	DrawTestScene::DrawTestScene()
	{
		// カメラオブジェクトを生成
		{
			GameObject *camera_object = new GameObject();
			camera_object->transform_->position_ = Vector2(0, 0);
			Camera *camera = new Camera();
			camera_object->AddComponent(camera);

			gameObjects_.push_back(camera_object);
		}

		// 描画オブジェクトを生成
		{
			GameObject *draw_object = new GameObject();
			draw_object->transform_->position_ = Vector2(0, 0);
			Sprite *sprite = new Sprite(TEST_TEXTURE_NAME);
			sprite->SetSize(Vector2(100,100));
			draw_object->AddComponent(sprite);

			gameObjects_.push_back(draw_object);
		}

	}
	
	// デストラクタ
	DrawTestScene::~DrawTestScene()
	{
	}

	// 初期化処理
	HRESULT DrawTestScene::Init()
	{

		return S_OK;
	}

}
