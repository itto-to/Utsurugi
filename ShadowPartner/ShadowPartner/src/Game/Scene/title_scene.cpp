//==========================================================
// 概要  :ライトのテスト用シーン
// Author:Itsuki Namito
// Copyright(c) Utsurugi.All right reserved.
//==========================================================
#include "title_scene.h"
#include "../../Base/2D/camera.h"
#include "../../Base/2D/sprite.h"
#include "../../Base/Input/input.h"
#include "../../Base/System/scene_manager.h"
#include "first_stage_scene.h"
#include "../../Base/Sound/sound.h"

#ifdef _DEBUG
#include "../../Base/Debug/debugger.h"
#endif

#include "../../Base/Time/time.h"

#define TITLE_BACKGROUND_TEXTURE_NAME "Resources/Texture/Title/TitleBackGround.png"
#define TITLE_COMMANDS_TEXTURE_NAME "Resources/Texture/Title/TitleCommands.png"
#define TITLE_CEFFECT_TEXTURE_NAME "Resources/Texture/Title/TitleCommandsEffect.png"



//#define TITLE_POINTED_COLOR			D3DCOLOR_RGBA(0xfe,0xf2,0x63,0xff)
//#define TITLE_NOT_POINTED_COLOR		D3DCOLOR_RGBA(0x70,0x58,0xa3,0xff)

namespace shadowpartner
{

	namespace {
		const int kCountPerFrame = 10;
		bool decision_flag_;
	}



	// コンストラクタ
	TitleScene::TitleScene()
	{

	}

	// デストラクタ
	TitleScene::~TitleScene()
	{

	}

	// 初期化処理
	HRESULT TitleScene::Init()
	{
#ifdef _DEBUG
		debug::Debug::Log("シーンの切り替え：タイトル");
#endif
		sound::PlaySound(sound::SOUND_LABEL_BGM_INTRO);

		// カメラオブジェクトを生成
		{
			camera_object_ = new GameObject();
			camera_object_->transform_->position_ = Vector2(0.0f, 0.0f);
			Camera *camera = new Camera();
			camera_object_->AddComponent(camera);

			AddGameObject(camera_object_);
		}

		// タイトル背景のオブジェクト
		{
			title_background_ = new GameObject();
			title_background_->transform_->position_ = Vector2(0.0f, 0.0f);

			// スプライトの設定
			Sprite *sprite = new Sprite(TITLE_BACKGROUND_TEXTURE_NAME);
			sprite->SetSize(Vector2(11.2f, 6.3f));
			sprite->SetColor(D3DCOLOR_RGBA(0xff, 0xff, 0xff, 0xff));
			title_background_->AddComponent(sprite);

			// シーンにゲームオブジェクトを登録
			AddGameObject(title_background_);
		}

		current_button_index_ = 0;
		blink_counter_ = 0;
		decision_flag_ = FALSE;
		Vector2 next_button_pos_ = Vector2(4.0f, 0.0f);
		Vector2 button_pos_diff_ = Vector2(0.0f, -0.8f);


		// タイトルのコマンドボタン
		{
			for (int i = 0;i < TitleButton::kTitleButtonCount;++i)
			{
				title_command_buttons_[i] = new GameObject();
				title_command_buttons_[i]->transform_->position_ = next_button_pos_;

				// スプライトの設定
				Sprite *sprite = new Sprite(TITLE_COMMANDS_TEXTURE_NAME);
				sprite->SetSize(Vector2(1.6f, 0.8f));
				sprite->SetUvOffset(Vector2(0.5f * (i / 2),0.5f * (i % 2)));
				sprite->SetUvSize(Vector2::one() * 0.5f);
				sprite->SetUvNormal();
				sprite->SetColor(D3DCOLOR_RGBA(0xff, 0xff, 0xff, 0xff));
				title_command_buttons_[i]->AddComponent(sprite);

				// シーンにゲームオブジェクトを登録
				AddGameObject(title_command_buttons_[i]);

				next_button_pos_ += button_pos_diff_;
			}

		}


		// 選択中のコマンドの光のオブジェクト
		{

			title_light_fog_ = new GameObject();
			title_light_fog_->transform_->position_ = Vector2(4.0f, 0.0f);

			// スプライトの設定
			Sprite *sprite = new Sprite(TITLE_CEFFECT_TEXTURE_NAME);
			sprite->SetSize(Vector2(1.6f, 0.8f));
			sprite->SetUvSize(Vector2::one() * 0.5f);
			sprite->SetColor(D3DCOLOR_RGBA(0xff, 0xff, 0xff, 0xff));
			title_light_fog_->AddComponent(sprite);


			// シーンにゲームオブジェクトを登録
			AddGameObject(title_light_fog_);
		}


		return S_OK;
	}

	static int light_radius_scale = 0;

	void TitleScene::Update()
	{
		if (input::Input::Instance()->GetButtonDown(input::InputButton::Start))
		{
			decision_flag_ = TRUE;

		}

		if (decision_flag_)
		{
			blink_counter_++;
#ifdef _DEBUG
			debug::Debug::Log("title_counter:%d", blink_counter_);
#endif
			if (blink_counter_ % kCountPerFrame>=kCountPerFrame/2)
			{
				title_light_fog_->is_active_ = FALSE;
			}
			else
			{
				title_light_fog_->is_active_ = TRUE;

			}
		}

		if (blink_counter_ ==50)
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

			
		// 選択コマンドの上下への移動
		if (!decision_flag_) //ボタン決定したらもう移動しないこと
		{

			if (input::Input::Instance()->GetButtonDown(input::InputButton::Up))
			{

				current_button_index_ = (current_button_index_ + (TitleButton::kTitleButtonCount - 1)) % TitleButton::kTitleButtonCount;
				title_light_fog_->transform_->position_ = title_command_buttons_[current_button_index_]->transform_->position_;
				title_light_fog_->GetComponent<Sprite>()->SetUvOffset(Vector2(0.5f * (current_button_index_ / 2), 0.5f * (current_button_index_ % 2)));
			}

			if (input::Input::Instance()->GetButtonDown(input::InputButton::Down))
			{
				current_button_index_ = (current_button_index_ + 1) % TitleButton::kTitleButtonCount;
				title_light_fog_->transform_->position_ = title_command_buttons_[current_button_index_]->transform_->position_;
				title_light_fog_->GetComponent<Sprite>()->SetUvOffset(Vector2(0.5f * (current_button_index_ / 2), 0.5f * (current_button_index_ % 2)));
			}
			if (input::Input::Instance()->GetButtonDown(input::InputButton::Left))
			{
				Sprite *s = title_background_->GetComponent<Sprite>();
				s->SetFlipX(!s->GetFlipX());
			}
			if (input::Input::Instance()->GetButtonDown(input::InputButton::Right))
			{
				Sprite *s = title_background_->GetComponent<Sprite>();
				s->SetFlipY(!s->GetFlipY());
			}
		}

	}

	void TitleScene::Uninit()
	{
	}
}
