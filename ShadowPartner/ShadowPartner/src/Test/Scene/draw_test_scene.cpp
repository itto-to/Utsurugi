//==========================================================
// 概要  :描画のテスト用シーン
// Author:Itsuki Namito
// Copyright(c) Utsurugi.All right reserved.
//==========================================================
#include "draw_test_scene.h"
#include "../../Base/2D/camera.h"
#include "../../Base/2D/sprite.h"
#include "../../Base/Input/input.h"
#include "../../Game/Actor/Common/actor.h"
#include "../../Game/Actor/Player/idle_state.h"
#include "../../Game/Stage/tile.h"
#include "../../Game/Stage/Stage.h"
#include "../../Base/System/scene_manager.h"
#include "physics_test_scene.h"

#ifdef _DEBUG
#include "../../Base/Debug/debugger.h"
#endif

#include "../Object/frame_counter.h"
#include "../Object/fps_object.h"

#include "../../Base/Time/time.h"

#define TEST_TEXTURE_NAME "Resources/Texture/Fox1.png"
#define TEST_TILES_NAME "Resources/Tiles/053-Wall01.png"

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
#ifdef _DEBUG
		debug::Debug::Log("シーンの切り替え：描画テスト");
#endif
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


			 draw_stage=new GameObject();
			 draw_stage->transform_->position_ = Vector2(0.0f, 0.0f);
			 Stage *stage = new Stage(kTest,*draw_stage, TILE_DATA, STAGE_PASS);
			 draw_stage->AddComponent(stage);

			gameObjects_.push_back(draw_stage);


			draw_object = new GameObject();
			draw_object->transform_->position_ = Vector2(0.0f, -200.0f);
			Sprite *sprite = new Sprite(TEST_TEXTURE_NAME);
			sprite->SetSize(Vector2(100, 100));
			draw_object->AddComponent(sprite);
			Actor *actor = new Actor();
			actor->SetState(new IdleState(actor));
			draw_object->AddComponent(actor);

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

	void DrawTestScene::Uninit()
	{
	}

	void DrawTestScene::Update()
	{
		//float move = input::Input::Instance()->GetAxis(input::InputAxis::MouseX);
		//draw_object->transform_->position_.x += move * 10 * Time::Instance()->delta_time_;

#ifdef _DEBUG
		if (input::Input::Instance()->GetButtonDown(input::InputButton::Action))
		{
			debug::Debug::Log("Log:%d", 1);
		}
#endif
		if (input::Input::Instance()->GetButtonDown(input::InputButton::Down))
		{
			draw_object->transform_->position_.y += 100.0f;
		}

		if (input::Input::Instance()->GetButtonDown(input::InputButton::Cancel))
			SceneManager::LoadScene(new PhysicsTestScene());
	}
}
