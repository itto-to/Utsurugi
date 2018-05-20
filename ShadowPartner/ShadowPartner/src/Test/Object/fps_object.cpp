//==========================================================
// 概要  :FPSの表示用オブジェクト
// Author:Itsuki Namito
// Copyright(c) Utsurugi.All right reserved.
//==========================================================
#include <math.h>

#include "fps_object.h"

#include "../../Base/System/scene_manager.h"
#include "../../Base/Time/time.h"

const float NEXT_NUMBER_LENGHT = 50.0f;	// 次の桁の数字のX座標までの距離

namespace shadowpartner
{
	// コンストラクタ
	FpsObject::FpsObject()
		:fps_(0)
	{

	}

	// デストラクタ
	FpsObject::~FpsObject()
	{

	}

	// 終了処理
	void FpsObject::Uninit()
	{

	}

	// 
	void FpsObject::Start()
	{
		// 各桁のスプライトの生成
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

	// 更新処理
	void FpsObject::Update()
	{
		fps_ = Time::Instance()->current_fps_;

		for (int i = 0;i < FPS_DIGIT_NUM;++i)
		{
			fps_digits_[i]->SetNumber((fps_ / (int)pow(10, FPS_DIGIT_NUM - (i + 1))) % 10);
		}
	}
}
