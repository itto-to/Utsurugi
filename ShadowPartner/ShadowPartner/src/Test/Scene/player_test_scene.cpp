//==========================================================
// 概要  :プレイヤーのテストシーン
// Author:Ittoto
// Copyright(c) Utsurugi.All right reserved.
//==========================================================
#include "player_test_scene.h"
#include "../../Base/2D/camera.h"
#include "../../Game/Actor/Player/player.h"
#include "../../Game/Actor/Player/shadow.h"
#include "../../Game/Actor/Player/jump_state.h"
#include "../../Game/Actor/Player/shadow_state.h"
#include "../../Base/Debug/debugger.h"
#include "../../Base/2D/sprite.h"
#include "../../Base/Light/light.h"
#include "../../Base/Physics/physics.h"
#include "../../Base/Input/input.h"
#include "../../Base/System/scene_manager.h"
#include "draw_test_scene.h"

#define PLAYER_TEXTURE_NAME "Resources/Texture/Fox1.png"
#define BOX_TEXTURE_NAME "Resources/Texture/white.png"
#define LIGHT_TEXTURE_NAME "Resources/Texture/LightBulb.png"

using namespace physics;

namespace shadowpartner {

	PlayerTestScene::PlayerTestScene() {}

	PlayerTestScene::~PlayerTestScene() {}

	HRESULT PlayerTestScene::Init()
	{
#ifdef _DEBUG
		debug::Debug::Log("シーンの切り替え：プレイヤーテスト");
#endif


		// カメラオブジェクトを生成
		{
			camera_object_ = new GameObject();
			camera_object_->transform_->position_ = Vector2(0.0f, 0.0f);
			Camera *camera = new Camera();
			camera_object_->AddComponent(camera);

			gameObjects_.push_back(camera_object_);
		}

		// 足場
		{
			platform_ = new GameObject();
			platform_->transform_->position_ = Vector2(0.0f, -215.0f);

			// スプライトの設定
			Sprite *sprite = new Sprite(BOX_TEXTURE_NAME);
			sprite->SetSize(Vector2(1120, 200));
			sprite->SetColor(D3DCOLOR_RGBA(0, 255, 0, 255));
			platform_->AddComponent(sprite);

			// 矩形の当たり判定の設定
			BoxInitializer box_init;
			box_init.width_ = 1120.0f;
			box_init.height_ = 200.0f;
			box_init.pos_ = platform_->transform_->position_;

			BoxCollider *box_collider = new BoxCollider(box_init);
			platform_->AddComponent(box_collider);

			// シーンにゲームオブジェクトを登録
			gameObjects_.push_back(platform_);
		}

		// プレイヤーを生成
		{
			player_ = new GameObject();
			player_->transform_->position_ = Vector2(0.0f, 100.0f);
			Sprite *sprite = new Sprite(PLAYER_TEXTURE_NAME);
			sprite->SetSize(Vector2(100, 100));
			player_->AddComponent(sprite);
			Player *actor = new Player();
			actor->SetState(new JumpState(actor));
			player_->AddComponent(actor);

			// 矩形の当たり判定の設定
			BoxInitializer box_init;
			box_init.width_ = 100.0f;
			box_init.height_ = 100.0f;
			box_init.is_static_ = false;
			box_init.pos_ = player_->transform_->position_;

			BoxCollider *box_collider = new BoxCollider(box_init);
			box_collider->is_active_ = false;
			player_->AddComponent(box_collider);

			// シーンにゲームオブジェクトを登録
			gameObjects_.push_back(player_);
		}

		// 影を生成
		{
			shadow_ = new GameObject();
			shadow_->transform_->position_ = player_->transform_->position_ + Vector2::down() * 100.0f;
			Sprite *sprite = new Sprite(PLAYER_TEXTURE_NAME);
			sprite->SetSize(Vector2(100, 100));
			sprite->SetColor(D3DCOLOR_RGBA(0, 0, 0, 0xff));
			shadow_->AddComponent(sprite);
			Shadow *shadow = new Shadow();
			ShadowState *shadow_state = new ShadowState(shadow);
			shadow_state->SetPlayer(player_);
			shadow->SetState(shadow_state);
			shadow_->AddComponent(shadow);

			// 矩形の当たり判定の設定
			//BoxInitializer box_init;
			//box_init.width_ = 200.0f;
			//box_init.height_ = 100.0f;
			//box_init.is_static_ = false;
			//box_init.pos_ = shadow_->transform_->position_;

			//BoxCollider *box_collider = new BoxCollider(box_init);
			//shadow_->AddComponent(box_collider);
			//shadow_->GetComponent<BoxCollider>()->is_active_ = false;

			gameObjects_.push_back(shadow_);
		}


		// ライト生成
		{
			light_ = new GameObject();
			light_->transform_->position_ = Vector2(0.0f, 270.0f);

			// ライトの設定
			LightInitializer light_init;
			light_init.radius_ = 500.0f;
			light_init.color_ = D3DCOLOR_RGBA(0xff, 0xff, 0x99, 0x77);
			Light *light = new Light(light_init);
			light_->AddComponent(light);

			// スプライトの設定
			Sprite *sprite = new Sprite(LIGHT_TEXTURE_NAME);
			sprite->SetSize(Vector2(100, 100));
			sprite->SetColor(D3DCOLOR_RGBA(0xff, 0xff, 0x99, 0xff));
			light_->AddComponent(sprite);

			// シーンにゲームオブジェクトを登録
			gameObjects_.push_back(light_);
		}

		return S_OK;
	}

	void PlayerTestScene::Update()
	{
		if (input::Input::Instance()->GetButtonDown(input::InputButton::Cancel))
			SceneManager::LoadScene(new DrawTestScene());
	}

	void PlayerTestScene::Uninit()
	{
	}

}	// namespace shadowpartner