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

#define TITLE_BACKGROUND_TEXTURE_NAME "Resources/Texture/Title/TitleBackGround.png"
#define TITLE_LIGHT_FOG_TEXTURE_NAME "Resources/Texture/Title/LightFog.png"
#define TITLE_COMMANDS_TEXTURE_NAME "Resources/Texture/Title/TitleCommands.png"


#define TITLE_POINTED_COLOR			D3DCOLOR_RGBA(0xfe,0xf2,0x63,0xff)
#define TITLE_NOT_POINTED_COLOR		D3DCOLOR_RGBA(0x70,0x58,0xa3,0xff)

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

			AddGameObject(camera_object_);
		}

		// �^�C�g���w�i�̃I�u�W�F�N�g
		{
			title_background_ = new GameObject();
			title_background_->transform_->position_ = Vector2(0.0f, 0.0f);

			// �X�v���C�g�̐ݒ�
			Sprite *sprite = new Sprite(TITLE_BACKGROUND_TEXTURE_NAME);
			sprite->SetSize(Vector2(11.2f, 6.3f));
			sprite->SetColor(D3DCOLOR_RGBA(0xff, 0xff, 0xff, 0xff));
			title_background_->AddComponent(sprite);

			// �V�[���ɃQ�[���I�u�W�F�N�g��o�^
			AddGameObject(title_background_);
		}

		current_button_index_ = 0;
		Vector2 next_button_pos_ = Vector2(4.0f, 0.0f);
		Vector2 button_pos_diff_ = Vector2(0.0f, -0.8f);

		// �I�𒆂̃R�}���h�̌��̃I�u�W�F�N�g
		{
			title_light_fog_ = new GameObject();
			title_light_fog_->transform_->position_ = Vector2(4.0f, 0.0f);

			// �X�v���C�g�̐ݒ�
			Sprite *sprite = new Sprite(TITLE_LIGHT_FOG_TEXTURE_NAME);
			sprite->SetSize(Vector2(1.6f, 0.8f));
			sprite->SetColor(TITLE_POINTED_COLOR);
			title_light_fog_->AddComponent(sprite);

			// �V�[���ɃQ�[���I�u�W�F�N�g��o�^
			AddGameObject(title_light_fog_);
		}

		// �^�C�g���̃R�}���h�{�^��
		{
			for (int i = 0;i < TitleButton::kTitleButtonCount;++i)
			{
				title_command_buttons_[i] = new GameObject();
				title_command_buttons_[i]->transform_->position_ = next_button_pos_;

				// �X�v���C�g�̐ݒ�
				Sprite *sprite = new Sprite(TITLE_COMMANDS_TEXTURE_NAME);
				sprite->SetSize(Vector2(1.6f, 0.8f));
				sprite->SetUvOffset(Vector2(0.5f * (i / 2),0.5f * (i % 2)));
				sprite->SetUvSize(Vector2::one() * 0.5f);
				sprite->SetColor(TITLE_NOT_POINTED_COLOR);
				title_command_buttons_[i]->AddComponent(sprite);

				// �V�[���ɃQ�[���I�u�W�F�N�g��o�^
				AddGameObject(title_command_buttons_[i]);

				next_button_pos_ += button_pos_diff_;
			}

			title_command_buttons_[0]->GetComponent<Sprite>()->SetColor(TITLE_POINTED_COLOR);
		}


		return S_OK;
	}

	static int light_radius_scale = 0;

	void TitleScene::Update()
	{
		if (input::Input::Instance()->GetButtonDown(input::InputButton::Start))
		{
			switch (current_button_index_)
			{
			case TitleButton::kNewGame:
			{
				SceneManager::LoadScene(new FirstStageScene(3));
			}
			break;
			case TitleButton::kExit:
			{
				SceneManager::ExitGame();
			}
			break;

			default:
				break;
			}
		}
			
		// �I���R�}���h�̏㉺�ւ̈ړ�
		if (input::Input::Instance()->GetButtonDown(input::InputButton::Up))
		{

			title_command_buttons_[current_button_index_]->GetComponent<Sprite>()->SetColor(TITLE_NOT_POINTED_COLOR);
			current_button_index_ = (current_button_index_ + (TitleButton::kTitleButtonCount - 1)) % TitleButton::kTitleButtonCount;
			title_light_fog_->transform_->position_ = title_command_buttons_[current_button_index_]->transform_->position_;
			title_command_buttons_[current_button_index_]->GetComponent<Sprite>()->SetColor(TITLE_POINTED_COLOR);
		}

		if (input::Input::Instance()->GetButtonDown(input::InputButton::Down))
		{
			title_command_buttons_[current_button_index_]->GetComponent<Sprite>()->SetColor(TITLE_NOT_POINTED_COLOR);
			current_button_index_ = (current_button_index_ + 1) % TitleButton::kTitleButtonCount;
			title_light_fog_->transform_->position_ = title_command_buttons_[current_button_index_]->transform_->position_;
			title_command_buttons_[current_button_index_]->GetComponent<Sprite>()->SetColor(TITLE_POINTED_COLOR);
		}
	}

	void TitleScene::Uninit()
	{
	}
}
