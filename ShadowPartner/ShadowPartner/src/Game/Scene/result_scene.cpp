//==========================================================
// �T�v  :���U���g�V�[��
// Author:Ittoto
// Copyright(c) Utsurugi.All right reserved.
//==========================================================
#include "result_scene.h"

#include "../../Game/Scene/title_scene.h"
#include "../../Base/System/scene_manager.h"
#include "../../Base/Input/input.h"
#include "../../Base/2D/camera.h"
#include "../../Base/2D/sprite.h"

#define RESULT_BACKGROUND_TEXTURE_NAME	"Resources/Texture/BackGround/BackGround.png"
#define STAGE_CLEAR_TEXTURE_NAME		"Resources/Texture/Result/StageClear.png"

namespace shadowpartner
{

	ResultScene::ResultScene()
	{
	}

	ResultScene::~ResultScene()
	{
	}

	HRESULT ResultScene::Init()
	{
		// �J�����I�u�W�F�N�g�𐶐�
		{
			camera_object_ = new GameObject();
			camera_object_->transform_->position_ = Vector2(0.0f, 0.0f);
			Camera *camera = new Camera();
			camera_object_->AddComponent(camera);

			AddGameObject(camera_object_);
		}

		// ���U���g�w�i�̃I�u�W�F�N�g
		{
			result_background_ = new GameObject();
			result_background_->transform_->position_ = Vector2(0.0f, 0.0f);

			// �X�v���C�g�̐ݒ�
			Sprite *sprite = new Sprite(RESULT_BACKGROUND_TEXTURE_NAME);
			sprite->SetSize(Vector2(11.2f, 6.3f));
			sprite->SetColor(D3DCOLOR_RGBA(0xff, 0xff, 0xff, 0xff));
			result_background_->AddComponent(sprite);

			// �V�[���ɃQ�[���I�u�W�F�N�g��o�^
			AddGameObject(result_background_);
		}

		// �X�e�[�W�N���A�\���̃I�u�W�F�N�g
		{
			stage_clear_ = new GameObject;
			stage_clear_->transform_->position_ = Vector2(0.0f, 0.0f);

			// �X�v���C�g�̐ݒ�
			Sprite *sprite = new Sprite(STAGE_CLEAR_TEXTURE_NAME);
			sprite->SetSize(Vector2(3.62f, 1.74f) * 1.5f);
			sprite->SetColor(D3DCOLOR_RGBA(0xff, 0xff, 0xff, 0xff));
			stage_clear_->AddComponent(sprite);

			// �V�[���ɃQ�[���I�u�W�F�N�g��o�^
			AddGameObject(stage_clear_);
		}


		return S_OK;
	}

	void ResultScene::Update()
	{
		if (input::Input::Instance()->GetButtonDown(input::InputButton::Start))
		{
			SceneManager::LoadScene(new TitleScene());
		}
	}

	void ResultScene::Uninit()
	{
	}

}	// namespace shadowpartner