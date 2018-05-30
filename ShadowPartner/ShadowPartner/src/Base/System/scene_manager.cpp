//==========================================================
// �T�v  :�V�[���Ǘ��N���X
// Author:Itsuki Namito
// Copyright(c) Utsurugi.All right reserved.
//==========================================================
#include "scene_manager.h"

// �ŏ��ɓǂݍ��ރV�[��
#include "../../Test/Scene/draw_test_scene.h"
#include "../../Test/Scene/physics_test_scene.h"

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

			instance_->Init();
		}

		return instance_;
	}

	// �R���X�g���N�^
	SceneManager::SceneManager()
	{
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
		PhysicsTestScene *physics_test_scene = new PhysicsTestScene();
		current_scene_ = physics_test_scene;
		
		current_scene_->Init();

		scenes_.push_back(physics_test_scene);
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
	// �T�v  :���ݑ��݂���V�[���̐��𐔂��܂��B
	// �߂�l:���ݑ��݂���V�[���̐�(dont_destroy_on_load_�͏���)
	//==========================================================
	int SceneManager::SceneCount()
	{
		return scenes_.size();
	}

	//==========================================================
	// �T�v  :���ݏ������̃V�[�����擾���܂��B
	// �߂�l:���ݏ������̃V�[���ւ̃|�C���^
	//==========================================================
	Scene *SceneManager::GetCurrentScene()
	{
		return current_scene_;
	}

	//==========================================================
	// �T�v  :���ݏ������̃V�[���̃C���f�b�N�X���擾���܂��B
	// �߂�l:���ݏ������̃V�[���̃C���f�b�N�X
	//==========================================================
	int SceneManager::GetCurrentSceneIndex()
	{
		return current_scene_index_;
	}

	//==========================================================
	// �T�v  :�w�肳�ꂽ�C���f�b�N�X�̃V�[����ǂݍ��݂܂�
	// ����  :�ǂݍ��݂����V�[���̃C���f�b�N�X
	// �߂�l:�w�肳�ꂽ�V�[���ւ̃|�C���^
	//==========================================================
	Scene *SceneManager::GetSceneByIndex(int index)
	{
		return scenes_[index];
	}

	//==========================================================
	// �T�v  :�V�����V�[����ǂݍ��݂܂��B�Â��V�[���͍폜����܂��B
	// ����  :�V�����V�[���̃C���X�^���X�ւ̃|�C���^�B(new���Ă����Ă��������B)
	//==========================================================
	void SceneManager::LoadScene(Scene *new_scene)
	{
		//for (int i = 0;i < instance_->scenes_.size();++i)
		//{
		//	delete instance_->scenes_[i];
		//	instance_->scenes_[i] = nullptr;
		//}

		//instance_->scenes_.clear();

		//instance_->scenes_.push_back(new_scene);
	}
}
