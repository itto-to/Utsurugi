//==========================================================
// �T�v  :�ŏ��̃V�[���N���X
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

#include "temp_ending.h"

#ifdef _DEBUG
#include "../../Base/Debug/debugger.h"
#endif

#include "../../Base/Physics/physics.h"
#include "../../Base/Time/time.h"

#define LIGHT_TEXTURE_NAME       "Resources/Texture/LightBulb.png"
#define BACK_GROUND_TEXTURE_NAME "Resources/Texture/Stage/ForestBackGround.png"
#define CLEAR_GATE_TEXTURE_NAME  "Resources/Texture/Stage/Gate.png"
#define PLAYER_TEXTURE_NAME      "Resources/Texture/Character/newfox.png"
#define LIGHT_TEXTURE_NAME       "Resources/Texture/white.png"
#define TREE_TEXTURE_NAME        "Resources/Texture/white.png"

using namespace physics;

namespace
{
	const Vector2 kInitPlayerPos = Vector2(-2.0f, 3.0f);
}

namespace shadowpartner
{
	// �R���X�g���N�^
	FirstStageScene::FirstStageScene(int phase_num)
		:StageScene(phase_num)
	{

	}

	// �f�X�g���N�^
	FirstStageScene::~FirstStageScene()
	{

	}

	// ����������
	HRESULT FirstStageScene::Init()
	{
#ifdef _DEBUG
		debug::Debug::Log("�V�[���̐؂�ւ��F�����e�X�g");
#endif

		//�J����
		{
			camera_object_ = new GameObject();
			camera_object_->transform_->position_ = Vector2::zero();

			Camera *camera = new Camera();
			camera_object_->AddComponent(camera);

			AddGameObject(camera_object_);
		}

		// �w�i
		{
			back_ground_ = new GameObject();
			back_ground_->transform_->position_ = Vector2(11.2f, 0.0f);

			Sprite *sprite = new Sprite(BACK_GROUND_TEXTURE_NAME);
			sprite->SetSize(Vector2(33.6f, 6.3f));
			back_ground_->AddComponent(sprite);

			AddGameObject(back_ground_);
		}

		// �Q�[�g
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

			AddGameObject(stages_[0]);
		}

		// �����C�g����
		{
			middle_light_ = new GameObject();
			middle_light_->transform_->position_ = Vector2(-2.0f, -1.0f);
			middle_light_->tag_ = Tag::kMiddleLight;

			// �X�v���C�g�̐ݒ�
			Sprite *sprite = new Sprite(LIGHT_TEXTURE_NAME);
			sprite->SetSize(Vector2(3.0f, 3.0f));
			sprite->SetColor(D3DCOLOR_RGBA(0x00, 0x00, 0xff, 0x80));
			middle_light_->AddComponent(sprite);

			// ��`�̓����蔻��̐ݒ�
			BoxInitializer box_init;
			box_init.width_ = 3.0f;
			box_init.height_ = 3.0f;
			box_init.body_type_ = kStaticBody;
			box_init.is_trigger_ = true;
			box_init.pos_ = middle_light_->transform_->position_;

			BoxCollider *box_collider = new BoxCollider(box_init);
			middle_light_->AddComponent(box_collider);

			// �V�[���ɃQ�[���I�u�W�F�N�g��o�^
			AddGameObject(middle_light_);
		}

		// �����C�g����
		{
			small_light_ = new GameObject();
			small_light_->transform_->position_ = Vector2(1.0f, -1.5f);
			small_light_->tag_ = Tag::kSmallLight;

			// �X�v���C�g�̐ݒ�
			Sprite *sprite = new Sprite(LIGHT_TEXTURE_NAME);
			sprite->SetSize(Vector2(2.0f, 2.0f));
			sprite->SetColor(D3DCOLOR_RGBA(0xff, 0x00, 0x00, 0x80));
			small_light_->AddComponent(sprite);

			// ��`�̓����蔻��̐ݒ�
			BoxInitializer box_init;
			box_init.width_ = 2.0f;
			box_init.height_ = 2.0f;
			box_init.body_type_ = kStaticBody;
			box_init.is_trigger_ = true;
			box_init.pos_ = small_light_->transform_->position_;

			BoxCollider *box_collider = new BoxCollider(box_init);
			small_light_->AddComponent(box_collider);

			// �V�[���ɃQ�[���I�u�W�F�N�g��o�^
			AddGameObject(small_light_);
		}


		//// �v���C���[
		//{
		//	player_ = new GameObject();
		//	player_->transform_->position_ = kInitPlayerPos;

		//	Sprite *sprite = new Sprite(PLAYER_TEXTURE_NAME);
		//	sprite->SetSize(Vector2(1.0f, 1.0f));
		//	player_->AddComponent(sprite);
		//	Player *actor = new Player();
		//	player_->AddComponent(actor);

		//	// ��`�̓����蔻��̐ݒ�
		//	BoxInitializer box_init;
		//	box_init.width_ = 1.0f;
		//	box_init.height_ = 1.0f;
		//	box_init.density_ = 0.1f;
		//	box_init.body_type_ = kDynamicBody;
		//	box_init.is_trigger_ = false;
		//	box_init.pos_ = player_->transform_->position_;

		//	BoxCollider *box_collider = new BoxCollider(box_init);
		//	player_->AddComponent(box_collider);

		//	// �V�[���ɃQ�[���I�u�W�F�N�g��o�^
		//	AddGameObject(player_);

		//}

		//// �c�^�̐���
		{
			vine_ = new GameObject();
			vine_->transform_->position_ = Vector2(-4.0f, 0.0f);
			vine_->tag_ = Tag::kClimb;

			Sprite *sprite = new Sprite(LIGHT_TEXTURE_NAME);
			sprite->SetSize(Vector2(0.5f, 4.0f));
			sprite->SetColor(D3DCOLOR_ARGB(0xff, 0x00, 0xff, 0x00));
			vine_->AddComponent(sprite);


			// ��`�̓����蔻��̐ݒ�
			BoxInitializer box_init;
			box_init.width_ = 0.5f;
			box_init.height_ = 4.0f;
			box_init.density_ = 0.1f;
			box_init.body_type_ = kStaticBody;
			box_init.is_trigger_ = true;
			box_init.pos_ = vine_->transform_->position_;

			BoxCollider *box_collider = new BoxCollider(box_init);
			vine_->AddComponent(box_collider);

			// �V�[���ɃQ�[���I�u�W�F�N�g��o�^
			AddGameObject(vine_);
		}

		// ���̐���
		{
			const float kTreeWidth = 0.5f;
			const float kTreeHeight = 2.0f;

			tree_ = new GameObject();
			tree_->transform_->position_ = Vector2(4.0f, 0.0f);
			tree_->tag_ = Tag::kTree;

			// �X�v���C�g�ݒ�
			Sprite *sprite = new Sprite(TREE_TEXTURE_NAME);
			sprite->SetSize(Vector2(kTreeWidth, kTreeHeight));
			tree_->AddComponent(sprite);

			// ��`�̓����蔻��̐ݒ�
			BoxInitializer box_init;
			box_init.width_ = kTreeWidth;
			box_init.height_ = kTreeHeight;
			box_init.density_ = 1.0f;
			box_init.friction_ = 1.0f;
			box_init.body_type_ = kDynamicBody;
			box_init.is_trigger_ = false;

			BoxCollider *box_collider = new BoxCollider(box_init);
			tree_->AddComponent(box_collider);

			AddGameObject(tree_);
		}

		// �v���C���[�𐶐�
		{
			const float kPlayerWidth = 1.0f;
			const float kPlayerHeight = 1.0f;

			player_ = new GameObject();
			player_->transform_->position_ = kInitPlayerPos;
			player_->tag_ = Tag::kPlayer;

			Sprite *sprite = new Sprite(PLAYER_TEXTURE_NAME);
			sprite->SetSize(Vector2(1.0f, 1.0f));

			player_->AddComponent(sprite);

			// ��`�̓����蔻��̐ݒ�
			BoxInitializer box_init;
			box_init.width_ = kPlayerWidth;
			box_init.height_ = kPlayerHeight;
			box_init.density_ = 1.0f;
			box_init.friction_ = 0.0f;
			box_init.body_type_ = kDynamicBody;
			box_init.is_trigger_ = false;
			box_init.category_bits_ = CollisionFilter::kPlayer;
			box_init.mask_bits_ = ~CollisionFilter::kShadow;	// �e�ƏՓ˂��Ȃ�

			BoxCollider *box_collider = new BoxCollider(box_init);
			box_collider->SetSleepingAllowed(false);	// Sleep�������Ȃ�
			// ��`�̃Z���T�[�̐ݒ�
			BoxInitializer trigger_init;
			trigger_init.width_ = kPlayerWidth;
			trigger_init.height_ = kPlayerHeight;
			trigger_init.is_trigger_ = true;
			trigger_init.offset_ = Vector2::zero();
			trigger_init.category_bits_ = CollisionFilter::kPlayer;
			trigger_init.category_bits_ = CollisionFilter::kShadow;	// �e�Ƃ�����������
			box_collider->AddFixture(trigger_init);

			player_->AddComponent(box_collider);

			// ���n�g���K
			BoxInitializer land_init;
			land_init.pos_ = player_->transform_->position_;
			land_init.width_ = kPlayerWidth;
			land_init.height_ = 0.1f;
			land_init.offset_ = Vector2(0.0f, -kPlayerHeight / 2);
			land_init.is_trigger_ = true;
			land_init.gravity_scale_ = 0.0f;

			LandingTrigger *land_trigger = new LandingTrigger(land_init);
			player_->AddComponent(land_trigger);



			//BoxInitializer box_trigger_init;
			//box_trigger_init.width_      = kPlayerWidth;
			//box_trigger_init.height_     = kPlayerHeight;
			//box_trigger_init.density_    = 1.0f;
			//box_trigger_init.friction_   = 10.0f;
			//box_trigger_init.body_type_  = kDynamicBody;
			//box_trigger_init.is_trigger_ = false;
			//box_trigger_init.pos_ = player_->transform_->position_;

			//BoxCollider *box_trigger= new BoxCollider(box_trigger_init);
			//box_trigger->SetSleepingAllowed(false);	// Sleep�������Ȃ�
			//box_trigger->tag_ = Tag::kPlayer;
			//player_->AddComponent(box_trigger);

			Jumper *jumper = new Jumper();
			player_->AddComponent(jumper);

			Player *player_component = new Player();
			player_->AddComponent(player_component);

			// �V�[���ɃQ�[���I�u�W�F�N�g��o�^
			AddGameObject(player_);
		}

		// �e�𐶐�
		{
			shadow_ = new GameObject();
			shadow_->transform_->position_ = player_->transform_->position_ + Vector2::down() * 1.0f;
			shadow_->tag_ = Tag::kShadow;

			Sprite *sprite = new Sprite(PLAYER_TEXTURE_NAME);
			sprite->SetSize(Vector2(1.0f, 1.0f));
			sprite->SetColor(D3DCOLOR_RGBA(0, 0, 0, 0xff));
			shadow_->AddComponent(sprite);

			// ��`�̓����蔻��̐ݒ�
			BoxInitializer box_init;
			box_init.pos_ = shadow_->transform_->position_;
			box_init.width_ = 1.0f;
			box_init.height_ = 1.0f;
			box_init.friction_ = 0.0f;
			box_init.body_type_ = kStaticBody;
			box_init.is_trigger_ = true;
			box_init.mask_bits_ = CollisionFilter::kShadow;
			box_init.category_bits_ = ~CollisionFilter::kPlayer;	// �v���C���[�Ƃ͏Փ˂��Ȃ�

			BoxCollider *box_collider = new BoxCollider(box_init);
			shadow_->AddComponent(box_collider);

			Jumper *jumper = new Jumper();
			shadow_->AddComponent(jumper);

			Shadow *shadow = new Shadow();
			ShadowState *shadow_state = new ShadowState(shadow);
			shadow->SetState(shadow_state);
			shadow_->AddComponent(shadow);

			// �v���C���[�̃V���h�E�ɓo�^
			shadow->SetPlayerObject(player_);
			player_->GetComponent<Player>()->shadow_ = shadow_;

			AddGameObject(shadow_);
		}

		// �G�l�~�[�𐶐�
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

			//// ��`�̓����蔻��̐ݒ�
			//BoxInitializer box_init;
			//box_init.pos_ = enemy_->transform_->position_;
			//box_init.width_ = 1.0f;
			//box_init.height_ = 1.0f;
			//box_init.friction_ = 0.0f;
			//box_init.body_type_ = kStaticBody;
			//box_init.is_trigger_ = true;
			//box_init.mask_bits_ = CollisionFilter::kEnemy;
			//box_init.category_bits_ = ~CollisionFilter::kPlayer;	// �v���C���[�Ƃ͏Փ˂��Ȃ�

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
			z = (z + 1) % 4;
			Camera::main_->SetZoom(0.64f + 0.33f * (z + 1));
		}
	}

	void FirstStageScene::Uninit()
	{
		StageScene::Uninit();


	}
}
