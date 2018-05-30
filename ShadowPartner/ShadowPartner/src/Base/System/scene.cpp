//==========================================================
// 概要  :シーン
// Author:Itsuki Namito
// Copyright(c) Utsurugi.All right reserved.
//==========================================================
#include "scene.h"

namespace shadowpartner
{
	// コンストラクタ
	Scene::Scene()
		:is_active_(true)
	{
		Init();
	}
	
	// デストラクタ
	Scene::~Scene()
	{
		Uninit();
	}

	void Scene::UpdateScene()
	{
		// シーンが非アクティブなら更新しない
		if (!is_active_)
			return;

		for (int i = 0; i < gameObjects_.size(); ++i)
		{
			if (gameObjects_[i]->is_active_)
			{
				gameObjects_[i]->Update();
			}
		}

		Update();
	}

	void Scene::DrawScene()
	{
		// シーンが非アクティブなら描画しない
		if (!is_active_)
			return;

		for (int i = 0; i < gameObjects_.size(); ++i)
		{
			if (gameObjects_[i]->is_active_)
			{
				gameObjects_[i]->Draw();
			}
		}

		Draw();
	}

	// 初期化処理
	HRESULT Scene::Init()
	{
		return S_OK;
	}

	//==========================================================
	// 概要  :シーンにあるゲームオブジェクトを解放します。
	//==========================================================
	void Scene::Uninit()
	{
		for (int i = 0; i < gameObjects_.size(); ++i)
		{
			if (gameObjects_[i] != nullptr)
			{
				delete gameObjects_[i];
				gameObjects_[i] = nullptr;
			}
		}
	}

	// 更新処理
	void Scene::Update()
	{

	}

	// 描画処理
	void Scene::Draw()
	{

	}
}
