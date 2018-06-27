//==========================================================
// 概要  :描画のテスト用シーン
// Author:Itsuki Namito
// Copyright(c) Utsurugi.All right reserved.
//==========================================================
#include "physics_test_scene.h"
#include "../../Base/2D/camera.h"
#include "../../Base/2D/sprite.h"
#include "../../Base/Light/light.h"
#include "../../Base/Input/input.h"
#include "../../Base/System/scene_manager.h"
#include "light_test_scene.h"
#include "player_test_scene.h"

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
		{1.0f,0.0f},{1.2f,0.0f},{1.4f,0.0f},{1.6f,0.0f},{1.8f,0.0f},
		{1.1f,0.2f},{1.3f,0.2f},{1.5f,0.2f},{1.7f,0.2f},
		{1.2f,0.4f},{1.4f,0.4f},{1.6f,0.4f},
		{1.3f,0.6f},{1.5f,0.6f},
		{1.4f,0.8f}
	};

	// コンストラクタ
	PhysicsTestScene::PhysicsTestScene()
	{

	}

	// デストラクタ
	PhysicsTestScene::~PhysicsTestScene()
	{

	}

	// 初期化処理
	HRESULT PhysicsTestScene::Init()
	{
#ifdef _DEBUG
		debug::Debug::Log("シーンの切り替え：物理テスト");
#endif
		// カメラオブジェクトを生成
		{
			camera_object = new GameObject();
			camera_object->transform_->position_ = Vector2(0.0f, 0.0f);
			Camera *camera = new Camera();
			camera_object->AddComponent(camera);

			AddGameObject(camera_object);
		}

		// 動く円形のオブジェクト
		{
			dynamic_circle = new GameObject();
			dynamic_circle->transform_->position_ = Vector2(-3.0f, 1.0f);

			// スプライトの設定
			Sprite *sprite = new Sprite(CIRCLE_TEXTURE_NAME);
			sprite->SetSize(Vector2(0.3f, 0.3f));
			sprite->SetColor(D3DCOLOR_RGBA(255, 0, 0, 255));
			sprite->SetOrderInLayer(1);
			dynamic_circle->AddComponent(sprite);

			// 円形の当たり判定の設定
			CircleInitializer circle_init;
			circle_init.radius_ = 0.1f;
			circle_init.pos_ = dynamic_circle->transform_->position_;

			CircleCollider *circle_collider = new CircleCollider(circle_init);
			dynamic_circle->AddComponent(circle_collider);

			// シーンにゲームオブジェクトを登録
			AddGameObject(dynamic_circle);
		}

		// 静止したボックス
		{
			static_box = new GameObject();
			static_box->transform_->position_ = Vector2(0.0f, -2.0f);

			// スプライトの設定
			Sprite *sprite = new Sprite(BOX_TEXTURE_NAME);
			sprite->SetSize(Vector2(11.2f, 3.0f));
			sprite->SetColor(D3DCOLOR_RGBA(0, 255, 0, 255));
			static_box->AddComponent(sprite);

			// 矩形の当たり判定の設定
			BoxInitializer box_init;
			box_init.width_ = 11.2f;
			box_init.height_ = 3.0f;
			box_init.pos_ = static_box->transform_->position_;
			box_init.body_type_ = BodyType::kStaticBody;

			BoxCollider *box_collider = new BoxCollider(box_init);
			static_box->AddComponent(box_collider);

			// シーンにゲームオブジェクトを登録
			AddGameObject(static_box);
		}

		// 動かせるボックス
		{
			dynamic_box = new GameObject();
			dynamic_box->transform_->position_ = Vector2(-1.0f, 1.0f);

			// スプライトの設定
			Sprite *sprite = new Sprite(BOX_TEXTURE_NAME);
			sprite->SetSize(Vector2(0.1f, 2.0f));
			sprite->SetColor(D3DCOLOR_RGBA(255, 30, 30, 255));
			dynamic_box->AddComponent(sprite);

			// 矩形の当たり判定の設定
			BoxInitializer box_init;
			box_init.width_ = 0.1f;
			box_init.height_ = 2.0f;
			box_init.pos_ = dynamic_box->transform_->position_;
			box_init.fixed_rotation_ = false;

			BoxCollider *box_collider = new BoxCollider(box_init);
			dynamic_box->AddComponent(box_collider);

			box_collider->AddForce(Vector2(1.0f,1.0f) * 1000.0f);

			// シーンにゲームオブジェクトを登録
			AddGameObject(dynamic_box);
		}

		// 動かない円形のオブジェクト
		{
			static_circle = new GameObject();
			static_circle->transform_->position_ = Vector2(4.0f, -1.0f);

			// スプライトの設定
			Sprite *sprite = new Sprite(CIRCLE_TEXTURE_NAME);
			sprite->SetSize(Vector2(2, 2));
			sprite->SetColor(D3DCOLOR_RGBA(30, 200, 30, 255));
			static_circle->AddComponent(sprite);

			// 円形の当たり判定の設定
			CircleInitializer circle_init;
			circle_init.radius_ = 1.0f;
			circle_init.pos_ = static_circle->transform_->position_;
			circle_init.body_type_ = BodyType::kStaticBody;

			CircleCollider *circle_collider = new CircleCollider(circle_init);
			static_circle->AddComponent(circle_collider);

			// シーンにゲームオブジェクトを登録
			AddGameObject(static_circle);
		}

		// ヒンジジョイントを作る
		{
			hinge_joint = new GameObject();

			hinge_joint->transform_->position_ = Vector2(-1.0f, -0.4f);

			RevoluteInitializer ri;
			ri.collider_a_ = dynamic_box->GetComponent<BoxCollider>();
			ri.local_anchor_a_ = Vector2(0.0f, -1.1f);
			ri.collider_b_ = static_box->GetComponent<BoxCollider>();
			ri.local_anchor_b_ = Vector2(0.0f, 1.6f);
			ri.world_pos_ = hinge_joint->transform_->position_;

			ri.enable_limit_ = true;
			ri.lower_angle_ = -60.0f;
			ri.upper_angle_ = 5.0f;

			RevoluteJoint *revolute_joint = new RevoluteJoint(ri);
			hinge_joint->AddComponent(revolute_joint);

			AddGameObject(hinge_joint);
		}

		// ピラミッド作る
		{
			for (int i = 0;i < 15;++i)
			{
				pyramids_[i] = new GameObject();

				pyramids_[i]->transform_->position_ = pyramid_points[i];

				Sprite *sprite = new Sprite(BOX_TEXTURE_NAME);
				sprite->SetSize(Vector2(0.2f, 0.2f));
				sprite->SetColor(D3DCOLOR_RGBA(200, 153, 50, 255));
				pyramids_[i]->AddComponent(sprite);

				// 矩形の当たり判定の設定
				BoxInitializer box_init;
				box_init.width_ = 0.2f;
				box_init.height_ = 0.2f;
				box_init.pos_ = pyramids_[i]->transform_->position_;
				box_init.friction_ = 0.1f;
				box_init.fixed_rotation_ = false;

				BoxCollider *box_collider = new BoxCollider(box_init);
				pyramids_[i]->AddComponent(box_collider);

				// シーンにゲームオブジェクトを登録
				AddGameObject(pyramids_[i]);
			}
		}


		return S_OK;
	}

	void PhysicsTestScene::Update()
	{
		CircleCollider *circle_collider = dynamic_circle->GetComponent<CircleCollider>();

		RaycastHit hit_info = physics::PhysicsFunc::Raycast(
			dynamic_circle->transform_->position_ + Vector2::down() * 0.01f,
			Vector2::down(), 0.15f);

		if (hit_info.collider != nullptr)
			if (input::Input::Instance()->GetButtonDown(input::InputButton::Jump))
			{
				circle_collider->AddForce(Vector2::up() * 15.0f);
			}

		if (input::Input::Instance()->GetButtonDown(input::InputButton::Action))
		{
			static int z = 0;
			z = (z + 1) % 3;
			Camera::main_->SetZoom(0.5f + 0.33f * (z + 1));
		}

		Vector2 move = Vector2::zero();
		move.x = input::Input::Instance()->GetAxis(input::InputAxis::Horizontal);
		move.y = input::Input::Instance()->GetAxis(input::InputAxis::Vertical);

		dynamic_circle->GetComponent<CircleCollider>()->SetVelocity(move * 3.0f);

		if (input::Input::Instance()->GetButtonDown(input::InputButton::Cancel))
			SceneManager::LoadScene(new LightTestScene());
	}

	void PhysicsTestScene::Uninit()
	{
	}
}
