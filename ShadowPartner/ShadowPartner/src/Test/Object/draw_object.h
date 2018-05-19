//==========================================================
// 概要  :描画のテスト用オブジェクト
// Author:Itsuki Namito
// Copyright(c) Utsurugi.All right reserved.
//==========================================================

#ifndef _TEST_OBJECT_DRAW_OBJECT_H_
#define _TEST_OBJECT_DRAW_OBJECT_H_

//**********************************************************
// インクルードファイル
//**********************************************************
#include "../../Base/Element/component.h"
#include "../../Base/2D/sprite.h"

namespace shadowpartner
{

	//==========================================================
	// 概要  :描画のテスト用オブジェクト
	//==========================================================
	class DrawObject:public Component
	{
	public:
		DrawObject();
		virtual ~DrawObject();
		
		// variables

		// methods

	protected:

		// methods
		void Uninit();
		void Awake();
		void Update();
		void Draw();

	private:
		// variables

		// methods

		// 利用禁止
	};
}

#endif