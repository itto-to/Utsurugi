//==========================================================
// �T�v  :FPS�̕\���p�I�u�W�F�N�g
// Author:Itsuki Namito
// Copyright(c) Utsurugi.All right reserved.
//==========================================================
#include <math.h>

#include "fps_object.h"

#include "../../Base/System/scene_manager.h"
#include "../../Base/Time/time.h"

const float NEXT_NUMBER_LENGHT = 50.0f;	// ���̌��̐�����X���W�܂ł̋���

namespace shadowpartner
{
	// �R���X�g���N�^
	FpsObject::FpsObject()
		:fps_(0)
	{

	}

	// �f�X�g���N�^
	FpsObject::~FpsObject()
	{

	}

	// �I������
	void FpsObject::Uninit()
	{

	}

	// 
	void FpsObject::Start()
	{
		// �e���̃X�v���C�g�̐���
		for (int i = 0;i < FPS_DIGIT_NUM;++i)
		{
			GameObject *digit = new GameObject();
			digit->transform_->parent_ = transform_;
			digit->transform_->position_ = Vector2(NEXT_NUMBER_LENGHT * i, 0.0f);

			fps_digits_[i] = new DrawNumber();
			digit->AddComponent(fps_digits_[i]);

			SceneManager::Instance()->GetCurrentScene()->gameObjects_.push_back(digit);
		}
	}

	// �X�V����
	void FpsObject::Update()
	{
		fps_ = Time::Instance()->current_fps_;

		for (int i = 0;i < FPS_DIGIT_NUM;++i)
		{
			fps_digits_[i]->SetNumber((fps_ / (int)pow(10, FPS_DIGIT_NUM - (i + 1))) % 10);
		}
	}
}
