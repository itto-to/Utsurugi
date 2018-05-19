//==========================================================
// 概要  :描画のテスト用オブジェクト
// Author:Itsuki Namito
// Copyright(c) Utsurugi.All right reserved.
//==========================================================
#include "draw_object.h"

#define TEST_TEXTURE_NAME "Resources/Texture/Fox1.png"

namespace shadowpartner
{
	// コンストラクタ
	DrawObject::DrawObject()
	{

	}

	// デストラクタ
	DrawObject::~DrawObject()
	{

	}

	// 終了処理
	void DrawObject::Uninit()
	{

	}

	// 
	void DrawObject::Awake()
	{
		gameObject_->AddComponent(new Sprite(TEST_TEXTURE_NAME));
	}

	// 更新処理
	void DrawObject::Update()
	{

	}

	// 描画処理
	void DrawObject::Draw()
	{

	}

}
