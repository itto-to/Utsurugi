//==========================================================
// 概要  :数字のテクスチャーを表示するだけ
// Author:Itsuki Namito
// Copyright(c) Utsurugi.All right reserved.
//==========================================================
#include "draw_number.h"

#define NUMBER_TEXTURE_NAME "Resources/Texture/NumberTexture.png"

namespace shadowpartner
{
	// コンストラクタ
	DrawNumber::DrawNumber()
		:number_(0)
		, number_sprite_(nullptr)
	{

	}

	// デストラクタ
	DrawNumber::~DrawNumber()
	{
		Uninit();
	}

	// 終了処理
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

	// 更新処理
	void DrawNumber::Update()
	{

	}

	// 描画処理
	void DrawNumber::Draw()
	{

	}

	//==========================================================
	// 概要  :数字を設定します。
	// 引数  :表示させる数字（一桁目のみ）
	//==========================================================
	void DrawNumber::SetNumber(int number)
	{
		number_ = number % 10;

		number_sprite_->SetUvOffset(Vector2(0.2f * (number_ % 5), 0.5f * (number_ / 5)));
	}
}
