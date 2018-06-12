//==========================================================
// �T�v  :���C�g�̃e�X�g�p�V�[��
// Author:Itsuki Namito
// Copyright(c) Utsurugi.All right reserved.
//==========================================================
#include "title_scene.h"
#include "../../Base/2D/camera.h"
#include "../../Base/2D/sprite.h"
#include "../../Base/Input/input.h"
#include "../../Base/System/scene_manager.h"
#include "first_stage_scene.h"

#ifdef _DEBUG
#include "../../Base/Debug/debugger.h"
#endif

#include "../../Base/Time/time.h"

#define TITLE_LOGO_TEXTURE_NAME "Resources/Texture/Title/TitleLogo.png"

namespace shadowpartner
{
	// �R���X�g���N�^
	TitleScene::TitleScene()
	{

	}

	// �f�X�g���N�^
	TitleScene::~TitleScene()
	{

	}

	// ����������
	HRESULT TitleScene::Init()
	{
#ifdef _DEBUG
		debug::Debug::Log("�V�[���̐؂�ւ��F�^�C�g��");
#endif
		// �J�����I�u�W�F�N�g�𐶐�
		{
			camera_object_ = new GameObject();
			camera_object_->transform_->position_ = Vector2(0.0f, 0.0f);
			Camera *camera = new Camera();
			camera_object_->AddComponent(camera);

			gameObjects_.push_back(camera_object_);
		}

		// �^�C�g�����S�̃I�u�W�F�N�g
		{
			title_logo_ = new GameObject();
			title_logo_->transform_->position_ = Vector2(-200.0f, 200.0f);

			// �X�v���C�g�̐ݒ�
			Sprite *sprite = new Sprite(TITLE_LOGO_TEXTURE_NAME);
			sprite->SetSize(Vector2(500, 150));
			sprite->SetColor(D3DCOLOR_RGBA(0xff, 0xff, 0x99, 0xff));
			title_logo_->AddComponent(sprite);

			// �V�[���ɃQ�[���I�u�W�F�N�g��o�^
			gameObjects_.push_back(title_logo_);
		}


		return S_OK;
	}

	static int light_radius_scale = 0;

	void TitleScene::Update()
	{
		if (input::Input::Instance()->GetButtonDown(input::InputButton::Start))
			SceneManager::LoadScene(new FirstStageScene());
	}

	void TitleScene::Uninit()
	{
	}
}
