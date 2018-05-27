//==========================================================
// �T�v  :�`��̃e�X�g�p�V�[��
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
	// �R���X�g���N�^
	PhysicsTestScene::PhysicsTestScene()
	{

	}

	// �f�X�g���N�^
	PhysicsTestScene::~PhysicsTestScene()
	{

	}

	// ����������
	HRESULT PhysicsTestScene::Init()
	{
		printf("�`��e�X�g�̃V�[���̃I�u�W�F�N�g�𐶐����܂��B");

		// �J�����I�u�W�F�N�g�𐶐�
		{
			camera_object = new GameObject();
			camera_object->transform_->position_ = Vector2(0.0f, 0.0f);
			Camera *camera = new Camera();
			camera_object->AddComponent(camera);

			gameObjects_.push_back(camera_object);
		}

		// �Î~�����{�b�N�X
		{
			static_box = new GameObject();
			static_box->transform_->position_ = Vector2(0.0f, -100.0f);

			// �X�v���C�g�̐ݒ�
			Sprite *sprite = new Sprite(BOX_TEXTURE_NAME);
			sprite->SetSize(Vector2(800, 200));
			sprite->SetColor(D3DCOLOR_RGBA(0, 255, 0, 255));
			static_box->AddComponent(sprite);

			// ��`�̓����蔻��̐ݒ�
			BoxInitializer box_init;
			box_init.width_ = 800.0f;
			box_init.height_ = 200.0f;
			box_init.pos_ = static_box->transform_->position_;

			BoxCollider *box_collider = new BoxCollider(box_init);
			static_box->AddComponent(box_collider);

			// �V�[���ɃQ�[���I�u�W�F�N�g��o�^
			gameObjects_.push_back(static_box);
		}

		// ��������{�b�N�X
		{
			dynamic_box = new GameObject();
			dynamic_box->transform_->position_ = Vector2(50.0f, 100.0f);

			// �X�v���C�g�̐ݒ�
			Sprite *sprite = new Sprite(BOX_TEXTURE_NAME);
			sprite->SetSize(Vector2(10, 10));
			sprite->SetColor(D3DCOLOR_RGBA(255, 30, 30, 255));
			dynamic_box->AddComponent(sprite);

			// ��`�̓����蔻��̐ݒ�
			BoxInitializer box_init;
			box_init.width_ = 10.0f;
			box_init.height_ = 10.0f;
			box_init.is_static_ = false;
			box_init.pos_ = dynamic_box->transform_->position_;

			BoxCollider *box_collider = new BoxCollider(box_init);
			dynamic_box->AddComponent(box_collider);

			// �V�[���ɃQ�[���I�u�W�F�N�g��o�^
			gameObjects_.push_back(dynamic_box);
		}

		// �����Ȃ��~�`�̃I�u�W�F�N�g
		{
			static_circle = new GameObject();
			static_circle->transform_->position_ = Vector2(0.0f, 100.0f);

			// �X�v���C�g�̐ݒ�
			Sprite *sprite = new Sprite(CIRCLE_TEXTURE_NAME);
			sprite->SetSize(Vector2(100, 100));
			sprite->SetColor(D3DCOLOR_RGBA(30, 255, 30, 255));
			static_circle->AddComponent(sprite);

			// ��`�̓����蔻��̐ݒ�
			CircleInitializer circle_init;
			circle_init.radius_ = 100.0f;
			circle_init.pos_ = static_circle->transform_->position_;

			CircleCollider *circle_collider = new CircleCollider(circle_init);
			static_circle->AddComponent(circle_collider);

			// �V�[���ɃQ�[���I�u�W�F�N�g��o�^
			gameObjects_.push_back(static_circle);
		}

		// �����~�`�̃I�u�W�F�N�g
		{
			dynamic_circle = new GameObject();
			dynamic_circle->transform_->position_ = Vector2(-50.0f, 200.0f);

			// �X�v���C�g�̐ݒ�
			Sprite *sprite = new Sprite(CIRCLE_TEXTURE_NAME);
			sprite->SetSize(Vector2(20, 20));
			sprite->SetColor(D3DCOLOR_RGBA(255, 0, 0, 255));
			dynamic_circle->AddComponent(sprite);

			// ��`�̓����蔻��̐ݒ�
			CircleInitializer circle_init;
			circle_init.radius_ = 20.0f;
			circle_init.pos_ = dynamic_circle->transform_->position_;
			circle_init.is_static_ = false;

			CircleCollider *circle_collider = new CircleCollider(circle_init);
			dynamic_circle->AddComponent(circle_collider);

			// �V�[���ɃQ�[���I�u�W�F�N�g��o�^
			gameObjects_.push_back(dynamic_circle);
		}

		return S_OK;
	}

	void PhysicsTestScene::Update()
	{
		if (input::Input::Instance()->GetButton(input::InputButton::Action))
		{
			CircleCollider *circle_collider = dynamic_circle->GetComponent<CircleCollider>();

			circle_collider->Stop();
		}

		Vector2 move;
		move.x = input::Input::Instance()->GetAxis(input::InputAxis::Horizontal);
		move.y = input::Input::Instance()->GetAxis(input::InputAxis::Vertical);

		dynamic_circle->transform_->position_ += move;
	}
}
