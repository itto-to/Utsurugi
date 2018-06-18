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
//#include "../../Base/Physics/Element/light_collider.h"
#include "../../Base/Debug/debugger.h"
#include "../../Base/2D/sprite.h"
#include "../../Base/Light/light.h"
#include "../../Base/Physics/physics.h"
#include "../../Base/Physics/Element/polygon_collider.h"
#include "../../Base/Input/input.h"
#include "../../Base/System/scene_manager.h"
#include "draw_test_scene.h"
#include "../../Base/Physics/Filter/collision_filter.h"

#define PLAYER_TEXTURE_NAME "Resources/Texture/Fox1.png"
#define BOX_TEXTURE_NAME    "Resources/Texture/white.png"
#define LIGHT_TEXTURE_NAME  "Resources/Texture/LightBulb.png"

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

			AddGameObject(camera_object_);
		}


		// 大ライト生成
		{
			large_light_ = new GameObject();
			large_light_->transform_->position_ = Vector2(0.0f, 0.0f);
			large_light_->tag_ = Tag::kLargeLight;

			// スプライトの設定
			Sprite *sprite = new Sprite(BOX_TEXTURE_NAME);
			sprite->SetSize(Vector2(1000, 800));
			sprite->SetColor(D3DCOLOR_RGBA(0xff, 0xff, 0x99, 0xff));
			large_light_->AddComponent(sprite);

			// 矩形の当たり判定の設定
			BoxInitializer box_init;
			box_init.width_ = 1000.0f;
			box_init.height_ = 800.0f;
			box_init.body_type_ = kStaticBody;
			box_init.is_trigger_ = true;
			box_init.pos_ = large_light_->transform_->position_;

			BoxCollider *box_collider = new BoxCollider(box_init);
			large_light_->AddComponent(box_collider);

			// シーンにゲームオブジェクトを登録
			AddGameObject(large_light_);
		}

		// 足場
		{
			platform_[0] = new GameObject();
			platform_[0]->transform_->position_ = Vector2(-300.0f, -350.0f);

			// スプライトの設定
			Sprite *sprite = new Sprite(BOX_TEXTURE_NAME);
			sprite->SetSize(Vector2(900, 200));
			sprite->SetColor(D3DCOLOR_RGBA(0, 255, 0, 255));
			platform_[0]->AddComponent(sprite);

			// 矩形の当たり判定の設定
			BoxInitializer box_init;
			box_init.width_ = 900.0f;
			box_init.height_ = 200.0f;
			box_init.body_type_ = kStaticBody;
			box_init.pos_ = platform_[0]->transform_->position_;

			BoxCollider *box_collider = new BoxCollider(box_init);
			platform_[0]->AddComponent(box_collider);

			// シーンにゲームオブジェクトを登録
			AddGameObject(platform_[0]);
		}

		// 足場
		{
			platform_[1] = new GameObject();
			platform_[1]->transform_->position_ = Vector2(600.0f, -350.0f);

			// スプライトの設定
			Sprite *sprite = new Sprite(BOX_TEXTURE_NAME);
			sprite->SetSize(Vector2(600, 200));
			sprite->SetColor(D3DCOLOR_RGBA(0, 255, 0, 255));
			platform_[1]->AddComponent(sprite);

			// 矩形の当たり判定の設定
			BoxInitializer box_init;
			box_init.width_ = 600.0f;
			box_init.height_ = 200.0f;
			box_init.body_type_ = kStaticBody;
			box_init.pos_ = platform_[1]->transform_->position_;

			BoxCollider *box_collider = new BoxCollider(box_init);
			platform_[1]->AddComponent(box_collider);

			// シーンにゲームオブジェクトを登録
			AddGameObject(platform_[1]);
		}

		// 足場
		{
			platform_[2] = new GameObject();
			platform_[2]->transform_->position_ = Vector2(-200.0f, 200.0f);

			// スプライトの設定
			Sprite *sprite = new Sprite(BOX_TEXTURE_NAME);
			sprite->SetSize(Vector2(200, 100));
			sprite->SetColor(D3DCOLOR_RGBA(0, 255, 0, 255));
			platform_[2]->AddComponent(sprite);

			// 矩形の当たり判定の設定
			BoxInitializer box_init;
			box_init.width_ = 200.0f;
			box_init.height_ = 100.0f;
			box_init.body_type_ = kStaticBody;
			box_init.pos_ = platform_[2]->transform_->position_;

			BoxCollider *box_collider = new BoxCollider(box_init);
			platform_[2]->AddComponent(box_collider);

			// シーンにゲームオブジェクトを登録
			AddGameObject(platform_[2]);
		}

		// 足場
		{
			platform_[3] = new GameObject();
			platform_[3]->transform_->position_ = Vector2(0.0f, 300.0f);

			// スプライトの設定
			Sprite *sprite = new Sprite(BOX_TEXTURE_NAME);
			sprite->SetSize(Vector2(200, 100));
			sprite->SetColor(D3DCOLOR_RGBA(0, 255, 0, 255));
			platform_[3]->AddComponent(sprite);

			// 矩形の当たり判定の設定
			BoxInitializer box_init;
			box_init.width_ = 200.0f;
			box_init.height_ = 100.0f;
			box_init.body_type_ = kStaticBody;
			box_init.pos_ = platform_[3]->transform_->position_;

			BoxCollider *box_collider = new BoxCollider(box_init);
			platform_[3]->AddComponent(box_collider);

			// シーンにゲームオブジェクトを登録
			AddGameObject(platform_[3]);
		}

		// 中ライト生成
		{
			middle_light_ = new GameObject();
			middle_light_->transform_->position_ = Vector2(-200.0f, -100.0f);
			middle_light_->tag_ = Tag::kMiddleLight;

			// スプライトの設定
			Sprite *sprite = new Sprite(BOX_TEXTURE_NAME);
			sprite->SetSize(Vector2(300, 300));
			sprite->SetColor(D3DCOLOR_RGBA(0x00, 0x00, 0xff, 0x80));
			middle_light_->AddComponent(sprite);

			// 矩形の当たり判定の設定
			BoxInitializer box_init;
			box_init.width_ = 300.0f;
			box_init.height_ = 300.0f;
			box_init.body_type_ = kStaticBody;
			box_init.is_trigger_ = true;
			box_init.pos_ = middle_light_->transform_->position_;

			BoxCollider *box_collider = new BoxCollider(box_init);
			middle_light_->AddComponent(box_collider);

			// シーンにゲームオブジェクトを登録
			AddGameObject(middle_light_);
		}

		// 小ライト生成
		{
			small_light_ = new GameObject();
			small_light_->transform_->position_ = Vector2(100.0f, -150.0f);
			small_light_->tag_ = Tag::kSmallLight;

			// スプライトの設定
			Sprite *sprite = new Sprite(BOX_TEXTURE_NAME);
			sprite->SetSize(Vector2(200, 200));
			sprite->SetColor(D3DCOLOR_RGBA(0xff, 0x00, 0x00, 0x80));
			small_light_->AddComponent(sprite);

			// 矩形の当たり判定の設定
			BoxInitializer box_init;
			box_init.width_ = 200.0f;
			box_init.height_ = 200.0f;
			box_init.body_type_ = kStaticBody;
			box_init.is_trigger_ = true;
			box_init.pos_ = small_light_->transform_->position_;

			BoxCollider *box_collider = new BoxCollider(box_init);
			small_light_->AddComponent(box_collider);

			// シーンにゲームオブジェクトを登録
			AddGameObject(small_light_);
		}

		// プレイヤーを生成
		{
			player_ = new GameObject();
			player_->transform_->position_ = Vector2(-400.0f, -100.0f);
			Sprite *sprite = new Sprite(PLAYER_TEXTURE_NAME);
			sprite->SetSize(Vector2(100, 100));
			player_->AddComponent(sprite);

			// 矩形の当たり判定の設定
			BoxInitializer box_init;
			box_init.width_ = 100.0f;
			box_init.height_ = 100.0f;
			box_init.density_ = 1.0f;
			box_init.body_type_ = kDynamicBody;
			box_init.is_trigger_ = false;
			box_init.pos_ = player_->transform_->position_;

			BoxCollider *box_collider = new BoxCollider(box_init);
			box_collider->SetSleepingAllowed(false);	// Sleepを許可しない
			player_->AddComponent(box_collider);

			Player *actor = new Player();
			player_->AddComponent(actor);

			// シーンにゲームオブジェクトを登録
			AddGameObject(player_);
		}

		// TEST: 凸ポリゴン生成
		{
			//player_ = new GameObject();
			//player_->transform_->position_ = Vector2(0.0f, 100.0f);
			//Sprite *sprite = new Sprite(PLAYER_TEXTURE_NAME);
			//sprite->SetSize(Vector2(100, 100));
			//player_->AddComponent(sprite);
			////Player *actor = new Player();
			////actor->SetState(new JumpState(actor));
			////player_->AddComponent(actor);

			//// ポリゴンの当たり判定の設定
			//PolygonInitializer poly_init;
			//poly_init.vertices_.push_back(Vector2(90.0f, 100.0f));
			//poly_init.vertices_.push_back(Vector2(-100.0f, 100.0f));
			//poly_init.vertices_.push_back(Vector2(0.0f, -100.0f));
			//poly_init.body_type_ = kDynamicBody;
			//poly_init.pos_ = player_->transform_->position_;

			//PolygonCollider *poly_collider = new PolygonCollider(poly_init);
			//player_->AddComponent(poly_collider);

			//// シーンにゲームオブジェクトを登録
			//gameObjects_.push_back(player_);

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

			// プレイヤーのシャドウに登録
			shadow->player_object_ = player_;
			player_->GetComponent<Player>()->shadow_ = shadow_;

			// 矩形の当たり判定の設定
			BoxInitializer box_init;
			box_init.width_ = 100.0f;
			box_init.height_ = 100.0f;
			box_init.body_type_ = kDynamicBody;
			box_init.is_trigger_ = true;
			box_init.pos_ = shadow_->transform_->position_;

			BoxCollider *box_collider = new BoxCollider(box_init);
			shadow_->AddComponent(box_collider);

			AddGameObject(shadow_);
		}

		//// ライト生成
		//{
		//	light_ = new GameObject();
		//	light_->transform_->position_ = Vector2(0.0f, 270.0f);

		//	// ライトの設定
		//	LightInitializer light_init;
		//	light_init.radius_ = 100.0f;
		//	light_init.color_ = D3DCOLOR_RGBA(0xff, 0xff, 0x99, 0x77);
		//	Light *light = new Light(light_init);
		//	light_->AddComponent(light);

		//	// スプライトの設定
		//	Sprite *sprite = new Sprite(LIGHT_TEXTURE_NAME);
		//	sprite->SetSize(Vector2(100, 100));
		//	sprite->SetColor(D3DCOLOR_RGBA(0xff, 0xff, 0x99, 0xff));
		//	light_->AddComponent(sprite);

		//	// シーンにゲームオブジェクトを登録
		//	gameObjects_.push_back(light_);
		//}

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