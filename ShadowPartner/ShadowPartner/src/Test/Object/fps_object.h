//==========================================================
// 概要  :FPSの表示用オブジェクト
// Author:Itsuki Namito
// Copyright(c) Utsurugi.All right reserved.
//==========================================================

#ifndef _TEST_OBJECT_FPS_OBJECT_H_
#define _TEST_OBJECT_FPS_OBJECT_H_

//**********************************************************
// インクルードファイル
//**********************************************************
#include "../../Base/Element/component.h"
#include "../../Base/2D/sprite.h"

#include "draw_number.h"

//**********************************************************
// マクロ
//**********************************************************
#define FPS_DIGIT_NUM (3)

namespace shadowpartner
{

	//==========================================================
	// 概要  :描画のテスト用オブジェクト
	//==========================================================
	class FpsObject:public Component
	{
	public:
		FpsObject();
		virtual ~FpsObject();
		
		// variables

		// methods

	protected:

		// methods
		void Uninit();
		void Start();
		void Update();

	private:
		// variables
		int fps_;
		DrawNumber *fps_digits_[FPS_DIGIT_NUM];

		// methods

		// 利用禁止
	};
}

#endif