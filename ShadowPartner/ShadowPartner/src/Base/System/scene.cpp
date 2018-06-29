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

		for (int i = 0; i < game_objects_.size(); ++i)
		{
			if (game_objects_[i]->is_active_)
			{
				game_objects_[i]->Update();
			}
		}

		Update();
	}

	void Scene::DrawScene()
	{
		// シーンが非アクティブなら描画しない
		if (!is_active_)
			return;

		for (int i = 0; i < game_objects_.size(); ++i)
		{
			if (game_objects_[i]->is_active_)
			{
				game_objects_[i]->Draw();
			}
		}

		Draw();
	}

	//シーンにゲームオブジェクトを追加します。
	void Scene::AddGameObject(GameObject *game_object)
	{
		game_objects_.push_back(game_object);
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
		for (int i = 0; i < game_objects_.size(); ++i)
		{
			if (game_objects_[i] != nullptr)
			{
				delete game_objects_[i];
				game_objects_[i] = nullptr;
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

	void Scene::DestroyImmediate(GameObject *destroy_object)
	{
		for (int i = 0; i < game_objects_.size();++i)
		{
			if (destroy_object == game_objects_[i])
			{
				delete game_objects_[i];
				game_objects_.erase(game_objects_.begin() + i);
			}
		}
	}
}
