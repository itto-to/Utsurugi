//==========================================================
// 概要  :ステージシーンの基底クラス
// Author:Itsuki Namito
// Copyright(c) Utsurugi.All right reserved.
//==========================================================
#include "stage_scene.h"
#include "../../Base/2D/camera.h"
#include "../../Base/2D/sprite.h"
#include "../../Base/Light/light.h"
#include "../../Base/Input/input.h"
#include "../../Base/System/scene_manager.h"
#include "../../Base/Physics/Element/light_collider.h"

#ifdef _DEBUG
#include "../../Base/Debug/debugger.h"
#endif

#include "../../Base/Physics/physics.h"
#include "../../Base/Time/time.h"

#define BACK_GROUND_TEXTURE_NAME "Resources/Texture/BackGround/BackGround.png"
#define BACK_GROUND_SIZE Vector2(11.2f,6.3f)
#define BACK_GROUND_TREE1_NAME "Resources/Texture/BackGround/Tree1.png"
#define BACK_GROUND_TREE1_SIZE Vector2(1.28f,2.575f)
#define BACK_GROUND_TREE2_NAME "Resources/Texture/BackGround/Tree2.png"
#define BACK_GROUND_TREE2_SIZE Vector2(2.56f,2.625f)

namespace shadowpartner
{
	// コンストラクタ
	StageScene::StageScene(int phase_num)
		:phase_num_(phase_num)
	{

	}

	// デストラクタ
	StageScene::~StageScene()
	{

	}

	// 初期化処理
	HRESULT StageScene::Init()
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

			AddGameObject(camera_object_);
		}

		// 背景の作成
		CreateBackGround();

		// 月の光を生成
		{
			moon_light_ = new GameObject();
			moon_light_->transform_->position_ = Vector2(0.0f, 30.0f);
			moon_light_->tag_ = Tag::kLargeLight;

			LightInitializer light_init;
			light_init.radius_ = 60.0f;
			light_init.color_ = D3DCOLOR_RGBA(0xff, 0xff, 0xff, 0x10);
			light_init.direction_ = Angle(Vector2::down());
			light_init.angle_ = 30.0f;
			Light *light = new Light(light_init);
			moon_light_->AddComponent(light);

			// コライダーを追加
			//physics::LightCollider *light_collider = new physics::LightCollider();
			//moon_light_->AddComponent(light_collider);

			AddGameObject(moon_light_);
		}

		current_phase_ = 0;

		return S_OK;
	}

	static int light_radius_scale = 0;

	void StageScene::Update()
	{
	}

	void StageScene::Uninit()
	{

	}

	void StageScene::NextPhase()
	{
		if (current_phase_ < phase_num_ - 1)
		{
			++current_phase_;

			CameraAdjustToCurrentPhase();
		}
	}

	void StageScene::PrevPhase()
	{
		if (current_phase_ > 0)
		{
			--current_phase_;

			CameraAdjustToCurrentPhase();
		}
	}

	void StageScene::CameraAdjustToCurrentPhase()
	{
		Camera::main_->SetPosition(Vector2(current_phase_ * 11.2f, 0.0f));
	}

	//==========================================================
	// 概要  :ステージの背景を作ります。
	//==========================================================
	void StageScene::CreateBackGround()
	{
		Sprite *sprite;
		{
			back_ground_ = new GameObject();
			back_ground_->transform_->position_ = Vector2(0.0f, 0.0f);

			sprite = new Sprite(BACK_GROUND_TEXTURE_NAME);
			sprite->SetSize(BACK_GROUND_SIZE);
			sprite->SetColor(D3DCOLOR_RGBA(0xff, 0xff, 0xff, 0xff));
			back_ground_->AddComponent(sprite);

			AddGameObject(back_ground_);
		}

		{
			back_ground_objects_[0] = new GameObject();
			back_ground_objects_[0]->transform_->position_ = Vector2(-4.0f, -0.85f);

			sprite = new Sprite(BACK_GROUND_TREE1_NAME);
			sprite->SetSize(BACK_GROUND_TREE1_SIZE);
			sprite->SetColor(D3DCOLOR_RGBA(0xff, 0xff, 0xff, 0x60));
			back_ground_objects_[0]->AddComponent(sprite);

			AddGameObject(back_ground_objects_[0]);
		}

		{
			back_ground_objects_[1] = new GameObject();
			back_ground_objects_[1]->transform_->position_ = Vector2(3.0f, -0.85f);

			sprite = new Sprite(BACK_GROUND_TREE1_NAME);
			sprite->SetSize(BACK_GROUND_TREE1_SIZE);
			sprite->SetColor(D3DCOLOR_RGBA(0xff, 0xff, 0xff, 0xa0));
			back_ground_objects_[1]->AddComponent(sprite);

			AddGameObject(back_ground_objects_[1]);
		}

		{
			back_ground_objects_[2] = new GameObject();
			back_ground_objects_[2]->transform_->position_ = Vector2(-2.5f, -1.2f);

			sprite = new Sprite(BACK_GROUND_TREE1_NAME);
			sprite->SetSize(BACK_GROUND_TREE1_SIZE * 0.7f);
			sprite->SetColor(D3DCOLOR_RGBA(0xff, 0xff, 0xff, 0xa0));
			back_ground_objects_[2]->AddComponent(sprite);

			AddGameObject(back_ground_objects_[2]);
		}

		{
			back_ground_objects_[3] = new GameObject();
			back_ground_objects_[3]->transform_->position_ = Vector2(1.0f, 2.0f);

			sprite = new Sprite(BACK_GROUND_TREE2_NAME);
			sprite->SetSize(BACK_GROUND_TREE2_SIZE * 0.8f);
			sprite->SetColor(D3DCOLOR_RGBA(0xff, 0xff, 0xff, 0xa0));
			back_ground_objects_[3]->AddComponent(sprite);

			AddGameObject(back_ground_objects_[3]);
		}

		{
			back_ground_objects_[4] = new GameObject();
			back_ground_objects_[4]->transform_->position_ = Vector2(-3.0f, 2.1f);

			sprite = new Sprite(BACK_GROUND_TREE2_NAME);
			sprite->SetSize(BACK_GROUND_TREE2_SIZE * 0.6f);
			sprite->SetColor(D3DCOLOR_RGBA(0xff, 0xff, 0xff, 0xa0));
			back_ground_objects_[4]->AddComponent(sprite);

			AddGameObject(back_ground_objects_[4]);
		}

		{
			back_ground_objects_[5] = new GameObject();
			back_ground_objects_[5]->transform_->position_ = Vector2(3.5f, -0.7f);

			sprite = new Sprite(BACK_GROUND_TREE1_NAME);
			sprite->SetSize(BACK_GROUND_TREE1_SIZE * 1.2f);
			sprite->SetColor(D3DCOLOR_RGBA(0xff, 0xff, 0xff, 0xff));
			back_ground_objects_[5]->AddComponent(sprite);

			AddGameObject(back_ground_objects_[5]);
		}

		{
			back_ground_objects_[6] = new GameObject();
			back_ground_objects_[6]->transform_->position_ = Vector2(-3.5f, -1.35f);

			sprite = new Sprite(BACK_GROUND_TREE1_NAME);
			sprite->SetSize(BACK_GROUND_TREE1_SIZE * 0.6f);
			sprite->SetColor(D3DCOLOR_RGBA(0xff, 0xff, 0xff, 0xff));
			back_ground_objects_[6]->AddComponent(sprite);

			AddGameObject(back_ground_objects_[6]);
		}

	}
}
