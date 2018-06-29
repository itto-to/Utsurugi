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
#include "../Actor/Player/gimmck_trigger.h"
#include "../Actor/Gimmick/chain.h"
#include "../Actor//Player//action_trigger.h"

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

			Stage *stage = new Stage(StageNumber::kStage1_1, *stages_[0]);
			stages_[0]->AddComponent(stage);

			CornerCandidates::PreCalculate(stage);

			AddGameObject(stages_[0]);

			
		}

		// Stage Fase1
		{
			stages_[1] = new GameObject();
			stages_[1]->transform_->position_ = Vector2(11.2f, 0.0f);

			Stage *stage = new Stage(StageNumber::kStage1_2, *stages_[1]);
			stages_[1]->AddComponent(stage);

			CornerCandidates::PreCalculate(stage);

			AddGameObject(stages_[1]);


		}

		// Stage Fase1
		{
			stages_[2] = new GameObject();
			stages_[2]->transform_->position_ = Vector2(22.4f, 0.0f);

			Stage *stage = new Stage(StageNumber::kStage1_3, *stages_[2]);
			stages_[2]->AddComponent(stage);

			CornerCandidates::PreCalculate(stage);

			AddGameObject(stages_[2]);


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

		// �c�^�̐���
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

			RevoluteInitializer revolute_init;
			revolute_init.collider_a_ = box_collider;
			revolute_init.collider_b_ = stages_[0]->GetComponent<TileMapCollider>();
			revolute_init.local_anchor_a_ = Vector2(0.0f, 0.0f);
			revolute_init.local_anchor_b_ = Vector2(4.0f, -1.0f);

			revolute_init.enable_limit_ = true;
			revolute_init.lower_angle_ = -5.0f;
			revolute_init.upper_angle_ = -90.f;

			revolute_init.collide_connected_ = false;

			RevoluteJoint *revolute_joint = new RevoluteJoint(revolute_init);
			tree_->AddComponent(revolute_joint);

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
			box_init.width_         = kPlayerWidth;
			box_init.height_        = kPlayerHeight;
			box_init.density_       = 1.0f;
			box_init.friction_      = 0.0f;
			box_init.body_type_     = kDynamicBody;
			box_init.is_trigger_    = false;
			box_init.category_bits_ = CollisionFilter::kPlayer;
			box_init.mask_bits_     = ~CollisionFilter::kShadow;	// �e�ƏՓ˂��Ȃ�

			BoxCollider *box_collider = new BoxCollider(box_init);
			box_collider->SetSleepingAllowed(false);	// Sleep�������Ȃ�
			player_->AddComponent(box_collider);

			// �M�~�b�N�g���K�[�̐ݒ�
			BoxInitializer gimmick_init;
			gimmick_init.body_type_     = kDynamicBody;
			gimmick_init.gravity_scale_ = 0.0f;
			gimmick_init.pos_           = player_->transform_->position_;
			gimmick_init.width_         = kPlayerWidth;
			gimmick_init.height_        = kPlayerHeight;
			gimmick_init.is_trigger_    = true;
			gimmick_init.offset_        = Vector2::zero();
			gimmick_init.category_bits_ = CollisionFilter::kPlayer;
			gimmick_init.category_bits_ = CollisionFilter::kShadow;	// �e�Ƃ�����������

			GimmickTrigger *gimmick_trigger = new GimmickTrigger(gimmick_init);
			gimmick_trigger->SetSleepingAllowed(false);

			player_->AddComponent(gimmick_trigger);

			// ���n�g���K�[�̐ݒ�
			BoxInitializer land_init;
			land_init.body_type_     = kDynamicBody;
			land_init.gravity_scale_ = 0.0f;
			land_init.pos_           = player_->transform_->position_;
			land_init.width_         = kPlayerWidth;
			land_init.height_        = 0.1f;
			land_init.offset_        = Vector2(0.0f, -kPlayerHeight / 2);
			land_init.is_trigger_    = true;
			land_init.category_bits_ = CollisionFilter::kPlayer;
			land_init.mask_bits_     = ~CollisionFilter::kPlayer;

			LandingTrigger *land_trigger = new LandingTrigger(land_init);
			land_trigger->SetSleepingAllowed(false);
			player_->AddComponent(land_trigger);

			// �A�N�V�����g���K�[�̐ݒ�
			BoxInitializer act_init;
			act_init.body_type_ = kDynamicBody;
			act_init.gravity_scale_ = 0.0f;
			act_init.pos_ = player_->transform_->position_;
			act_init.width_ = 0.2f;
			act_init.height_ = kPlayerHeight;
			act_init.offset_ = Vector2(kPlayerWidth / 2, 0.0f);
			act_init.is_trigger_ = true;
			act_init.category_bits_ = CollisionFilter::kPlayer;
			act_init.mask_bits_ = ~CollisionFilter::kPlayer;

			ActionTrigger *act_trigger = new ActionTrigger(act_init);
			act_trigger->SetSleepingAllowed(false);
			player_->AddComponent(act_trigger);

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
			box_init.pos_           = shadow_->transform_->position_;
			box_init.width_         = 1.0f;
			box_init.height_        = 1.0f;
			box_init.friction_      = 0.0f;
			box_init.body_type_     = kStaticBody;
			box_init.is_trigger_    = true;
			box_init.mask_bits_     = CollisionFilter::kShadow;
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
			player_->GetComponent<Player>()->shadow_object_ = shadow_;

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

		// �e�X�g�p�̃T�[�N���ł�
		{
			test_circle_ = new GameObject();
			test_circle_->transform_->position_ = Vector2(10.0f, 30.0f);
			test_circle_->layer_ = Layer::kTestLayer;

			Sprite *sprite = new Sprite("Resources/Texture/WhiteCircle.png");
			sprite->SetSize(Vector2::one());
			sprite->SetColor(D3DCOLOR_RGBA(0xff, 0xff, 0xff, 0xff));
			test_circle_->AddComponent(sprite);

			CircleInitializer circle_init;
			circle_init.pos_ = test_circle_->transform_->position_;
			circle_init.radius_ = 0.5f;
			//circle_init.body_type_ = BodyType::kStaticBody;
			CircleCollider *circle_collider = new CircleCollider(circle_init);
			test_circle_->AddComponent(circle_collider);

			AddGameObject(test_circle_);
		}

		// �ۑ����Œ肷���1
		{
			ivy_chain_[0] = new GameObject();
			ivy_chain_[0]->transform_->position_ = Vector2(4.0f, 1.0f);

			ChainInitializer chain_init;
			chain_init.first_pos_ = Vector2(4.0f, 1.0f);
			chain_init.next_diff_ = Vector2(0.3f, 0.0f);
			chain_init.pieces_count_ = 3;
			chain_init.piece_width_ = 0.5f;
			chain_init.piece_height_ = 0.25f;
			Chain *chain = new Chain(chain_init, this);
			ivy_chain_[0]->AddComponent(chain);

			RevoluteInitializer revolute_init;
			revolute_init.world_pos_ = Vector2(0.0f, 0.0f);
			revolute_init.collider_a_ = tree_->GetComponent<BoxCollider>();
			revolute_init.collider_b_ = chain->first_;
			revolute_init.local_anchor_a_ = Vector2(4.0f, 1.0f);
			revolute_init.local_anchor_b_ = Vector2::zero();
			revolute_init.collide_connected_ = false;

			RevoluteJoint *tree_ivy_joint = new RevoluteJoint(revolute_init);

			ivy_chain_[0]->AddComponent(tree_ivy_joint);

			AddGameObject(ivy_chain_[0]);
		}
		
		// �ۑ����Œ肷���2
		{
			ivy_chain_[1] = new GameObject();
			ivy_chain_[1]->transform_->position_ = Vector2(4.75f, 0.0f);

			ChainInitializer chain_init;
			chain_init.first_pos_ = Vector2(4.0f, 1.0f);
			chain_init.next_diff_ = Vector2(0.3f, 0.0f);
			chain_init.pieces_count_ = 3;
			chain_init.piece_width_ = 0.5f;
			chain_init.piece_height_ = 0.25f;
			Chain *chain = new Chain(chain_init, this);
			ivy_chain_[1]->AddComponent(chain);

			RevoluteInitializer revolute_init;

			revolute_init.world_pos_ = Vector2(0.0f, 0.0f);
			revolute_init.collider_a_ = chain->last_;
			revolute_init.collider_b_ = stages_[1]->GetComponent<TileMapCollider>();
			revolute_init.local_anchor_a_ = Vector2::zero();
			revolute_init.local_anchor_b_ = Vector2(5.5f,-2.0f);

			RevoluteJoint *ivy_first_stage_joint = new RevoluteJoint(revolute_init);

			ivy_chain_[1]->AddComponent(ivy_first_stage_joint);

			AddGameObject(ivy_chain_[1]);
		}


		{
			//ivy_joint_ = new GameObject();
			//ivy_joint_->transform_->position_ = Vector2(4.75f, 0.0f);

			//RevoluteInitializer revolute_init;

			//revolute_init.world_pos_ = Vector2(4.75f, 0.0f);
			//revolute_init.collider_a_ = ivy_chain_[0]->GetComponent<Chain>()->last_;
			//revolute_init.collider_b_ = ivy_chain_[1]->GetComponent<Chain>()->first_;
			//revolute_init.local_anchor_a_ = Vector2::zero();
			//revolute_init.local_anchor_b_ = Vector2::zero();

			//RevoluteJoint *ivy_ivy_joint = new RevoluteJoint(revolute_init);

			//ivy_joint_->AddComponent(ivy_ivy_joint);

			//AddGameObject(ivy_joint_);
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
