//==========================================================
// 概要  :描画のテスト用シーン
// Author:Itsuki Namito
// Copyright(c) Utsurugi.All right reserved.
//==========================================================
#include "physics_test_scene.h"
#include "../../Base/2D/camera.h"
#include "../../Base/2D/sprite.h"
#include "../../Base/Input/input.h"

#ifdef _DEBUG
#include "../../Base/Debug/debugger.h"
#endif

#include "../../Base/Physics/physics.h"
#include "../../Base/Time/time.h"

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

	// コンストラクタ
	PhysicsTestScene::PhysicsTestScene()
		:pyramids_(nullptr)
	{

	}

	// デストラクタ
	PhysicsTestScene::~PhysicsTestScene()
	{

	}

	// 初期化処理
	HRESULT PhysicsTestScene::Init()
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

		// 静止したボックス
		{
			static_box = new GameObject();
			static_box->transform_->position_ = Vector2(0.0f, -215.0f);

			// スプライトの設定
			Sprite *sprite = new Sprite(BOX_TEXTURE_NAME);
			sprite->SetSize(Vector2(1120, 200));
			sprite->SetColor(D3DCOLOR_RGBA(0, 255, 0, 255));
			static_box->AddComponent(sprite);

			// 矩形の当たり判定の設定
			BoxInitializer box_init;
			box_init.width_ = 1120.0f;
			box_init.height_ = 200.0f;
			box_init.pos_ = static_box->transform_->position_;

			BoxCollider *box_collider = new BoxCollider(box_init);
			static_box->AddComponent(box_collider);

			// シーンにゲームオブジェクトを登録
			gameObjects_.push_back(static_box);
		}

		// 動かせるボックス
		{
			dynamic_box = new GameObject();
			dynamic_box->transform_->position_ = Vector2(0.0f, 0.0f);

			// スプライトの設定
			Sprite *sprite = new Sprite(BOX_TEXTURE_NAME);
			sprite->SetSize(Vector2(10, 10));
			sprite->SetColor(D3DCOLOR_RGBA(255, 30, 30, 255));
			dynamic_box->AddComponent(sprite);

			// 矩形の当たり判定の設定
			BoxInitializer box_init;
			box_init.width_ = 10.0f;
			box_init.height_ = 10.0f;
			box_init.is_static_ = false;
			box_init.pos_ = dynamic_box->transform_->position_;

			BoxCollider *box_collider = new BoxCollider(box_init);
			dynamic_box->AddComponent(box_collider);

			// シーンにゲームオブジェクトを登録
			gameObjects_.push_back(dynamic_box);
		}

		// 動かない円形のオブジェクト
		{
			static_circle = new GameObject();
			static_circle->transform_->position_ = Vector2(400.0f, -130.0f);

			// スプライトの設定
			Sprite *sprite = new Sprite(CIRCLE_TEXTURE_NAME);
			sprite->SetSize(Vector2(200, 200));
			sprite->SetColor(D3DCOLOR_RGBA(30, 200, 30, 255));
			static_circle->AddComponent(sprite);

			// 円形の当たり判定の設定
			CircleInitializer circle_init;
			circle_init.radius_ = 100.0f;
			circle_init.pos_ = static_circle->transform_->position_;

			CircleCollider *circle_collider = new CircleCollider(circle_init);
			static_circle->AddComponent(circle_collider);

			// シーンにゲームオブジェクトを登録
			gameObjects_.push_back(static_circle);
		}

		// 動く円形のオブジェクト
		{
			dynamic_circle = new GameObject();
			dynamic_circle->transform_->position_ = Vector2(-100.0f, 0.0f);

			// スプライトの設定
			Sprite *sprite = new Sprite(CIRCLE_TEXTURE_NAME);
			sprite->SetSize(Vector2(20, 20));
			sprite->SetColor(D3DCOLOR_RGBA(255, 0, 0, 255));
			dynamic_circle->AddComponent(sprite);

			// 円形の当たり判定の設定
			CircleInitializer circle_init;
			circle_init.radius_ = 10.0f;
			circle_init.pos_ = dynamic_circle->transform_->position_;
			circle_init.is_static_ = false;

			CircleCollider *circle_collider = new CircleCollider(circle_init);
			dynamic_circle->AddComponent(circle_collider);

			// シーンにゲームオブジェクトを登録
			gameObjects_.push_back(dynamic_circle);
		}

		// ピラミッド作る
		{
			pyramids_ = new GameObject[15];

			for (int i = 0;i < 15;++i)
			{
				pyramids_[i].transform_->position_ = pyramid_points[i];

				Sprite *sprite = new Sprite(BOX_TEXTURE_NAME);
				sprite->SetSize(Vector2(20, 20));
				sprite->SetColor(D3DCOLOR_RGBA(200, 153, 50, 255));
				pyramids_[i].AddComponent(sprite);

				// 矩形の当たり判定の設定
				BoxInitializer box_init;
				box_init.width_ = 20.0f;
				box_init.height_ = 20.0f;
				box_init.is_static_ = false;
				box_init.pos_ = pyramids_[i].transform_->position_;

				BoxCollider *box_collider = new BoxCollider(box_init);
				pyramids_[i].AddComponent(box_collider);

				// シーンにゲームオブジェクトを登録
				gameObjects_.push_back(&pyramids_[i]);
			}
		}


		return S_OK;
	}

	void PhysicsTestScene::Update()
	{
		CircleCollider *circle_collider = dynamic_circle->GetComponent<CircleCollider>();

		if (input::Input::Instance()->GetButtonDown(input::InputButton::Jump))
		{
			circle_collider->AddForce(Vector2::up() * 700000.0f);
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

		dynamic_circle->GetComponent<CircleCollider>()->AddForce(move * 100000.0f);
	}

	void PhysicsTestScene::Uninit()
	{
		if (pyramids_ != nullptr)
			delete[] pyramids_;
	}
}
