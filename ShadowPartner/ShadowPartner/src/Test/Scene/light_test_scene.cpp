//==========================================================
// 概要  :ライトのテスト用シーン
// Author:Itsuki Namito
// Copyright(c) Utsurugi.All right reserved.
//==========================================================
#include "light_test_scene.h"
#include "../../Base/2D/camera.h"
#include "../../Base/2D/sprite.h"
#include "../../Base/Light/light.h"
#include "../../Base/Input/input.h"
#include "../../Base/System/scene_manager.h"
#include "draw_test_scene.h"

#ifdef _DEBUG
#include "../../Base/Debug/debugger.h"
#endif

#include "../../Base/Physics/physics.h"
#include "../../Base/Time/time.h"

#define LIGHT_TEXTURE_NAME "Resources/Texture/LightBulb.png"
#define BOX_TEXTURE_NAME "Resources/Texture/white.png"
#define CIRCLE_TEXTURE_NAME "Resources/Texture/WhiteCircle.png"

using namespace physics;

namespace shadowpartner
{
	const Vector2 pyramid_points[15] =
	{
		{100,0},{120,0},{140,0},{160,0},{180,0},
		{110,20},{130,20},{150,20},{170,20},
		{120,40},{140,40},{160,40},
		{130,60},{150,60},
		{140,80}
	};

	const Vector2 circle_points[11] =
	{
		{ -360,180 },{ -280,220 },{ -210,190 },{ -140,220 },{ -70,200 },
		{ 0,210 },{ 70,230 },{ 140,210 },{ 210,170 },{ 280,180 },{360,230}
	};

	// コンストラクタ
	LightTestScene::LightTestScene()
	{

	}

	// デストラクタ
	LightTestScene::~LightTestScene()
	{

	}

	// 初期化処理
	HRESULT LightTestScene::Init()
	{
#ifdef _DEBUG
		debug::Debug::Log("シーンの切り替え：物理テスト");
#endif
		// カメラオブジェクトを生成
		{
			camera_object_ = new GameObject();
			camera_object_->transform_->position_ = Vector2(0.0f, 0.0f);
			Camera *camera = new Camera();
			camera_object_->AddComponent(camera);

			gameObjects_.push_back(camera_object_);
		}

		// ライトのオブジェクト
		{
			light_object_ = new GameObject();
			light_object_->transform_->position_ = Vector2(0.0f, 270.0f);

			// ライトの設定
			LightInitializer light_init;
			light_init.radius_ = 100.0f;
			light_init.color_ = D3DCOLOR_RGBA(0xff, 0xff, 0x99, 0x77);
			Light *light = new Light(light_init);
			light_object_->AddComponent(light);

			// スプライトの設定
			Sprite *sprite = new Sprite(LIGHT_TEXTURE_NAME);
			sprite->SetSize(Vector2(100, 100));
			sprite->SetColor(D3DCOLOR_RGBA(0xff, 0xff, 0x99, 0xff));
			light_object_->AddComponent(sprite);

			// シーンにゲームオブジェクトを登録
			gameObjects_.push_back(light_object_);
		}


		// 動く円形のオブジェクト
		{
			player_ = new GameObject();
			player_->transform_->position_ = Vector2(-100.0f, 50.0f);

			// スプライトの設定
			Sprite *sprite = new Sprite(CIRCLE_TEXTURE_NAME);
			sprite->SetSize(Vector2(100, 100));
			sprite->SetColor(D3DCOLOR_RGBA(255, 0, 0, 255));
			player_->AddComponent(sprite);

			// 円形の当たり判定の設定
			CircleInitializer circle_init;
			circle_init.radius_ = 50.0f;
			circle_init.pos_ = player_->transform_->position_;
			circle_init.is_static_ = false;

			CircleCollider *circle_collider = new CircleCollider(circle_init);
			player_->AddComponent(circle_collider);

			// シーンにゲームオブジェクトを登録
			gameObjects_.push_back(player_);
		}

		// 天井
		{
			ceiling_ = new GameObject();
			ceiling_->transform_->position_ = Vector2(0.0f, 400.0f);

			// スプライトの設定
			Sprite *sprite = new Sprite(BOX_TEXTURE_NAME);
			sprite->SetSize(Vector2(800, 200));
			sprite->SetColor(D3DCOLOR_RGBA(150, 150, 150, 255));
			ceiling_->AddComponent(sprite);

			// 矩形の当たり判定の設定
			BoxInitializer box_init;
			box_init.width_ = 800.0f;
			box_init.height_ = 200.0f;
			box_init.pos_ = ceiling_->transform_->position_;

			BoxCollider *box_collider = new BoxCollider(box_init);
			ceiling_->AddComponent(box_collider);

			// シーンにゲームオブジェクトを登録
			gameObjects_.push_back(ceiling_);
		}

		// 左側の壁
		{
			left_wall_ = new GameObject();
			left_wall_->transform_->position_ = Vector2(-500.0f, 0.0f);

			// スプライトの設定
			Sprite *sprite = new Sprite(BOX_TEXTURE_NAME);
			sprite->SetSize(Vector2(200, 600));
			sprite->SetColor(D3DCOLOR_RGBA(150, 150, 150, 255));
			left_wall_->AddComponent(sprite);

			// 矩形の当たり判定の設定
			BoxInitializer box_init;
			box_init.width_ = 200.0f;
			box_init.height_ = 600.0f;
			box_init.pos_ = left_wall_->transform_->position_;

			BoxCollider *box_collider = new BoxCollider(box_init);
			left_wall_->AddComponent(box_collider);

			// シーンにゲームオブジェクトを登録
			gameObjects_.push_back(left_wall_);
		}

		// 右側の壁
		{
			right_wall_ = new GameObject();
			right_wall_->transform_->position_ = Vector2(500.0f, 0.0f);

			// スプライトの設定
			Sprite *sprite = new Sprite(BOX_TEXTURE_NAME);
			sprite->SetSize(Vector2(200, 600));
			sprite->SetColor(D3DCOLOR_RGBA(150, 150, 150, 255));
			right_wall_->AddComponent(sprite);

			// 矩形の当たり判定の設定
			BoxInitializer box_init;
			box_init.width_ = 200.0f;
			box_init.height_ = 600.0f;
			box_init.pos_ = right_wall_->transform_->position_;

			BoxCollider *box_collider = new BoxCollider(box_init);
			right_wall_->AddComponent(box_collider);

			// シーンにゲームオブジェクトを登録
			gameObjects_.push_back(right_wall_);
		}

		// 床
		{
			floor_ = new GameObject();
			floor_->transform_->position_ = Vector2(0.0f, -400.0f);

			// スプライトの設定
			Sprite *sprite = new Sprite(BOX_TEXTURE_NAME);
			sprite->SetSize(Vector2(800, 200));
			sprite->SetColor(D3DCOLOR_RGBA(150, 150, 150, 255));
			floor_->AddComponent(sprite);

			// 矩形の当たり判定の設定
			BoxInitializer box_init;
			box_init.width_ = 800.0f;
			box_init.height_ = 200.0f;
			box_init.pos_ = floor_->transform_->position_;

			BoxCollider *box_collider = new BoxCollider(box_init);
			floor_->AddComponent(box_collider);

			// シーンにゲームオブジェクトを登録
			gameObjects_.push_back(floor_);
		}

		// 適当なブロック
		{
			block1_ = new GameObject();
			block1_->transform_->position_ = Vector2(150.0f, -100.0f);

			// スプライトの設定
			Sprite *sprite = new Sprite(BOX_TEXTURE_NAME);
			sprite->SetSize(Vector2(300, 50));
			sprite->SetColor(D3DCOLOR_RGBA(100, 100, 100, 255));
			block1_->AddComponent(sprite);

			// 矩形の当たり判定の設定
			BoxInitializer box_init;
			box_init.width_ = 300.0f;
			box_init.height_ = 50.0f;
			box_init.pos_ = block1_->transform_->position_;

			BoxCollider *box_collider = new BoxCollider(box_init);
			block1_->AddComponent(box_collider);

			// シーンにゲームオブジェクトを登録
			gameObjects_.push_back(block1_);
		}

		// 適当な円を作る
		{
			for (int i = 0;i < 11;++i)
			{
				circles_[i] = new GameObject();

				circles_[i]->transform_->position_ = circle_points[i];

				Sprite *sprite = new Sprite(CIRCLE_TEXTURE_NAME);
				sprite->SetSize(Vector2(30, 30));
				sprite->SetColor(D3DCOLOR_RGBA(50, 153, 200, 255));
				circles_[i]->AddComponent(sprite);

				// 矩形の当たり判定の設定
				CircleInitializer circle_init;
				circle_init.radius_ = 15.0f;
				circle_init.pos_ = circles_[i]->transform_->position_;

				CircleCollider *circle_collider = new CircleCollider(circle_init);
				circles_[i]->AddComponent(circle_collider);

				// シーンにゲームオブジェクトを登録
				gameObjects_.push_back(circles_[i]);
			}
		}

		// ピラミッド作る
		{
			for (int i = 0;i < 15;++i)
			{
				pyramids_[i] = new GameObject();

				pyramids_[i]->transform_->position_ = pyramid_points[i];

				Sprite *sprite = new Sprite(BOX_TEXTURE_NAME);
				sprite->SetSize(Vector2(20, 20));
				sprite->SetColor(D3DCOLOR_RGBA(200, 153, 50, 255));
				pyramids_[i]->AddComponent(sprite);

				// 矩形の当たり判定の設定
				BoxInitializer box_init;
				box_init.width_ = 20.0f;
				box_init.height_ = 20.0f;
				box_init.is_static_ = false;
				box_init.pos_ = pyramids_[i]->transform_->position_;

				BoxCollider *box_collider = new BoxCollider(box_init);
				pyramids_[i]->AddComponent(box_collider);

				// シーンにゲームオブジェクトを登録
				gameObjects_.push_back(pyramids_[i]);
			}
		}

		return S_OK;
	}

	static int light_radius_scale = 0;

	void LightTestScene::Update()
	{
		CircleCollider *circle_collider = player_->GetComponent<CircleCollider>();

		RaycastHit hit_info = physics::PhysicsFunc::Raycast(
			player_->transform_->position_ + Vector2::down() * 9.9f,
			Vector2::down(), 0.15f);

		if (input::Input::Instance()->GetButtonDown(input::InputButton::Jump))
		{
			light_radius_scale = light_radius_scale % 5 + 1;
			light_object_->GetComponent<Light>()->SetRadius(100.0f * light_radius_scale);
		}

		if (input::Input::Instance()->GetButtonDown(input::InputButton::Action))
		{
			static int z = 0;
			z = (z + 1) % 3;
			Camera::main_->SetZoom(0.5f + 0.33f * (z + 1));

			debug::Debug::Log("set target_zoom_:%f", 0.5f + 0.33f * (z + 1));
		}

		Vector2 move = Vector2::zero();
		move.x = input::Input::Instance()->GetAxis(input::InputAxis::Horizontal);
		move.y = input::Input::Instance()->GetAxis(input::InputAxis::Vertical);

		player_->GetComponent<CircleCollider>()->AddForce(move * 10000000.0f);

		float shift = 0.01f;
		light_object_->transform_->position_.x += shift * 10 * Time::Instance()->delta_time_;
		if (light_object_->transform_->position_.x < -350.0f)
			light_object_->transform_->position_.x = 350.0f;
		if (light_object_->transform_->position_.x > 350.0f)
			light_object_->transform_->position_.x = -350.0f;

		if (input::Input::Instance()->GetButtonDown(input::InputButton::Cancel))
			SceneManager::LoadScene(new DrawTestScene());
	}

	void LightTestScene::Uninit()
	{
	}
}
