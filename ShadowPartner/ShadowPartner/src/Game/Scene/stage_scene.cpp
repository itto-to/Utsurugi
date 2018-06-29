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

		// 月の光を生成
		{
			//moon_light_ = new GameObject();
			//moon_light_->transform_->position_ = Vector2(10.0f, 30.0f);
			//moon_light_->tag_ = Tag::kLargeLight;

			//LightInitializer light_init;
			//light_init.radius_ = 60.0f;
			//light_init.color_ = D3DCOLOR_RGBA(0xff, 0xff, 0xff, 0x28);
			//light_init.direction_ = Angle(Vector2::down());
			//light_init.angle_ = 90.0f;
			//Light *light = new Light(light_init);
			//moon_light_->AddComponent(light);

			//// コライダーを追加
			//physics::LightCollider *light_collider = new physics::LightCollider();
			//moon_light_->AddComponent(light_collider);

			//AddGameObject(moon_light_);
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
}
