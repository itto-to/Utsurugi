//==========================================================
// �T�v  :�V�[���Ǘ��N���X
// Author:Itsuki Namito
// Copyright(c) Utsurugi.All right reserved.
//==========================================================
#include "scene_manager.h"

// �ŏ��ɓǂݍ��ރV�[��
#include "../../Test/Scene/physics_test_scene.h"
#include "../../Game/Scene/title_scene.h"
#include "../../Test/Scene/player_test_scene.h"
//#include "../Physics/physics.h"

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
	SceneManager::SceneManager() : next_scene_(nullptr)
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

		if (instance_ != nullptr)
		{
			delete instance_;
			instance_ = nullptr;
		}
	}

	HRESULT SceneManager::Init()
	{
		TitleScene *title_scene = new TitleScene();
		current_scene_ = title_scene;

		current_scene_->Init();

		scenes_.push_back(title_scene);

		//PlayerTestScene *player_test_scene = new PlayerTestScene();
		//current_scene_ = player_test_scene;
		//current_scene_->Init();
		//scenes_.push_back(player_test_scene);

		//PhysicsTestScene *physics_test_scene = new PhysicsTestScene();
		//current_scene_ = physics_test_scene;

		//current_scene_->Init();

		//scenes_.push_back(physics_test_scene);

		return S_OK;
	}

	void SceneManager::Uninit()
	{

	}

	void SceneManager::Update()
	{
		if (next_scene_ != nullptr)
		{
			ChangeScene();
		}

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

	void SceneManager::ChangeScene()
	{
		// �����̃V�[�����폜
		for (int i = 0; i < instance_->scenes_.size(); ++i)
		{
			delete instance_->scenes_[i];
			instance_->scenes_[i] = nullptr;
		}
		instance_->scenes_.clear();

		// �V�����V�[���̍쐬
		current_scene_ = next_scene_;
		current_scene_->Init();

		scenes_.push_back(current_scene_);

		// ���̃V�[����nullptr��
		next_scene_ = nullptr;
	}

	//==========================================================
	// �T�v  :�V�����V�[����ǂݍ��݂܂��B�Â��V�[���͍폜����܂��B
	// ����  :�V�����V�[���̃C���X�^���X�ւ̃|�C���^�B(new���Ă����Ă��������B)
	//==========================================================
	void SceneManager::LoadScene(Scene *new_scene)
	{
		// ����t���[���Ŋ��Ƀ��[�h���ꂽ�V�[��������ꍇ����ւ���
		if (instance_->next_scene_ != nullptr)
		{
			delete instance_->next_scene_;
		}

		instance_->next_scene_ = new_scene;

		//// �����̃V�[�����폜
		//for (int i = 0;i < instance_->scenes_.size();++i)
		//{
		//	delete instance_->scenes_[i];
		//	instance_->scenes_[i] = nullptr;
		//}

		////physics::PhysicsWorld::ClearBody();
		//instance_->scenes_.clear();

		//// �V�����V�[���̍쐬
		//instance_->current_scene_ = new_scene;
		//instance_->current_scene_->Init();

		//instance_->scenes_.push_back(new_scene);
	}

	void SceneManager::ExitGame()
	{
		PostQuitMessage(0);
	}
}
