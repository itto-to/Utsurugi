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
#include "../Actor/Player/shadow.h"
#include "../Actor/Player/shadow_state.h"
#include "../Actor/Player/landing_trigger.h"
#include "../Actor/Common/jumper.h"
#include "../../Base/Physics/Filter/collision_filter.h"
#include "../Actor/Player/gimmck_trigger.h"
#include "../Actor//Player//action_trigger.h"
#include "../Actor/Gimmick/tree.h"

#include "temp_ending.h"

#ifdef _DEBUG
#include "../../Base/Debug/debugger.h"
#endif

#include "../../Base/Physics/physics.h"
#include "../../Base/Time/time.h"


#include "../../Base/Light/corner_candidates.h"

#define LIGHT_TEXTURE_NAME "Resources/Texture/LightBulb.png"
#define BACK_GROUND_TEXTURE_NAME "Resources/Texture/Stage/ForestBackGround.png"
#define CLEAR_GATE_TEXTURE_NAME  "Resources/Texture/Stage/Gate.png"
#define PLAYER_TEXTURE_NAME      "Resources/Texture/Character/newfox.png"
#define LIGHT_TEXTURE_NAME       "Resources/Texture/white.png"
#define IVY_TEXTURE_NAME         "Resources/Texture/Stage/Ivy.png"
#define TREE_LOG_TEXTURE_NAME    "Resources/Texture/Stage/RoundWood.png"
#define LIGHT_TREE_TEXTURE_NAME  "Resources/Texture/Light/TreeLine.png"
#define FIREFLY_TEXTURE_NAME     "Resources/Texture/Light/FireFly.png"

using namespace physics;

namespace
{
	const Vector2 kInitPlayerPos = Vector2(2.0f, 3.0f);

	const float kPlayerWidth = 1.0f;
	const float kPlayerHeight = 1.0f;

	const Vector2 kTreeLogPosition = Vector2(3.5f, -1.1f);
	const float kTreeWidth = 0.2f;
	const float kTreeHeight = 2.0f;

	const Vector2 kFireflyPosition   = Vector2(1.0f, -1.2f);
	const Vector2 kFireflySpriteSize = Vector2(0.3f, 0.3f);
	const Vector2 kFireflyLightSize  = Vector2(2.0f, 2.0f);

	const Vector2 kLightTreePosition = Vector2(-2.0f, -0.6f);
	const Vector2 kLightTreeSpriteSize = Vector2(2.56f, 3.25f);
	const Vector2 kLightTreeLightSize = Vector2(3.0f, 3.0f);

	const float kShadowWidth = 1.0f;
	const float kShadowHeight = 1.0f;

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
			back_ground_->transform_->position_ = Vector2(11.2f, 0.0f);

			Sprite *sprite = new Sprite(BACK_GROUND_TEXTURE_NAME);
			sprite->SetSize(Vector2(33.6f, 6.3f));
			back_ground_->AddComponent(sprite);

			AddGameObject(back_ground_);
		}

		// ゲート
		{
			back_ground_ = new GameObject();
			back_ground_->transform_->position_ = Vector2(4.0f, -1.6f);

			Sprite *sprite = new Sprite(CLEAR_GATE_TEXTURE_NAME);
			sprite->SetSize(Vector2(1.0f, 1.5f));
			back_ground_->AddComponent(sprite);

			AddGameObject(back_ground_);

		}

		// Stage Fase1
		{
			stages_[0] = new GameObject();
			stages_[0]->transform_->position_ = Vector2(0.0f, 0.0f);

			Stage *stage = new Stage(StageNumber::kTest, *stages_[0]);
			stages_[0]->AddComponent(stage);

			CornerCandidates::PreCalculate(stage);

			AddGameObject(stages_[0]);

			
		}
		 
		// 発光樹（中ライト）生成
		{
			middle_light_ = new GameObject();
			middle_light_->transform_->position_ = kLightTreePosition;
			middle_light_->tag_ = Tag::kMiddleLight;

			// ライトツリーのスプライト設定
			Sprite *tree_sprite = new Sprite(LIGHT_TREE_TEXTURE_NAME);
			tree_sprite->SetSize(kLightTreeSpriteSize);
			middle_light_->AddComponent(tree_sprite);

			// 光のスプライト設定
			Sprite *sprite = new Sprite(LIGHT_TEXTURE_NAME);
			sprite->SetSize(kLightTreeLightSize);
			sprite->SetColor(D3DCOLOR_RGBA(0x00, 0x00, 0xff, 0x80));
			middle_light_->AddComponent(sprite);

			// 矩形の当たり判定の設定
			BoxInitializer box_init;
			box_init.pos_        = middle_light_->transform_->position_;
			box_init.width_      = 3.0f;
			box_init.height_     = 3.0f;
			box_init.body_type_  = kStaticBody;
			box_init.is_trigger_ = true;

			BoxCollider *box_collider = new BoxCollider(box_init);
			middle_light_->AddComponent(box_collider);

			// シーンにゲームオブジェクトを登録
			AddGameObject(middle_light_);
		}

		// ホタル（小ライト）生成
		{
			small_light_ = new GameObject();
			small_light_->transform_->position_ = kFireflyPosition;
			small_light_->tag_ = Tag::kSmallLight;

			// ホタルのスプライト設定
			Sprite *firefly_sprite = new Sprite(FIREFLY_TEXTURE_NAME);
			firefly_sprite->SetSize(kFireflySpriteSize);
			small_light_->AddComponent(firefly_sprite);

			// スプライトの設定
			Sprite *sprite = new Sprite(LIGHT_TEXTURE_NAME);
			sprite->SetSize(kFireflyLightSize);
			sprite->SetColor(D3DCOLOR_RGBA(0xff, 0x00, 0x00, 0x80));
			small_light_->AddComponent(sprite);

			// 矩形の当たり判定の設定
			BoxInitializer box_init;
			box_init.width_      = kFireflyLightSize.x;
			box_init.height_     = kFireflyLightSize.y;
			box_init.body_type_  = kStaticBody;
			box_init.is_trigger_ = true;
			box_init.pos_        = small_light_->transform_->position_;

			BoxCollider *box_collider = new BoxCollider(box_init);
			small_light_->AddComponent(box_collider);

			// シーンにゲームオブジェクトを登録
			AddGameObject(small_light_);
		}

		// ツタの生成
		{
			vine_ = new GameObject();
			vine_->transform_->position_ = Vector2(-4.0f, 0.0f);
			vine_->tag_                  = Tag::kClimb;

			Sprite *sprite = new Sprite(IVY_TEXTURE_NAME);
			sprite->SetSize(Vector2(0.5f, 4.0f));
			sprite->SetColor(D3DCOLOR_ARGB(0xff, 0x00, 0xff, 0x00));
			vine_->AddComponent(sprite);


			// 矩形の当たり判定の設定
			BoxInitializer box_init;
			box_init.pos_        = vine_->transform_->position_;
			box_init.width_      = 0.5f;
			box_init.height_     = 4.0f;
			box_init.density_    = 0.1f;
			box_init.body_type_  = kStaticBody;
			box_init.is_trigger_ = true;

			BoxCollider *box_collider = new BoxCollider(box_init);
			vine_->AddComponent(box_collider);

			// シーンにゲームオブジェクトを登録
			AddGameObject(vine_);
		}

		// 丸太の生成
		{
			tree_log_ = new GameObject();
			tree_log_->transform_->position_ = kTreeLogPosition;
			tree_log_->tag_ = Tag::kTree;

			// スプライト設定
			Sprite *sprite = new Sprite(TREE_LOG_TEXTURE_NAME);
			sprite->SetSize(Vector2(kTreeWidth, kTreeHeight));
			tree_log_->AddComponent(sprite);

			// 矩形の当たり判定の設定
			BoxInitializer box_init;
			box_init.width_          = kTreeWidth;
			box_init.height_         = kTreeHeight;
			box_init.density_        = 1000.0f;
			box_init.friction_       = 1000.0f;
			box_init.body_type_      = kDynamicBody;
			box_init.fixed_rotation_ = false;
			box_init.is_trigger_     = false;
			//box_init.offset_         = Vector2(0.0f, kTreeHeight / 2.0f);
			box_init.category_bits_  = CollisionFilter::kActionObject;
			box_init.mask_bits_      = CollisionFilter::kDefaultMask | CollisionFilter::kActionTrigger;

			BoxCollider *box_collider = new BoxCollider(box_init);

			tree_log_->AddComponent(box_collider);


			Tree *tree_component = new Tree();
			tree_log_->AddComponent(tree_component);

			AddGameObject(tree_log_);
		}

		// ヒンジの土台を作る
		{
			hinge_joint_base_ = new GameObject();
			hinge_joint_base_->transform_->position_ = Vector2(kTreeLogPosition.x, kTreeLogPosition.y - 1.0f);

			// 矩形の当たり判定の設定
			BoxInitializer box_init;
			box_init.width_ = 1.0f;
			box_init.height_ = 1.0f;
			box_init.pos_ = hinge_joint_base_->transform_->position_;
			box_init.body_type_ = BodyType::kStaticBody;
			box_init.is_trigger_ = true;

			BoxCollider *box_collider = new BoxCollider(box_init);
			hinge_joint_base_->AddComponent(box_collider);
		}

		// 樹をつなぐヒンジを作る
		{
			hinge_joint_ = new GameObject();

			hinge_joint_->transform_->position_ = kTreeLogPosition;

			RevoluteInitializer ri;
			ri.collider_a_ = tree_log_->GetComponent<BoxCollider>();
			ri.local_anchor_a_ = Vector2(-kTreeWidth / 2.0f, -kTreeHeight / 2.0f);
			ri.collider_b_ = hinge_joint_base_->GetComponent<BoxCollider>();
			ri.local_anchor_b_ = Vector2(0.0f, 0.0f);
			ri.world_pos_ = hinge_joint_->transform_->position_;

			ri.enable_limit_ = true;
			ri.lower_angle_ = -90.0f;
			ri.upper_angle_ = 0.0f;

			RevoluteJoint *revolute_joint = new RevoluteJoint(ri);
			hinge_joint_->AddComponent(revolute_joint);

			AddGameObject(hinge_joint_);
		}

		// プレイヤーを生成
		{

			player_ = new GameObject();
			player_->transform_->position_ = kInitPlayerPos;
			player_->tag_ = Tag::kPlayer;

			Sprite *sprite = new Sprite(PLAYER_TEXTURE_NAME);
			sprite->SetSize(Vector2(1.0f, 1.0f));

			player_->AddComponent(sprite);

			// 矩形の当たり判定の設定
			BoxInitializer box_init;
			box_init.width_         = kPlayerWidth;
			box_init.height_        = kPlayerHeight;
			box_init.density_       = 1.0f;
			box_init.friction_      = 0.0f;
			box_init.body_type_     = kDynamicBody;
			box_init.is_trigger_    = false;
			box_init.category_bits_ = CollisionFilter::kPlayer;
			box_init.mask_bits_     = ~CollisionFilter::kShadow;	// 影とだけ衝突しない

			BoxCollider *box_collider = new BoxCollider(box_init);
			box_collider->SetSleepingAllowed(false);	// Sleepを許可しない
			player_->AddComponent(box_collider);

			// ギミックトリガーの設定
			BoxInitializer gimmick_init;
			gimmick_init.body_type_     = kDynamicBody;
			gimmick_init.gravity_scale_ = 0.0f;
			gimmick_init.pos_           = player_->transform_->position_;
			gimmick_init.width_         = kPlayerWidth;
			gimmick_init.height_        = kPlayerHeight;
			gimmick_init.is_trigger_    = true;
			gimmick_init.offset_        = Vector2::zero();
			gimmick_init.category_bits_ = CollisionFilter::kPlayer;
			gimmick_init.category_bits_ = CollisionFilter::kShadow;	// 影とだけ反応する

			GimmickTrigger *gimmick_trigger = new GimmickTrigger(gimmick_init);
			gimmick_trigger->SetSleepingAllowed(false);
			player_->AddComponent(gimmick_trigger);

			// 着地トリガーの設定
			BoxInitializer land_init;
			land_init.body_type_     = kDynamicBody;
			land_init.gravity_scale_ = 0.0f;
			land_init.pos_           = player_->transform_->position_;
			land_init.width_         = kPlayerWidth;
			land_init.height_        = 0.1f;
			land_init.offset_        = Vector2(0.0f, -kPlayerHeight / 2);
			land_init.is_trigger_    = true;
			land_init.category_bits_ = CollisionFilter::kPlayer;
			land_init.mask_bits_     = CollisionFilter::kDefaultCategory | CollisionFilter::kClimb | CollisionFilter::kActionObject;

			LandingTrigger *land_trigger = new LandingTrigger(land_init);
			land_trigger->SetSleepingAllowed(false);
			player_->AddComponent(land_trigger);

			// アクショントリガーの設定
			BoxInitializer act_init;
			act_init.body_type_     = kDynamicBody;
			act_init.gravity_scale_ = 0.0f;
			act_init.pos_           = player_->transform_->position_;
			act_init.width_         = 0.2f;
			act_init.height_        = kPlayerHeight;
			act_init.offset_        = Vector2(kPlayerWidth / 2, 0.0f);
			act_init.is_trigger_    = true;
			act_init.category_bits_ = CollisionFilter::kActionTrigger;
			act_init.mask_bits_     = CollisionFilter::kActionObject;

			ActionTrigger *act_trigger = new ActionTrigger(act_init);
			act_trigger->SetSleepingAllowed(false);
			player_->AddComponent(act_trigger);

			Jumper *jumper = new Jumper();
			player_->AddComponent(jumper);

			Player *player_component = new Player();
			player_->AddComponent(player_component);

			// シーンにゲームオブジェクトを登録
			AddGameObject(player_);
		}

		// 影を生成
		{
			shadow_ = new GameObject();
			shadow_->transform_->position_ = player_->transform_->position_ + Vector2::down() * 1.0f;
			shadow_->tag_ = Tag::kShadow;

			Sprite *sprite = new Sprite(PLAYER_TEXTURE_NAME);
			sprite->SetSize(Vector2(kShadowWidth, kShadowHeight));
			sprite->SetColor(D3DCOLOR_RGBA(0, 0, 0, 0xff));
			shadow_->AddComponent(sprite);

			// 矩形の当たり判定の設定
			BoxInitializer box_init;
			box_init.pos_           = shadow_->transform_->position_;
			box_init.width_         = kShadowWidth;
			box_init.height_        = kShadowHeight;
			box_init.friction_      = 0.0f;
			box_init.body_type_     = kStaticBody;
			box_init.is_trigger_    = true;
			box_init.mask_bits_     = CollisionFilter::kShadow;
			box_init.category_bits_ = ~CollisionFilter::kPlayer;	// プレイヤーとは衝突しない

			BoxCollider *box_collider = new BoxCollider(box_init);
			shadow_->AddComponent(box_collider);

			// ギミックトリガーの設定
			BoxInitializer gimmick_init;
			gimmick_init.body_type_ = kDynamicBody;
			gimmick_init.gravity_scale_ = 0.0f;
			gimmick_init.pos_ = player_->transform_->position_;
			gimmick_init.width_ = kShadowWidth;
			gimmick_init.height_ = kShadowHeight;
			gimmick_init.is_trigger_ = true;
			gimmick_init.offset_ = Vector2::zero();
			gimmick_init.category_bits_ = CollisionFilter::kPlayer;
			gimmick_init.category_bits_ = CollisionFilter::kShadow;	// 影とだけ反応する

			GimmickTrigger *gimmick_trigger = new GimmickTrigger(gimmick_init);
			gimmick_trigger->SetSleepingAllowed(false);

			shadow_->AddComponent(gimmick_trigger);

			// 着地トリガーの設定
			BoxInitializer land_init;
			land_init.body_type_     = kDynamicBody;
			land_init.gravity_scale_ = 0.0f;
			land_init.pos_           = player_->transform_->position_;
			land_init.width_         = kShadowWidth;
			land_init.height_        = 0.1f;
			land_init.offset_        = Vector2(0.0f, -kShadowHeight / 2);
			land_init.is_trigger_    = true;
			land_init.category_bits_ = CollisionFilter::kShadow;
			land_init.mask_bits_     = CollisionFilter::kDefaultCategory | CollisionFilter::kClimb | CollisionFilter::kActionObject;

			LandingTrigger *land_trigger = new LandingTrigger(land_init);
			land_trigger->SetSleepingAllowed(false);
			shadow_->AddComponent(land_trigger);

			Jumper *jumper = new Jumper();
			shadow_->AddComponent(jumper);

			Shadow *shadow = new Shadow();
			shadow->SetState(new ShadowState(shadow));
			shadow_->AddComponent(shadow);

			// プレイヤーのシャドウに登録
			shadow->SetPlayerObject(player_);
			player_->GetComponent<Player>()->shadow_object_ = shadow_;

			AddGameObject(shadow_);
		}


		// エネミーを生成
		{
			//enemy_ = new GameObject();
			//enemy_->transform_->position_ = player_->transform_->position_ + Vector2::down() * 1.0f;
			//enemy_->tag_ = Tag::kEnemy;

			//Sprite *sprite = new Sprite(PLAYER_TEXTURE_NAME);
			//sprite->SetSize(Vector2(1.0f, 1.0f));
			//sprite->SetColor(D3DCOLOR_RGBA(0, 0, 0, 0xff));
			//enemy_->AddComponent(sprite);
			//Shadow *shadow = new Shadow();
			//ShadowState *enemy_state = new ShadowState(shadow);
			//enemy_state->SetPlayer(player_);
			//shadow->SetState(enemy_state);
			//enemy_->AddComponent(shadow);

			//// 矩形の当たり判定の設定
			//BoxInitializer box_init;
			//box_init.pos_ = enemy_->transform_->position_;
			//box_init.width_ = 1.0f;
			//box_init.height_ = 1.0f;
			//box_init.friction_ = 0.0f;
			//box_init.body_type_ = kStaticBody;
			//box_init.is_trigger_ = true;
			//box_init.mask_bits_ = CollisionFilter::kEnemy;
			//box_init.category_bits_ = ~CollisionFilter::kPlayer;	// プレイヤーとは衝突しない

			//BoxCollider *box_collider = new BoxCollider(box_init);
			//enemy_->AddComponent(box_collider);

			//AddGameObject(enemy_);
		}
		
		StageScene::Init();

		return S_OK;
	}

	void FirstStageScene::Update()
	{
		StageScene::Update();

		//if (input::Input::Instance()->GetButtonDown(input::InputButton::Start))
		//	SceneManager::LoadScene(new TempEndingScene());

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

			z = (z + 1) % 16;
			Camera::main_->SetZoom(10.0f + 1.0f * (z - 9));
		}

		//static float rad = 0.0f;
		//rad += D3DXToRadian(0.1f);
		//moon_light_->GetComponent<Light>()->SetDirection(Vector2(cosf(rad),sinf(rad)));

	}

	void FirstStageScene::Uninit()
	{
		StageScene::Uninit();


	}
}
