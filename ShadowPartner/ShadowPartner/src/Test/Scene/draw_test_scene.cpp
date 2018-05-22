//==========================================================
// �T�v  :�`��̃e�X�g�p�V�[��
// Author:Itsuki Namito
// Copyright(c) Utsurugi.All right reserved.
//==========================================================
#include "draw_test_scene.h"
#include "../../Base/2D/camera.h"
#include "../../Base/2D/sprite.h"
#include "../../Base/Input/input.h"

#ifdef _DEBUG
#include "../../Base/Debug/debugger.h"
#endif

#include "../Object/frame_counter.h"
#include "../Object/fps_object.h"

#include "../../Base/Time/time.h"

#define TEST_TEXTURE_NAME "Resources/Texture/Fox1.png"

namespace shadowpartner
{
	// �R���X�g���N�^
	DrawTestScene::DrawTestScene()
	{

	}
	
	// �f�X�g���N�^
	DrawTestScene::~DrawTestScene()
	{

	}

	// ����������
	HRESULT DrawTestScene::Init()
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

		// �`��I�u�W�F�N�g�𐶐�
		{
			draw_object = new GameObject();
			draw_object->transform_->position_ = Vector2(0.0f, -200.0f);
			Sprite *sprite = new Sprite(TEST_TEXTURE_NAME);
			sprite->SetSize(Vector2(100, 100));
			draw_object->AddComponent(sprite);

			gameObjects_.push_back(draw_object);
		}

		// �Q�[���J�n������̃J�E���g�I�u�W�F�N�g�𐶐�
		{
			draw_count_object = new GameObject();
			draw_count_object->transform_->position_ = Vector2(-300.0f, 0.0f);
			draw_count_object->transform_->scale_ = Vector2(2.0f, 2.0f);
			FrameCounter *frame_counter = new FrameCounter();
			draw_count_object->AddComponent(frame_counter);

			gameObjects_.push_back(draw_count_object);
		}

		// FPS�\���I�u�W�F�N�g�𐶐�
		{
			draw_fps_object = new GameObject();
			draw_fps_object->transform_->position_ = Vector2(-300.0f, 200.0f);
			FpsObject *fps_object = new FpsObject();
			draw_fps_object->AddComponent(fps_object);

			gameObjects_.push_back(draw_fps_object);
		}

		return S_OK;
	}

	void DrawTestScene::Update()
	{
		float move = input::Input::Instance()->GetAxis(input::InputAxis::MouseX);
		draw_object->transform_->position_.x += move * 10 * Time::Instance()->delta_time_;
		system("cls");
		printf("move:%f\n", move);

<<<<<<< HEAD
#ifdef _DEBUG
		if (input::Input::Instance()->GetButtonDown(input::InputButton::Action))
		{
			debug::Debug::Log("Log:%d", 1);
		}
#endif
=======
		if (input::Input::Instance()->GetButtonDown(input::InputButton::Down))
		{
			draw_object->transform_->position_.y += 100.0f;
		}
>>>>>>> 161a44622ac47c57c9331b49c634d095a664506e
	}
}
