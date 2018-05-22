//==========================================================
// 概要  :描画のテスト用シーン
// Author:Itsuki Namito
// Copyright(c) Utsurugi.All right reserved.
//==========================================================
#include "draw_test_scene.h"
#include "../../Base/2D/camera.h"
#include "../../Base/2D/sprite.h"
#include "../../Base/Input/input.h"

#ifdef _DEBUG
#include "../../Base/Debug/debugger.h"
#endif

#include "../Object/frame_counter.h"
#include "../Object/fps_object.h"

#include "../../Base/Time/time.h"

#define TEST_TEXTURE_NAME "Resources/Texture/Fox1.png"

namespace shadowpartner
{
	// コンストラクタ
	DrawTestScene::DrawTestScene()
	{

	}
	
	// デストラクタ
	DrawTestScene::~DrawTestScene()
	{

	}

	// 初期化処理
	HRESULT DrawTestScene::Init()
	{
		printf("描画テストのシーンのオブジェクトを生成します。");

		// カメラオブジェクトを生成
		{
			camera_object = new GameObject();
			camera_object->transform_->position_ = Vector2(0.0f, 0.0f);
			Camera *camera = new Camera();
			camera_object->AddComponent(camera);

			gameObjects_.push_back(camera_object);
		}

		// 描画オブジェクトを生成
		{
			draw_object = new GameObject();
			draw_object->transform_->position_ = Vector2(0.0f, -200.0f);
			Sprite *sprite = new Sprite(TEST_TEXTURE_NAME);
			sprite->SetSize(Vector2(100, 100));
			draw_object->AddComponent(sprite);

			gameObjects_.push_back(draw_object);
		}

		// ゲーム開始時からのカウントオブジェクトを生成
		{
			draw_count_object = new GameObject();
			draw_count_object->transform_->position_ = Vector2(-300.0f, 0.0f);
			draw_count_object->transform_->scale_ = Vector2(2.0f, 2.0f);
			FrameCounter *frame_counter = new FrameCounter();
			draw_count_object->AddComponent(frame_counter);

			gameObjects_.push_back(draw_count_object);
		}

		// FPS表示オブジェクトを生成
		{
			draw_fps_object = new GameObject();
			draw_fps_object->transform_->position_ = Vector2(-300.0f, 200.0f);
			FpsObject *fps_object = new FpsObject();
			draw_fps_object->AddComponent(fps_object);

			gameObjects_.push_back(draw_fps_object);
		}

		return S_OK;
	}

	void DrawTestScene::Update()
	{
		float move = input::Input::Instance()->GetAxis(input::InputAxis::MouseX);
		draw_object->transform_->position_.x += move * 10 * Time::Instance()->delta_time_;
		system("cls");
		printf("move:%f\n", move);

<<<<<<< HEAD
#ifdef _DEBUG
		if (input::Input::Instance()->GetButtonDown(input::InputButton::Action))
		{
			debug::Debug::Log("Log:%d", 1);
		}
#endif
=======
		if (input::Input::Instance()->GetButtonDown(input::InputButton::Down))
		{
			draw_object->transform_->position_.y += 100.0f;
		}
>>>>>>> 161a44622ac47c57c9331b49c634d095a664506e
	}
}
