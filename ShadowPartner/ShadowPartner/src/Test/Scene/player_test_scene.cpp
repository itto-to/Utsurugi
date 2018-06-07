//==========================================================
// 概要  :プレイヤーのテストシーン
// Author:Ittoto
// Copyright(c) Utsurugi.All right reserved.
//==========================================================
#include "player_test_scene.h"
#include "../../Base/2D/camera.h"
#include "../../Game/Actor/Common/actor.h"
#include "../../Game/Actor/Player/jump_state.h"
#include "../../Base/Debug/debugger.h"
#include "../../Base/2D/sprite.h"
#include "../../Base/Physics/physics.h"

#define PLAYER_TEXTURE_NAME "Resources/Texture/Fox1.png"
#define BOX_TEXTURE_NAME "Resources/Texture/white.png"

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

		// プレイヤーを生成
		{
			player_ = new GameObject();
			player_->transform_->position_ = Vector2(0.0f, 100.0f);
			Sprite *sprite = new Sprite(PLAYER_TEXTURE_NAME);
			sprite->SetSize(Vector2(100, 100));
			player_->AddComponent(sprite);
			Actor *actor = new Actor();
			actor->SetState(new JumpState(actor));
			player_->AddComponent(actor);

			// 矩形の当たり判定の設定
			BoxInitializer box_init;
			box_init.width_ = 200.0f;
			box_init.height_ = 100.0f;
			box_init.is_static_ = false;
			box_init.pos_ = player_->transform_->position_;

			BoxCollider *box_collider = new BoxCollider(box_init);
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
			sprite->SetColor(D3DCOLOR_RGBA(0, 0, 0, 1));
			shadow_->AddComponent(sprite);

			gameObjects_.push_back(shadow_);
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

		return S_OK;
	}

	void PlayerTestScene::Update()
	{
	}

	void PlayerTestScene::Uninit()
	{
	}

}	// namespace shadowpartner