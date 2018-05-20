//==========================================================
// 概要  :数字のテクスチャーを表示するだけ
// Author:Itsuki Namito
// Copyright(c) Utsurugi.All right reserved.
//==========================================================

#ifndef _TEST_OBJECT_DRAW_NUMBER_H_
#define _TEST_OBJECT_DRAW_NUMBER_H_

//**********************************************************
// インクルードファイル
//**********************************************************
#include "../../Base/Element/component.h"
#include "../../Base/2D/sprite.h"

namespace shadowpartner
{

	//==========================================================
	// 概要  :数字のテクスチャーを表示するだけ
	//==========================================================
	class DrawNumber:public Component
	{
	public:
		DrawNumber();
		virtual ~DrawNumber();
		
		// variables

		// methods
		void SetNumber(int number);	// このオブジェクトは何桁目を描画するのかを設定する

	protected:

		// methods
		void Uninit();
		void Start();
		void Update();
		void Draw();

	private:
		// variables
		int number_;
		Sprite *number_sprite_;

		// methods

		// 利用禁止
	};
}

#endif