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
#include "../../Game/Actor/Common/jumper.h"
#include "../../Game/Actor/Player/landing_trigger.h"
#include "../../Base/Debug/debugger.h"
#include "../../Base/2D/sprite.h"
#include "../../Base/Light/light.h"
#include "../../Base/Physics/physics.h"
#include "../../Base/Physics/Element/polygon_collider.h"
#include "../../Base/Input/input.h"
#include "../../Base/System/scene_manager.h"
#include "draw_test_scene.h"
#include "../../Game/Actor/Player/gimmck_trigger.h"
#include "../../Base/Physics/Filter/collision_filter.h"
#include "../../Game/Actor/Player/action_trigger.h"

#define PLAYER_TEXTURE_NAME  "Resources/Texture/Character/PlayerWalk.png"
#define BOX_TEXTURE_NAME    "Resources/Texture/white.png"
#define LIGHT_TEXTURE_NAME  "Resources/Texture/LightBulb.png"

using namespace physics;

namespace shadowpartner {
	namespace
	{
		const Vector2 kInitPlayerPos = Vector2(-4.0f, 1.0f);

		const float kPlayerWidth = 2.0f;
		const float kPlayerHeight = 1.0f;

		const Vector2 kPlayerColliderSize = Vector2(1.5f, 0.75f);

		const Vector2 kPlayerUVSize = Vector2(0.25f, 0.25f);

		const Vector2 kTreeLogPosition = Vector2(2.0f, -1.1f);
		const float kTreeWidth = 0.2f;
		const float kTreeHeight = 2.0f;

		const Vector2 kFireflyPosition = Vector2(-4.0f, -1.4f);
		const Vector2 kFireflySpriteSize = Vector2(0.3f, 0.3f);
		const Vector2 kFireflyLightSize = Vector2(2.0f, 2.0f);

		const Vector2 kLightTreePosition = Vector2(-1.5f, -0.6f);
		const Vector2 kLightTreeSpriteSize = Vector2(2.56f, 3.25f);
		const Vector2 kLightTreeLightSize = Vector2(3.0f, 3.0f);

		const float kShadowWidth = 2.0f;
		const float kShadowHeight = 1.0f;

	}


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
			sprite->SetSize(Vector2(10.0f, 8.0f));
			sprite->SetColor(D3DCOLOR_RGBA(0xff, 0xff, 0x99, 0xff));
			large_light_->AddComponent(sprite);

			// 矩形の当たり判定の設定
			BoxInitializer box_init;
			box_init.width_ = 10.0f;
			box_init.height_ = 8.0f;
			box_init.body_type_ = kStaticBody;
			box_init.is_trigger_ = true;
			box_init.pos_ = large_light_->transform_->position_;

			BoxCollider *box_collider = new BoxCollider(box_init);
			large_light_->AddComponent(box_collider);

			// シーンにゲームオブジェクトを登録
			AddGameObject(large_light_);
		}

		{// 足場
			const float kWidth  = 0.35f;
			const Vector2 kStart = Vector2(-20.0f, -1.5f);

			for (int i = 0; i < kMaxPlatform; i++)
			{
				platform_[i] = new GameObject();
				platform_[i]->transform_->position_ = kStart + i * Vector2(kWidth, 0.0f);

				// スプライトの設定
				Sprite *sprite = new Sprite(BOX_TEXTURE_NAME);
				sprite->SetSize(Vector2(0.35f, 0.35f));
				sprite->SetColor(D3DCOLOR_RGBA(255, 255, 0, 255));
				platform_[i]->AddComponent(sprite);

				// 矩形の当たり判定の設定
				BoxInitializer box_init;
				box_init.width_ = 0.35f;
				box_init.height_ = 0.35f;
				box_init.body_type_ = kStaticBody;
				box_init.pos_ = platform_[i]->transform_->position_;

				BoxCollider *box_collider = new BoxCollider(box_init);
				platform_[i]->AddComponent(box_collider);

				// シーンにゲームオブジェクトを登録
				AddGameObject(platform_[i]);
			}
		}

		// 足場
		//{
		//	platform_[0] = new GameObject();
		//	platform_[0]->transform_->position_ = Vector2(-3.0f, -3.5f);

		//	// スプライトの設定
		//	Sprite *sprite = new Sprite(BOX_TEXTURE_NAME);
		//	sprite->SetSize(Vector2(9.0f, 2.0f));
		//	sprite->SetColor(D3DCOLOR_RGBA(0, 255, 0, 255));
		//	platform_[0]->AddComponent(sprite);

		//	// 矩形の当たり判定の設定
		//	BoxInitializer box_init;
		//	box_init.width_ = 9.0f;
		//	box_init.height_ = 2.0f;
		//	box_init.body_type_ = kStaticBody;
		//	box_init.pos_ = platform_[0]->transform_->position_;

		//	BoxCollider *box_collider = new BoxCollider(box_init);
		//	platform_[0]->AddComponent(box_collider);

		//	// シーンにゲームオブジェクトを登録
		//	AddGameObject(platform_[0]);
		//}

		// 中ライト生成
		{
			middle_light_ = new GameObject();
			middle_light_->transform_->position_ = Vector2(-2.0f, -1.0f);
			middle_light_->tag_ = Tag::kMiddleLight;

			// スプライトの設定
			Sprite *sprite = new Sprite(BOX_TEXTURE_NAME);
			sprite->SetSize(Vector2(3.0f, 3.0f));
			sprite->SetColor(D3DCOLOR_RGBA(0x00, 0x00, 0xff, 0x80));
			middle_light_->AddComponent(sprite);

			// 矩形の当たり判定の設定
			BoxInitializer box_init;
			box_init.width_ = 3.0f;
			box_init.height_ = 3.0f;
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
			small_light_->transform_->position_ = Vector2(1.0f, -1.5f);
			small_light_->tag_ = Tag::kSmallLight;

			//// スプライトの設定
			//Sprite *sprite = new Sprite(BOX_TEXTURE_NAME);
			//sprite->SetSize(Vector2(2.0f, 2.0f));
			//sprite->SetColor(D3DCOLOR_RGBA(0xff, 0x00, 0x00, 0x80));
			//small_light_->AddComponent(sprite);

			//// 矩形の当たり判定の設定
			//BoxInitializer box_init;
			//box_init.width_ = 2.0f;
			//box_init.height_ = 2.0f;
			//box_init.body_type_ = kStaticBody;
			//box_init.is_trigger_ = true;
			//box_init.pos_ = small_light_->transform_->position_;

			//BoxCollider *box_collider = new BoxCollider(box_init);
			//small_light_->AddComponent(box_collider);
			CircleInitializer circle_init;
			circle_init.radius_ = 2.0f;
			circle_init.pos_ =  small_light_->transform_->position_;
			circle_init.is_trigger_ = true;
			circle_init.body_type_ = kStaticBody;

			CircleCollider *col = new CircleCollider(circle_init);
			small_light_->AddComponent(col);

			// シーンにゲームオブジェクトを登録
			AddGameObject(small_light_);
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

			player_->AddComponent(sprite);

			// 矩形の当たり判定の設定
			BoxInitializer box_init;
			box_init.width_          = kPlayerColliderSize.x;
			box_init.height_         = kPlayerColliderSize.y;
			box_init.friction_       = 0.0f;
			box_init.density_        = 0.0f;
			box_init.gravity_scale_  = 1.0f;
			box_init.fixed_rotation_ = true;
			box_init.body_type_      = kDynamicBody;
			box_init.is_trigger_     = false;
			box_init.category_bits_  = CollisionFilter::kPlayer;
			box_init.mask_bits_ = ~(CollisionFilter::kShadow | CollisionFilter::kIvy);	// 影とだけ衝突しない

			BoxCollider *box_collider = new BoxCollider(box_init);
			box_collider->SetSleepingAllowed(false);	// Sleepを許可しない
			player_->AddComponent(box_collider);

			// ギミックトリガーの設定
			BoxInitializer gimmick_init;
			gimmick_init.body_type_ = kDynamicBody;
			gimmick_init.gravity_scale_ = 0.0f;
			gimmick_init.pos_ = player_->transform_->position_;
			gimmick_init.width_ = kPlayerColliderSize.x;
			gimmick_init.height_ = kPlayerColliderSize.y;
			gimmick_init.is_trigger_ = true;
			gimmick_init.offset_ = Vector2::zero();
			gimmick_init.category_bits_ = CollisionFilter::kGimmickTrigger;
			gimmick_init.mask_bits_ = CollisionFilter::kLight | CollisionFilter::kClimb;	// 光とツタだけ反応する

			GimmickTrigger *gimmick_trigger = new GimmickTrigger(gimmick_init);
			gimmick_trigger->SetSleepingAllowed(false);
			player_->AddComponent(gimmick_trigger);

			// 着地トリガーの設定
			BoxInitializer land_init;
			land_init.body_type_ = kDynamicBody;
			land_init.gravity_scale_ = 0.0f;
			land_init.is_trigger_ = true;
			land_init.pos_ = player_->transform_->position_;
			land_init.width_ = kPlayerColliderSize.x;
			land_init.height_ = 0.1f;
			land_init.offset_ = Vector2(0.0f, -kPlayerColliderSize.y / 2.0f);
			land_init.is_trigger_ = true;
			land_init.category_bits_ = CollisionFilter::kLandingTirgger;
			land_init.mask_bits_ = CollisionFilter::kPlatform | CollisionFilter::kClimb | CollisionFilter::kActionObject;
			LandingTrigger *land_trigger = new LandingTrigger(land_init);
			land_trigger->SetSleepingAllowed(false);
			player_->AddComponent(land_trigger);

			// アクショントリガーの設定
			BoxInitializer act_init;
			act_init.body_type_ = kDynamicBody;
			act_init.gravity_scale_ = 0.0f;
			act_init.pos_ = player_->transform_->position_;
			act_init.width_ = 0.2f;
			act_init.height_ = kPlayerHeight;
			act_init.offset_ = Vector2(kPlayerWidth / 2, 0.0f);
			act_init.is_trigger_ = true;
			act_init.category_bits_ = CollisionFilter::kActionTrigger;
			act_init.mask_bits_ = CollisionFilter::kActionObject;

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
			box_init.mask_bits_ = CollisionFilter::kShadow;
			box_init.density_ = 1.0f;
			box_init.friction_ = 0.0f;
			box_init.body_type_ = kStaticBody;
			box_init.is_trigger_ = true;
			box_init.mask_bits_ = CollisionFilter::kShadow;
			box_init.category_bits_ = ~CollisionFilter::kPlayer;	// プレイヤーとは衝突しない

			BoxCollider *box_collider = new BoxCollider(box_init);
			shadow_->AddComponent(box_collider);

			// ギミックトリガーの設定
			BoxInitializer gimmick_init;
			gimmick_init.body_type_ = kDynamicBody;
			gimmick_init.width_ = kMiddleShadowCollisionSize.x;
			gimmick_init.height_ = kMiddleShadowCollisionSize.y;
			gimmick_init.gravity_scale_ = 0.0f;
			gimmick_init.pos_ = shadow_->transform_->position_;
			gimmick_init.is_trigger_ = true;
			gimmick_init.offset_ = Vector2::zero();
			gimmick_init.category_bits_ = CollisionFilter::kGimmickTrigger;
			gimmick_init.mask_bits_ = CollisionFilter::kLight | CollisionFilter::kClimb;	// 光とツタだけ反応する

			GimmickTrigger *gimmick_trigger = new GimmickTrigger(gimmick_init);
			gimmick_trigger->SetSleepingAllowed(false);
			shadow_->AddComponent(gimmick_trigger);

			// 着地トリガーの設定
			BoxInitializer land_init;
			land_init.body_type_ = kDynamicBody;
			land_init.gravity_scale_ = 0.0f;
			land_init.pos_ = player_->transform_->position_;
			land_init.width_ = kMiddleShadowCollisionSize.x;
			land_init.height_ = 0.1f;
			land_init.offset_ = Vector2(0.0f, -kMiddleShadowCollisionSize.y / 2);
			land_init.is_trigger_ = true;
			land_init.category_bits_ = CollisionFilter::kShadow;
			land_init.mask_bits_ = CollisionFilter::kPlatform | CollisionFilter::kClimb | CollisionFilter::kActionObject;

			LandingTrigger *land_trigger = new LandingTrigger(land_init);
			land_trigger->SetSleepingAllowed(false);
			shadow_->AddComponent(land_trigger);

			// アクショントリガーの設定
			BoxInitializer act_init;
			act_init.body_type_ = kDynamicBody;
			act_init.gravity_scale_ = 0.0f;
			act_init.pos_ = shadow_->transform_->position_;
			act_init.width_ = 0.2f;
			act_init.height_ = kPlayerHeight;
			act_init.offset_ = Vector2(kPlayerWidth / 2, 0.0f);
			act_init.is_trigger_ = true;
			act_init.category_bits_ = CollisionFilter::kActionTrigger;
			act_init.mask_bits_ = CollisionFilter::kActionObject;

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
			shadow_->transform_->position_ = player_->transform_->position_ + Vector2::down() * 1.0f;
			Sprite *sprite = new Sprite(PLAYER_TEXTURE_NAME);
			sprite->SetSize(Vector2(1.0f, 1.0f));
			sprite->SetColor(D3DCOLOR_RGBA(0, 0, 0, 0xff));
			shadow_->AddComponent(sprite);
			Shadow *shadow = new Shadow();
			ShadowState *shadow_state = new ShadowState(shadow);
			shadow->SetState(shadow_state);
			shadow_->AddComponent(shadow);

			// プレイヤーのシャドウに登録
			shadow->SetPlayerObject(player_);
			player_->GetComponent<Player>()->shadow_object_ = shadow_;

			// 矩形の当たり判定の設定
			BoxInitializer box_init;
			box_init.pos_           = shadow_->transform_->position_;
			box_init.width_         = 1.0f;
			box_init.height_        = 1.0f;
			box_init.body_type_     = kStaticBody;
			box_init.is_trigger_    = true;
			box_init.mask_bits_     = CollisionFilter::kShadow;
			box_init.category_bits_ = ~CollisionFilter::kPlayer;	// プレイヤーとは衝突しない

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