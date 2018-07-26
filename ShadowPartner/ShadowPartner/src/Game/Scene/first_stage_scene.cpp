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
#include "../Actor/Gimmick/chain.h"
#include "../Actor//Player//action_trigger.h"
#include "../Actor/Gimmick/tree.h"
#include "../Actor/Gimmick/gate.h"
#include "../Scene/title_scene.h"

// Fase 3
#include "../Actor/Gimmick/observable_switch.h"
#include "../Actor/Gimmick/observer_gate.h"

#include "temp_ending.h"

#ifdef _DEBUG
#include "../../Base/Debug/debugger.h"
#endif

#include "../../Base/Physics/physics.h"
#include "../../Base/Time/time.h"


#include "../../Base/Light/corner_candidates.h"

#define WHITE_TEXTURE_NAME       "Resources/Texture/white.png"
#define BACK_GROUND_TEXTURE_NAME "Resources/Texture/Stage/ForestBackGround.png"
#define CLEAR_GATE_TEXTURE_NAME  "Resources/Texture/Stage/Gate.png"
#define PLAYER_TEXTURE_NAME      "Resources/Texture/Character/PlayerWalk.png"
#define LIGHT_TEXTURE_NAME       "Resources/Texture/Light/Light.png"
#define IVY_TEXTURE_NAME         "Resources/Texture/Stage/Ivy.png"
#define TREE_LOG_TEXTURE_NAME    "Resources/Texture/Stage/RoundWood.png"
#define LIGHT_TREE_TEXTURE_NAME  "Resources/Texture/Light/TreeLine.png"
#define FIREFLY_TEXTURE_NAME     "Resources/Texture/Light/FireFly.png"
#define NEEDLE_GATE_TEXTURE_NAME "Resources/Texture/Stage/Needle.png"
#define SWITCH_TEXTURE_NAME      "Resources/Texture/white.png"

using namespace physics;

namespace
{
	const Vector2 kInitPlayerPos = Vector2(-4.0f, -1.0f);

	const float kPlayerWidth  = 2.0f;
	const float kPlayerHeight = 1.0f;

	const Vector2 kPlayerColliderSize = Vector2(1.1f, 0.75f);
	const Vector2 kPlayerSpriteOffset = Vector2(-0.45f, 0.0f);	// 右向き時のオフセット

	const float kLandingTriggerHeight = 0.1f;

	const Vector2 kTreeLogPosition = Vector2(2.0f, -1.1f);
	const float kTreeWidth  = 0.2f;
	const float kTreeHeight = 2.0f;

	const Vector2 kFireflyPosition = Vector2(-4.0f, -1.4f);
	const Vector2 kFireflySpriteSize = Vector2(0.3f, 0.3f);
	const Vector2 kFireflyLightSize = Vector2(2.0f, 2.0f);

	const Vector2 kLightTreePosition   = Vector2(-1.5f, -0.6f);
	const Vector2 kLightTreeSpriteSize = Vector2(2.56f, 3.25f);
	const Vector2 kLightTreeLightSize  = Vector2(3.0f, 3.0f);

	const float kShadowWidth  = 2.0f;
	const float kShadowHeight = 1.0f;

	const Vector2 kPlayerUVSize = Vector2(0.25f, 0.25f);
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
		StageScene::Init();

		//// 大ライト1（仮）
		//{
		//	const int kWidth = 4;
		//	const int kHeight = 16;

		//	tmp_large_light_[0] = new GameObject();
		//	tmp_large_light_[0]->transform_->position_ = Vector2(-4.90f, 0.6f);
		//	tmp_large_light_[0]->tag_ = Tag::kLargeLight;

		//	//Sprite *sprite = new Sprite(WHITE_TEXTURE_NAME);
		//	//sprite->SetSize(Vector2(0.35 * kWidth, 0.35 * kHeight));
		//	//sprite->SetColor(D3DCOLOR_RGBA(0xff, 0xff, 0xff, 0x28));
		//	//tmp_large_light_[0]->AddComponent(sprite);

		//	BoxInitializer box_init;
		//	box_init.pos_           = tmp_large_light_[0]->transform_->position_;
		//	box_init.width_         = 0.35 * kWidth;
		//	box_init.height_        = 0.35 * kHeight;
		//	box_init.body_type_     = kStaticBody;
		//	box_init.is_trigger_    = true;
		//	box_init.gravity_scale_ = 0.0f;
		//	box_init.category_bits_ = CollisionFilter::kLight;
		//	box_init.mask_bits_     = CollisionFilter::kGimmickTrigger;

		//	BoxCollider *box_col = new BoxCollider(box_init);
		//	tmp_large_light_[0]->AddComponent(box_col);

		//	AddGameObject(tmp_large_light_[0]);
		//}

		//// 大ライト2（仮）
		//{
		//	const int kWidth = 10;
		//	const int kHeight = 5;

		//	tmp_large_light_[1] = new GameObject();
		//	tmp_large_light_[1]->transform_->position_ = Vector2(-2.45f, 2.27f);
		//	tmp_large_light_[1]->tag_ = Tag::kLargeLight;

		//	//Sprite *sprite = new Sprite(WHITE_TEXTURE_NAME);
		//	//sprite->SetSize(Vector2(0.35 * kWidth, 0.35 * kHeight));
		//	//sprite->SetColor(D3DCOLOR_RGBA(0xff, 0xff, 0xff, 0x28));
		//	//tmp_large_light_[1]->AddComponent(sprite);

		//	BoxInitializer box_init;
		//	box_init.pos_ = tmp_large_light_[1]->transform_->position_;
		//	box_init.width_ = 0.35 * kWidth;
		//	box_init.height_ = 0.35 * kHeight;
		//	box_init.body_type_ = kStaticBody;
		//	box_init.is_trigger_ = true;
		//	box_init.gravity_scale_ = 0.0f;
		//	box_init.category_bits_ = CollisionFilter::kLight;
		//	box_init.mask_bits_ = CollisionFilter::kGimmickTrigger;

		//	BoxCollider *box_col = new BoxCollider(box_init);
		//	tmp_large_light_[1]->AddComponent(box_col);

		//	AddGameObject(tmp_large_light_[1]);
		//}

		//// 大ライト3（仮）
		//{
		//	const int kWidth =7;
		//	const int kHeight = 6;

		//	tmp_large_light_[2] = new GameObject();
		//	tmp_large_light_[2]->transform_->position_ = Vector2(0.525f, 2.10f);
		//	tmp_large_light_[2]->tag_ = Tag::kLargeLight;

		//	//Sprite *sprite = new Sprite(WHITE_TEXTURE_NAME);
		//	//sprite->SetSize(Vector2(0.35 * kWidth, 0.35 * kHeight));
		//	//sprite->SetColor(D3DCOLOR_RGBA(0xff, 0xff, 0xff, 0x28));
		//	//tmp_large_light_[2]->AddComponent(sprite);

		//	BoxInitializer box_init;
		//	box_init.pos_ = tmp_large_light_[2]->transform_->position_;
		//	box_init.width_ = 0.35 * kWidth;
		//	box_init.height_ = 0.35 * kHeight;
		//	box_init.body_type_ = kStaticBody;
		//	box_init.is_trigger_ = true;
		//	box_init.gravity_scale_ = 0.0f;
		//	box_init.category_bits_ = CollisionFilter::kLight;
		//	box_init.mask_bits_ = CollisionFilter::kGimmickTrigger;

		//	BoxCollider *box_col = new BoxCollider(box_init);
		//	tmp_large_light_[2]->AddComponent(box_col);

		//	AddGameObject(tmp_large_light_[2]);
		//}

		//// 大ライト4（仮）
		//{
		//	const int kWidth = 11;
		//	const int kHeight = 16;

		//	tmp_large_light_[3] = new GameObject();
		//	tmp_large_light_[3]->transform_->position_ = Vector2(3.675f, 0.6f);
		//	tmp_large_light_[3]->tag_ = Tag::kLargeLight;

		//	//Sprite *sprite = new Sprite(WHITE_TEXTURE_NAME);
		//	//sprite->SetSize(Vector2(0.35 * kWidth, 0.35 * kHeight));
		//	//sprite->SetColor(D3DCOLOR_RGBA(0xff, 0xff, 0xff, 0x28));
		//	//tmp_large_light_[3]->AddComponent(sprite);

		//	BoxInitializer box_init;
		//	box_init.pos_ = tmp_large_light_[3]->transform_->position_;
		//	box_init.width_         = 0.35 * kWidth;
		//	box_init.height_        = 0.35 * kHeight;
		//	box_init.body_type_     = kStaticBody;
		//	box_init.is_trigger_    = true;
		//	box_init.gravity_scale_ = 0.0f;
		//	box_init.category_bits_ = CollisionFilter::kLight;
		//	box_init.mask_bits_     = CollisionFilter::kGimmickTrigger;

		//	BoxCollider *box_col = new BoxCollider(box_init);
		//	tmp_large_light_[3]->AddComponent(box_col);

		//	AddGameObject(tmp_large_light_[3]);
		//}


		// ゲート
		{
			gate_ = new GameObject();
			gate_->transform_->position_ = Vector2(4.5f, -1.6f);

			Sprite *sprite = new Sprite(CLEAR_GATE_TEXTURE_NAME);
			sprite->SetSize(Vector2(1.0f, 1.5f));
			gate_->AddComponent(sprite);

			BoxInitializer box_init;
			box_init.pos_           = gate_->transform_->position_;
			box_init.body_type_     = kDynamicBody;
			box_init.is_trigger_    = true;
			box_init.gravity_scale_ = 0.0f;
			box_init.width_         = 1.0f;
			box_init.height_        = 1.5f;
			box_init.category_bits_ = CollisionFilter::kActionObject;
			box_init.mask_bits_     = CollisionFilter::kActionTrigger;
			BoxCollider *box_col = new BoxCollider(box_init);
			gate_->AddComponent(box_col);


			Gate *gate_compo = new Gate();
			gate_->AddComponent(gate_compo);

			AddGameObject(gate_);
		}

		// Stage Fase1
		{
			stages_[0] = new GameObject();
			stages_[0]->transform_->position_ = Vector2(0.0f, 0.0f);

			Stage *stage = new Stage(StageNumber::kStage1_1, *stages_[0]);
			stages_[0]->AddComponent(stage);

			CornerCandidates::PreCalculate(stage);

			AddGameObject(stages_[0]);
		}

		// Stage Fase2
		//{
		//	stages_[1] = new GameObject();
		//	stages_[1]->transform_->position_ = Vector2(11.2f, 0.0f);

		//	Stage *stage = new Stage(StageNumber::kStage1_2, *stages_[1]);
		//	stages_[1]->AddComponent(stage);

		//	CornerCandidates::PreCalculate(stage);

		//	AddGameObject(stages_[1]);


		//}

		// Stage Fase3
		//{
		//	stages_[2] = new GameObject();
		//	stages_[2]->transform_->position_ = Vector2(22.4f, 0.0f);

		//	Stage *stage = new Stage(StageNumber::kStage1_3, *stages_[2]);
		//	stages_[2]->AddComponent(stage);

		//	CornerCandidates::PreCalculate(stage);

		//	AddGameObject(stages_[2]);
		//}


		// 発光樹（中ライト）生成
		{
			middle_light_ = new GameObject();
			middle_light_->transform_->position_ = kLightTreePosition;
			middle_light_->tag_ = Tag::kMiddleLight;

			// 光のスプライト設定
			Sprite *sprite = new Sprite(LIGHT_TEXTURE_NAME);
			sprite->SetSize(kLightTreeLightSize);
			sprite->SetColor(D3DCOLOR_RGBA(0xFF, 0xFF, 0xFF, 0xFF));
			middle_light_->AddComponent(sprite);

			// ライトツリーのスプライト設定
			Sprite *tree_sprite = new Sprite(LIGHT_TREE_TEXTURE_NAME);
			tree_sprite->SetSize(kLightTreeSpriteSize);
			middle_light_->AddComponent(tree_sprite);

			// 円形の当たり判定の設定
			CircleInitializer circle_init;
			circle_init.pos_ = middle_light_->transform_->position_;
			circle_init.radius_ = kLightTreeLightSize.x / 2.0f;
			circle_init.body_type_ = kStaticBody;
			circle_init.is_trigger_ = true;
			circle_init.gravity_scale_ = 0.0f;
			circle_init.category_bits_ = CollisionFilter::kLight;
			circle_init.mask_bits_     = CollisionFilter::kGimmickTrigger;

			CircleCollider *circle_collider = new CircleCollider(circle_init);
			middle_light_->AddComponent(circle_collider);

			// シーンにゲームオブジェクトを登録
			AddGameObject(middle_light_);
		}

		// ホタル（小ライト）生成
		{
			small_light_ = new GameObject();
			small_light_->transform_->position_ = kFireflyPosition;
			small_light_->tag_ = Tag::kSmallLight;

			// スプライトの設定
			Sprite *sprite = new Sprite(LIGHT_TEXTURE_NAME);
			sprite->SetSize(kFireflyLightSize);
			sprite->SetColor(D3DCOLOR_RGBA(0xFF, 0xFF, 0xFF, 0x80));
			small_light_->AddComponent(sprite);

			// ホタルのスプライト設定
			Sprite *firefly_sprite = new Sprite(FIREFLY_TEXTURE_NAME);
			firefly_sprite->SetSize(kFireflySpriteSize);
			small_light_->AddComponent(firefly_sprite);


			// 円形の当たり判定の設定
			CircleInitializer circle_init;
			circle_init.radius_ = kFireflyLightSize.x / 2.0f;
			circle_init.body_type_ = kStaticBody;
			circle_init.is_trigger_ = true;
			circle_init.pos_ = small_light_->transform_->position_;
			circle_init.gravity_scale_ = 0.0f;
			circle_init.category_bits_ = CollisionFilter::kLight;
			circle_init.mask_bits_ = CollisionFilter::kGimmickTrigger;

			CircleCollider *circle_collider = new CircleCollider(circle_init);
			small_light_->AddComponent(circle_collider);

			// シーンにゲームオブジェクトを登録
			AddGameObject(small_light_);
		}

		 //ツタの生成
		{
			//vine_ = new GameObject();
			//vine_->transform_->position_ = Vector2(-3.0f, 1.6f);
			//vine_->tag_ = Tag::kClimb;

			//ChainInitializer chain_init;
			//chain_init.first_pos_ = vine_->transform_->position_;
			//chain_init.next_diff_ = Vector2(0.2f, 0.0f);
			//chain_init.pieces_count_ = 15;
			//chain_init.piece_width_ = 0.3f;
			//chain_init.piece_height_ = 0.2f;
			////chain_init.is_trigger_ = true;
			//Chain *chain = new Chain(chain_init, this);
			//vine_->AddComponent(chain);

			//RevoluteInitializer revolute_init;
			//revolute_init.world_pos_ = Vector2(-3.0f, 1.6f);
			//revolute_init.collider_a_ = stages_[0]->GetComponent<TileMapCollider>();
			//revolute_init.collider_b_ = chain->first_;
			//revolute_init.local_anchor_a_ = Vector2(-3.0f, 1.4f);
			//revolute_init.local_anchor_b_ = Vector2::zero();
			//revolute_init.collide_connected_ = false;

			//RevoluteJoint *tree_ivy_joint = new RevoluteJoint(revolute_init);
			//box_init.category_bits_ = CollisionFilter::kClimb;
			//box_init.mask_bits_     = CollisionFilter::kGimmickTrigger;

			//vine_->AddComponent(tree_ivy_joint);

			//AddGameObject(vine_);

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
			box_init.body_type_        = kDynamicBody;
			box_init.fixed_rotation_   = false;
			box_init.is_trigger_       = false;
			//box_init.offset_         = Vector2(0.0f, kTreeHeight / 2.0f);
			box_init.width_ = kTreeWidth;
			box_init.height_ = kTreeHeight;
			box_init.category_bits_ = CollisionFilter::kActionObject;
			box_init.mask_bits_ = CollisionFilter::kDefaultMask | CollisionFilter::kActionTrigger;
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

			AddGameObject(hinge_joint_base_);
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
			ri.lower_angle_ = -89.0f;
			ri.upper_angle_ = 10.0f;

			RevoluteJoint *revolute_joint = new RevoluteJoint(ri);
			hinge_joint_->AddComponent(revolute_joint);

			AddGameObject(hinge_joint_);
		}

		// 丸太を固定する蔦
		{
			ivy_chain_ = new GameObject();
			ivy_chain_->transform_->position_ = Vector2(0.0f, 0.0f);

			ChainInitializer chain_init;
			chain_init.first_pos_ = Vector2(2.0f, 1.0f);
			chain_init.next_diff_ = Vector2(0.3f, 0.0f);
			chain_init.pieces_count_ = 6;
			chain_init.piece_width_ = 0.3f;
			chain_init.piece_height_ = 0.2f;
			Chain *chain = new Chain(chain_init, this);
			ivy_chain_->AddComponent(chain);

			RevoluteInitializer revolute_init;

			revolute_init.world_pos_ = Vector2(0.0f, 0.0f);
			revolute_init.collider_a_ = chain->last_;
			revolute_init.collider_b_ = stages_[0]->GetComponent<TileMapCollider>();
			revolute_init.local_anchor_a_ = Vector2::zero();
			revolute_init.local_anchor_b_ = Vector2(3.5f, -2.0f);

			RevoluteJoint *ivy_first_stage_joint = new RevoluteJoint(revolute_init);

			ivy_chain_->AddComponent(ivy_first_stage_joint);

			AddGameObject(ivy_chain_);
		}

		{
			ivy_joint_ = new GameObject();

			RevoluteInitializer revolute_init;
			revolute_init.world_pos_ = Vector2(0.0f, 0.0f);
			revolute_init.collider_a_ = tree_log_->GetComponent<BoxCollider>();
			revolute_init.collider_b_ = ivy_chain_->GetComponent<Chain>()->first_;
			revolute_init.local_anchor_a_ = Vector2::Vector2(0.0f, 0.7f);
			revolute_init.local_anchor_b_ = Vector2::zero();
			revolute_init.collide_connected_ = false;

			RevoluteJoint *tree_ivy_joint = new RevoluteJoint(revolute_init);

			ivy_joint_->AddComponent(tree_ivy_joint);

			AddGameObject(ivy_joint_);
		}

		// プレイヤーを生成
		{
			player_ = new GameObject();
			player_->transform_->position_ = kInitPlayerPos;
			player_->tag_ = Tag::kPlayer;

			Sprite *sprite = new Sprite(PLAYER_TEXTURE_NAME);
			sprite->SetSize(Vector2(kPlayerWidth, kPlayerHeight));
			sprite->SetUvSize(kPlayerUVSize);
			sprite->SetUvOffset(Vector2::zero());
			sprite->SetOffset(kPlayerSpriteOffset);

			player_->AddComponent(sprite);

			// 矩形の当たり判定の設定
			BoxInitializer box_init;
			box_init.width_         = kPlayerColliderSize.x;
			box_init.height_        = kPlayerColliderSize.y;
			box_init.density_       = 1.0f;
			box_init.friction_      = 0.0f;
			box_init.gravity_scale_ = 1.0f;
			box_init.body_type_     = kDynamicBody;
			box_init.is_trigger_    = false;
			box_init.category_bits_ = CollisionFilter::kPlayer;
			box_init.mask_bits_     = ~(CollisionFilter::kShadow | CollisionFilter::kIvy);	// 影とだけ衝突しない

			BoxCollider *box_collider = new BoxCollider(box_init);
			box_collider->SetSleepingAllowed(false);	// Sleepを許可しない
			player_->AddComponent(box_collider);

			// ギミックトリガーの設定
			BoxInitializer gimmick_init;
			gimmick_init.body_type_     = kDynamicBody;
			gimmick_init.gravity_scale_ = 0.0f;
			gimmick_init.pos_           = player_->transform_->position_;
			gimmick_init.width_         = kPlayerColliderSize.x;
			gimmick_init.height_        = kPlayerColliderSize.y;
			gimmick_init.is_trigger_    = true;
			gimmick_init.offset_        = Vector2::zero();
			gimmick_init.category_bits_ = CollisionFilter::kGimmickTrigger;
			gimmick_init.mask_bits_     = CollisionFilter::kLight | CollisionFilter::kClimb;	// 光とツタだけ反応する

			GimmickTrigger *gimmick_trigger = new GimmickTrigger(gimmick_init);
			gimmick_trigger->SetSleepingAllowed(false);
			player_->AddComponent(gimmick_trigger);

			// 着地トリガーの設定
			BoxInitializer land_init;
			land_init.body_type_         = kDynamicBody;
			land_init.gravity_scale_     = 0.0f;
			land_init.is_trigger_        = true;
			land_init.pos_               = player_->transform_->position_;
			land_init.width_             = kPlayerColliderSize.x - 0.1f;
			land_init.height_            = kLandingTriggerHeight;
			land_init.offset_            = Vector2(0.0f, -kPlayerColliderSize.y / 2.0f);
			land_init.is_trigger_        = true;
			land_init.category_bits_     = CollisionFilter::kLandingTirgger;
			land_init.mask_bits_         = CollisionFilter::kPlatform | CollisionFilter::kClimb | CollisionFilter::kActionObject;
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
			player_component->SetRespawnPoint(kInitPlayerPos);
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
			sprite->SetUvSize(kPlayerUVSize);
			sprite->SetUvOffset(Vector2::zero());
			sprite->SetFlipY(true);
			shadow_->AddComponent(sprite);

			// 矩形の当たり判定の設定
			BoxInitializer box_init;
			box_init.mask_bits_     = CollisionFilter::kShadow;
			box_init.density_       = 1.0f;
			box_init.friction_      = 0.0f;
			box_init.body_type_     = kStaticBody;
			box_init.is_trigger_    = true;
			box_init.mask_bits_     = CollisionFilter::kShadow;
			box_init.category_bits_ = ~CollisionFilter::kPlayer;	// プレイヤーとは衝突しない

			BoxCollider *box_collider = new BoxCollider(box_init);
			shadow_->AddComponent(box_collider);

			// ギミックトリガーの設定
			BoxInitializer gimmick_init;
			gimmick_init.body_type_     = kDynamicBody;
			gimmick_init.width_         = kMiddleShadowCollisionSize.x;
			gimmick_init.height_        = kMiddleShadowCollisionSize.y;
			gimmick_init.gravity_scale_ = 0.0f;
			gimmick_init.pos_           = shadow_->transform_->position_;
			gimmick_init.is_trigger_    = true;
			gimmick_init.offset_        = Vector2::zero();
			gimmick_init.category_bits_ = CollisionFilter::kGimmickTrigger;
			gimmick_init.mask_bits_     = CollisionFilter::kLight | CollisionFilter::kClimb;	// 光とツタだけ反応する

			GimmickTrigger *gimmick_trigger = new GimmickTrigger(gimmick_init);
			gimmick_trigger->SetSleepingAllowed(false);
			shadow_->AddComponent(gimmick_trigger);

			// 着地トリガーの設定
			BoxInitializer land_init;
			land_init.body_type_     = kDynamicBody;
			land_init.gravity_scale_ = 0.0f;
			land_init.pos_           = player_->transform_->position_;
			land_init.width_         = kMiddleShadowCollisionSize.x;
			land_init.height_        = kLandingTriggerHeight;
			land_init.offset_        = Vector2(0.0f, -kMiddleShadowCollisionSize.y / 2);
			land_init.is_trigger_    = true;
			land_init.category_bits_ = CollisionFilter::kShadow;
			land_init.mask_bits_     = CollisionFilter::kPlatform | CollisionFilter::kClimb | CollisionFilter::kActionObject;

			LandingTrigger *land_trigger = new LandingTrigger(land_init);
			land_trigger->SetSleepingAllowed(false);
			shadow_->AddComponent(land_trigger);

			// アクショントリガーの設定
			BoxInitializer act_init;
			act_init.body_type_     = kDynamicBody;
			act_init.gravity_scale_ = 0.0f;
			act_init.pos_           = shadow_->transform_->position_;
			act_init.width_         = 0.2f;
			act_init.height_        = kPlayerHeight;
			act_init.offset_        = Vector2(kPlayerWidth / 2, 0.0f);
			act_init.is_trigger_    = true;
			act_init.category_bits_ = CollisionFilter::kActionTrigger;
			act_init.mask_bits_     = CollisionFilter::kActionObject;

			ActionTrigger *act_trigger = new ActionTrigger(act_init);
			act_trigger->SetSleepingAllowed(false);
			shadow_->AddComponent(act_trigger);


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

		{
			//test_object_ = new GameObject();
			//test_object_->transform_->position_ = Vector2(-5.425f, 0.525f);
			//Sprite *sprite = new Sprite("Resources/Texture/white");
			//sprite->SetSize(Vector2(0.35f,5.25f));
			//sprite->SetColor(D3DCOLOR_RGBA(0xff, 0x00, 0x00, 0x55));

			//test_object_->AddComponent(sprite);

			//AddGameObject(test_object_);
		}

		// Fase 3
		{
			// とげのゲート
			observer_gate_ = new GameObject();
			observer_gate_->transform_->position_ = Vector2(22.0f, -2.0f);

			Sprite *sprite = new Sprite(NEEDLE_GATE_TEXTURE_NAME);
			sprite->SetSize(Vector2(1.0f, 1.0f));
			observer_gate_->AddComponent(sprite);

			BoxInitializer box_init;
			box_init.pos_ = observer_gate_->transform_->position_;
			box_init.width_ = 1.0f;
			box_init.height_ = 1.0f;
			box_init.category_bits_ = CollisionFilter::kPlatform;
			box_init.mask_bits_ = CollisionFilter::kPlayer;
			box_init.body_type_ = BodyType::kKinematicBody;

			BoxCollider *box_collider = new BoxCollider(box_init);
			observer_gate_->AddComponent(box_collider);

			ObserverGate *og = new ObserverGate();
			og->SetClosePos(observer_gate_->transform_->position_);
			og->SetOpenPos(observer_gate_->transform_->position_ + Vector2::down());

			observer_gate_->AddComponent(og);

			// 同時押しスイッチ１
			observable_switch1_ = new GameObject();
			observable_switch1_->transform_->position_ = Vector2(18.0f, -2.0f);

			sprite = new Sprite(SWITCH_TEXTURE_NAME);
			sprite->SetSize(Vector2(1.0f, 0.3f));
			observable_switch1_->AddComponent(sprite);

			ObservableSwitch *os = new ObservableSwitch();
			os->StartObservation(og);	// 観察開始
			observable_switch1_->AddComponent(os);

			// 同時押しスイッチ2
			observable_switch2_ = new GameObject();
			observable_switch2_->transform_->position_ = Vector2(26.0f, -2.0f);

			sprite = new Sprite(SWITCH_TEXTURE_NAME);
			sprite->SetSize(Vector2(1.0f, 0.3f));
			observable_switch2_->AddComponent(sprite);

			os = new ObservableSwitch();
			os->StartObservation(og);
			observable_switch2_->AddComponent(os);

			// これらのゲームオブジェクトを登録
			AddGameObject(observer_gate_);
			AddGameObject(observable_switch1_);
			AddGameObject(observable_switch2_);
		}

		return S_OK;
	}

	void FirstStageScene::Update()
	{
		StageScene::Update();

		//if (input::Input::Instance()->GetButtonDown(input::InputButton::Start))
		//	SceneManager::LoadScene(new TempEndingScene());
#ifdef _DEBUG
		//if (input::Input::Instance()->GetButtonDown(input::InputButton::Skill))
		//{
		//	NextPhase();
		//}
		//if (input::Input::Instance()->GetButtonDown(input::InputButton::Cancel))
		//{
		//	PrevPhase();
		//}
#endif
		if (input::Input::Instance()->GetButtonDown(input::InputButton::Action))
		{
			//static int z = 0;

			//z = (z + 1) % 16;
			//Camera::main_->SetZoom(10.0f + 1.0f * (z - 9));

			Vector2 pp = shadow_->transform_->position_;
			if (pp.x > 1.5f && pp.x < 3.5f && pp.y > -2.5f && pp.y < -0.5f)
			{
				DestroyImmediate(ivy_joint_);
			}
		}

		//static float rad = 0.0f;
		//rad += D3DXToRadian(0.1f);
		//moon_light_->GetComponent<Light>()->SetDirection(Vector2(cosf(rad),sinf(rad)));

#ifdef _DEBUG
		if (input::Input::Instance()->GetButtonDown(input::InputButton::Start))
		{
			SceneManager::LoadScene(new TitleScene());
		}
#endif
		tree_log_->GetComponent<BoxCollider>()->AddForce(Vector2(-5.0f, -10.0f));
	}

	void FirstStageScene::Uninit()
	{
		StageScene::Uninit();


	}
}
