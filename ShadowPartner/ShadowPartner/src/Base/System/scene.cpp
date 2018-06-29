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
	}

	void Scene::UpdateScene()
	{
		// �V�[������A�N�e�B�u�Ȃ�X�V���Ȃ�
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
		// �V�[������A�N�e�B�u�Ȃ�`�悵�Ȃ�
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

	//�V�[���ɃQ�[���I�u�W�F�N�g��ǉ����܂��B
	void Scene::AddGameObject(GameObject *game_object)
	{
		game_objects_.push_back(game_object);
	}

	// ����������
	HRESULT Scene::Init()
	{
		return S_OK;
	}

	//==========================================================
	// �T�v  :�V�[���ɂ���Q�[���I�u�W�F�N�g��������܂��B
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

	// �X�V����
	void Scene::Update()
	{

	}

	// �`�揈��
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
