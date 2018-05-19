//==========================================================
// �T�v  :�V�[���Ǘ��N���X
// Author:Itsuki Namito
// Copyright(c) Utsurugi.All right reserved.
//==========================================================
#include "scene_manager.h"

// �ŏ��ɓǂݍ��ރV�[��
#include "../../Test/Scene/draw_test_scene.h"

namespace shadowpartner
{
	//**********************************************************
	// �萔
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

	// �R���X�g���N�^
	SceneManager::SceneManager()
	{
		Init();
	}

	// �f�X�g���N�^
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
