//==========================================================
// 概要  :経過フレーム表示用
// Author:Itsuki Namito
// Copyright(c) Utsurugi.All right reserved.
//==========================================================
#include <math.h>

#include "frame_counter.h"

#include "../../Base/System/scene_manager.h"

const float NEXT_NUMBER_LENGHT = 100.0f;	// 次の桁の数字のX座標までの距離

namespace shadowpartner
{
	// コンストラクタ
	FrameCounter::FrameCounter()
		:frame_count_(0)
	{

	}

	// デストラクタ
	FrameCounter::~FrameCounter()
	{

	}

	// 終了処理
	void FrameCounter::Uninit()
	{
	}

	// 
	void FrameCounter::Start()
	{
		// 各桁のスプライトの生成
		for (int i = 0;i < FRAME_COUNT_DIGIT_MAX;++i)
		{
			GameObject *digit = new GameObject();
			digit->transform_->parent_ = transform_;
			digit->transform_->position_ = Vector2(NEXT_NUMBER_LENGHT * i, 0.0f);

			frame_digits_[i] = new DrawNumber();
			digit->AddComponent(frame_digits_[i]);

			SceneManager::Instance()->GetCurrentScene()->gameObjects_.push_back(digit);
		}
	}

	// 更新処理
	void FrameCounter::Update()
	{
		++frame_count_;

		for (int i = 0;i < FRAME_COUNT_DIGIT_MAX;++i)
		{
			frame_digits_[i]->SetNumber((frame_count_ / (int)pow(10, FRAME_COUNT_DIGIT_MAX - (i + 1))) % 10);
		}
	}
}
