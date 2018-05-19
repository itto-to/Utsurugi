//==========================================================
// �T�v  :�V�[��
// Author:Itsuki Namito
// Copyright(c) Utsurugi.All right reserved.
//==========================================================
#include "scene.h"

namespace shadowpartner
{
	// �R���X�g���N�^
	Scene::Scene()
		:is_active_(true)
	{
		Init();
	}
	
	// �f�X�g���N�^
	Scene::~Scene()
	{
		Uninit();

		for (int i = 0; i < gameObjects_.size(); ++i)
		{
			if (gameObjects_[i] != nullptr)
			{
				delete gameObjects_[i];
				gameObjects_[i] = nullptr;
			}
		}
	}

	void Scene::UpdateScene()
	{
		// �V�[������A�N�e�B�u�Ȃ�X�V���Ȃ�
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
		// �V�[������A�N�e�B�u�Ȃ�`�悵�Ȃ�
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
}
