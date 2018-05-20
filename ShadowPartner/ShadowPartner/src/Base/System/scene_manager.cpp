//==========================================================
// 概要  :シーン管理クラス
// Author:Itsuki Namito
// Copyright(c) Utsurugi.All right reserved.
//==========================================================
#include "scene_manager.h"

// 最初に読み込むシーン
#include "../../Test/Scene/draw_test_scene.h"

namespace shadowpartner
{
	//**********************************************************
	// 定数
	//**********************************************************
	//**********************************************************
	// Static
	//**********************************************************
	SceneManager *SceneManager::instance_ = nullptr;

	SceneManager *SceneManager::Instance()
	{
		if (instance_ == nullptr)
		{
			instance_ = new SceneManager();

			instance_->Init();
		}

		return instance_;
	}

	// コンストラクタ
	SceneManager::SceneManager()
	{
	}

	// デストラクタ
	SceneManager::~SceneManager()
	{
		Uninit();

		for (int i = 0; i < scenes_.size(); ++i)
		{
			if (scenes_[i] != nullptr)
			{
				delete scenes_[i];
				scenes_[i] = nullptr;
			}
		}
	}

	HRESULT SceneManager::Init()
	{
		DrawTestScene *draw_test_scene = new DrawTestScene();

		current_scene_ = draw_test_scene;

		current_scene_->Init();

		scenes_.push_back(draw_test_scene);

		return S_OK;
	}

	void SceneManager::Uninit()
	{

	}

	void SceneManager::Update()
	{
		for (int i = 0; i < scenes_.size(); ++i)
		{
			if (scenes_[i]->is_active_)
			{
				current_scene_index_ = i;
				current_scene_ = scenes_[i];
				scenes_[i]->UpdateScene();
			}
		}
	}

	void SceneManager::Draw()
	{
		for (int i = 0; i < scenes_.size(); ++i)
		{
			if (scenes_[i]->is_active_)
			{
				current_scene_index_ = i;
				current_scene_ = scenes_[i];
				scenes_[i]->DrawScene();
			}
		}
	}

	//==========================================================
	// 概要  :現在存在するシーンの数を数えます。
	// 戻り値:現在存在するシーンの数(dont_destroy_on_load_は除く)
	//==========================================================
	int SceneManager::SceneCount()
	{
		return scenes_.size();
	}

	//==========================================================
	// 概要  :現在処理中のシーンを取得します。
	// 戻り値:現在処理中のシーンへのポインタ
	//==========================================================
	Scene *SceneManager::GetCurrentScene()
	{
		return current_scene_;
	}

	//==========================================================
	// 概要  :現在処理中のシーンのインデックスを取得します。
	// 戻り値:現在処理中のシーンのインデックス
	//==========================================================
	int SceneManager::GetCurrentSceneIndex()
	{
		return current_scene_index_;
	}

	//==========================================================
	// 概要  :指定されたインデックスのシーンを読み込みます
	// 引数  :読み込みたいシーンのインデックス
	// 戻り値:指定されたシーンへのポインタ
	//==========================================================
	Scene *SceneManager::GetSceneByIndex(int index)
	{
		return scenes_[index];
	}
}
