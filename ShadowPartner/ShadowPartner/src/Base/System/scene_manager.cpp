//==========================================================
// 概要  :シーン管理クラス
// Author:Itsuki Namito
// Copyright(c) Utsurugi.All right reserved.
//==========================================================
#include "scene_manager.h"

// 最初に読み込むシーン
#include "../../Test/Scene/draw_test_scene.h"
#include "../../Test/Scene/physics_test_scene.h"
#include "../../Game/Scene/title_scene.h"

#include "../../Test/Scene/player_test_scene.h"	// 後で消す

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

		if (instance_ != nullptr)
		{
			delete instance_;
			instance_ = nullptr;
		}
	}

	HRESULT SceneManager::Init()
	{
		//TitleScene *title_scene = new TitleScene();
		//current_scene_ = title_scene;

		//current_scene_->Init();

		//scenes_.push_back(title_scene);

		//TEST: 後で消す
		PlayerTestScene *test = new PlayerTestScene();
		current_scene_ = test;
		current_scene_->Init();
		scenes_.push_back(test);
		

		//DrawTestScene *title_scene = new DrawTestScene();
		//current_scene_ = title_scene;

		//current_scene_->Init();

		//scenes_.push_back(title_scene);

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

	//==========================================================
	// 概要  :新しいシーンを読み込みます。古いシーンは削除されます。
	// 引数  :新しいシーンのインスタンスへのポインタ。(newしておいてください。)
	//==========================================================
	void SceneManager::LoadScene(Scene *new_scene)
	{
		// 既存のシーンを削除
		for (int i = 0;i < instance_->scenes_.size();++i)
		{
			delete instance_->scenes_[i];
			instance_->scenes_[i] = nullptr;
		}

		instance_->scenes_.clear();

		// 新しいシーンの作成
		instance_->current_scene_ = new_scene;
		instance_->current_scene_->Init();

		instance_->scenes_.push_back(new_scene);
	}
}
