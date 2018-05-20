//==========================================================
// �T�v  :�����̃e�N�X�`���[��\�����邾��
// Author:Itsuki Namito
// Copyright(c) Utsurugi.All right reserved.
//==========================================================
#include "draw_number.h"

#define NUMBER_TEXTURE_NAME "Resources/Texture/NumberTexture.png"

namespace shadowpartner
{
	// �R���X�g���N�^
	DrawNumber::DrawNumber()
		:number_(0)
		, number_sprite_(nullptr)
	{

	}

	// �f�X�g���N�^
	DrawNumber::~DrawNumber()
	{
		Uninit();
	}

	// �I������
	void DrawNumber::Uninit()
	{

	}

	// 
	void DrawNumber::Start()
	{
		{
			number_sprite_ = new Sprite(NUMBER_TEXTURE_NAME);
			number_sprite_->SetSize(Vector2(51.2f, 64.0f));
			number_sprite_->SetUvSize(Vector2(0.2f, 0.5f));

			game_object_->AddComponent(number_sprite_);
		}
	}

	// �X�V����
	void DrawNumber::Update()
	{

	}

	// �`�揈��
	void DrawNumber::Draw()
	{

	}

	//==========================================================
	// �T�v  :������ݒ肵�܂��B
	// ����  :�\�������鐔���i�ꌅ�ڂ̂݁j
	//==========================================================
	void DrawNumber::SetNumber(int number)
	{
		number_ = number % 10;

		number_sprite_->SetUvOffset(Vector2(0.2f * (number_ % 5), 0.5f * (number_ / 5)));
	}
}
