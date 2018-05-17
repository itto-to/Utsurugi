//==========================================================
// 概要  :シーン管理クラス
// Author:Itsuki Namito
// Copyright(c) Utsurugi.All right reserved.
//==========================================================
#include "scene_manager.h"

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
		}

		return instance_;
	}

	// コンストラクタ
	SceneManager::SceneManager()
	{
		Init();
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
				scenes_[i]->DrawScene();
			}
		}
	}
}
