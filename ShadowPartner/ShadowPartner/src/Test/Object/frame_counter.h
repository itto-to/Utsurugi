//==========================================================
// 概要  :経過フレーム表示用
// Author:Itsuki Namito
// Copyright(c) Utsurugi.All right reserved.
//==========================================================

#ifndef _TEST_OBJECT_FRAME_COUNTER_H_
#define _TEST_OBJECT_FRAME_COUNTER_H_

//**********************************************************
// インクルードファイル
//**********************************************************
#include "../../Base/Element/component.h"
#include "../../Base/2D/sprite.h"

#include "draw_number.h"

//**********************************************************
// マクロ
//**********************************************************
#define FRAME_COUNT_DIGIT_MAX (7)	// フレーム数を計測する最大桁数

namespace shadowpartner
{

	//==========================================================
	// 概要  :経過フレーム表示用
	//==========================================================
	class FrameCounter :public Component
	{
	public:
		FrameCounter();
		virtual ~FrameCounter();

		// variables

		// methods

	protected:

		// methods
		void Uninit();
		void Start();
		void Update();

	private:
		// variables
		int frame_count_;
		DrawNumber *frame_digits_[FRAME_COUNT_DIGIT_MAX];

		// methods

		// 利用禁止
	};
}

#endif