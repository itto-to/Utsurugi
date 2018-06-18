//==========================================================
// 概要  :最初のシーンクラス
// Author:Itsuki Namito
// Copyright(c) Utsurugi.All right reserved.
//==========================================================
#include "first_stage_scene.h"
#include "../../Base/2D/camera.h"
#include "../../Base/2D/sprite.h"
#include "../../Base/Light/light.h"
#include "../../Base/Input/input.h"
#include "../Stage/stage.h"
#include "../../Base/System/scene_manager.h"
#include "../Actor/Player/player.h"

#include "temp_ending.h"

#ifdef _DEBUG
#include "../../Base/Debug/debugger.h"
#endif

#include "../../Base/Physics/physics.h"
#include "../../Base/Time/time.h"

#define LIGHT_TEXTURE_NAME "Resources/Texture/LightBulb.png"
#define BACK_GROUND_TEXTURE_NAME "Resources/Texture/Stage/ForestBackGround.png"
#define CLEAR_GATE_TEXTURE_NAME "Resources/Texture/Stage/Gate.png"
#define PLAYER_TEXTURE_NAME "Resources/Texture/Character/newfox.png"
using namespace physics;

namespace
{
	const Vector2 kInitPlayerPos = Vector2(-200.0f, 0.0f);
}

namespace shadowpartner
{
	// コンストラクタ
	FirstStageScene::FirstStageScene(int phase_num)
		:StageScene(phase_num)
	{

	}

	// デストラクタ
	FirstStageScene::~FirstStageScene()
	{

	}

	// 初期化処理
	HRESULT FirstStageScene::Init()
	{
#ifdef _DEBUG
		debug::Debug::Log("シーンの切り替え：物理テスト");
#endif

		//カメラ
		{
			camera_object_ = new GameObject();
			camera_object_->transform_->position_ = Vector2::zero();

			Camera *camera = new Camera();
			camera_object_->AddComponent(camera);

			AddGameObject(camera_object_);
		}

		// 背景
		{
			back_ground_ = new GameObject();
			back_ground_->transform_->position_ = Vector2(1120, 0);

			Sprite *sprite = new Sprite(BACK_GROUND_TEXTURE_NAME);
			sprite->SetSize(Vector2(3360.0f, 630.0f));
			back_ground_->AddComponent(sprite);

			AddGameObject(back_ground_);
		}

		// ゲート
		{
			back_ground_ = new GameObject();
			back_ground_->transform_->position_ = Vector2(400, -160);

			Sprite *sprite = new Sprite(CLEAR_GATE_TEXTURE_NAME);
			sprite->SetSize(Vector2(100.0f, 150.0f));
			back_ground_->AddComponent(sprite);

			AddGameObject(back_ground_);

		}

		// Stage Fase1
		{
			stages_[0] = new GameObject();
			stages_[0]->transform_->position_ = Vector2(0.0f, 0.0f);

			Stage *stage = new Stage(StageNumber::kTest, *stages_[0], TILE_DATA, STAGE_PASS);
			stages_[0]->AddComponent(stage);

			AddGameObject(stages_[0]);
		}

		// プレイヤー
		{
			player_ = new GameObject();
			player_->transform_->position_ = kInitPlayerPos;

			Sprite *sprite = new Sprite(PLAYER_TEXTURE_NAME);
			sprite->SetSize(Vector2(100, 100));
			player_->AddComponent(sprite);
			Player *actor = new Player();
			player_->AddComponent(actor);

			// 矩形の当たり判定の設定
			BoxInitializer box_init;
			box_init.width_ = 100.0f;
			box_init.height_ = 100.0f;
			box_init.density_ = 0.00001f;
			box_init.body_type_ = kDynamicBody;
			box_init.is_trigger_ = false;
			box_init.pos_ = player_->transform_->position_;

			BoxCollider *box_collider = new BoxCollider(box_init);
			player_->AddComponent(box_collider);

			// シーンにゲームオブジェクトを登録
			AddGameObject(player_);

		}

		//{
		//	test = new GameObject();
		//	test->transform_->position_ = Vector2(100.0f, 150.0f);

		//	// スプライトの設定
		//	Sprite *sprite = new Sprite("Resources/Texture/WhiteCircle.png");
		//	sprite->SetSize(Vector2(30, 30));
		//	sprite->SetColor(D3DCOLOR_RGBA(255, 0, 0, 255));
		//	sprite->SetOrderInLayer(1);
		//	test->AddComponent(sprite);

		//	// 円形の当たり判定の設定
		//	CircleInitializer circle_init;
		//	circle_init.radius_ = 10.0f;
		//	circle_init.pos_ = test->transform_->position_;
		//	circle_init.body_type_ = kDynamicBody;

		//	CircleCollider *circle_collider = new CircleCollider(circle_init);
		//	test->AddComponent(circle_collider);

		//	// シーンにゲームオブジェクトを登録
		//	AddGameObject(test);
		//}		StageScene::Init();

		return S_OK;
	}

	void FirstStageScene::Update()
	{
		StageScene::Update();

		if (input::Input::Instance()->GetButtonDown(input::InputButton::Start))
			SceneManager::LoadScene(new TempEndingScene());

		if (input::Input::Instance()->GetButtonDown(input::InputButton::Skill))
		{
			NextPhase();
		}
		if (input::Input::Instance()->GetButtonDown(input::InputButton::Cancel))
		{
			PrevPhase();
		}
		if (input::Input::Instance()->GetButtonDown(input::InputButton::Action))
		{
			static int z = 0;
			z = (z + 1) % 3;
			Camera::main_->SetZoom(0.5f + 0.33f * (z + 1));
		}

	}

	void FirstStageScene::Uninit()
	{
		StageScene::Uninit();


	}
}
