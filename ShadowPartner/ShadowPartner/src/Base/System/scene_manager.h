//==========================================================
// �T�v  :�V�[���Ǘ��N���X
// Author:Itsuki Namito
// Copyright(c) Utsurugi.All right reserved.
//==========================================================

#ifndef _BASE_SYSTEM_SCENE_MANAGER_H_
#define _BASE_SYStEM_SCENE_MANAGER_H_

//**********************************************************
// �C���N���[�h�t�@�C��
//**********************************************************
#include "scene.h"
#include <vector>

//**********************************************************
// ���C�u�����ւ̃����N
//**********************************************************
#pragma comment (lib,"d3d9.lib")
#pragma comment (lib,"d3dx9.lib")
#pragma comment (lib,"dxguid.lib")
#pragma comment (lib,"dinput8.lib")
#pragma comment (lib,"winmm.lib")

namespace shadowpartner
{

	//==========================================================
	// �T�v  :�V�[���̊Ǘ���J�ڂ̐�����s���܂��B
	//==========================================================
	class SceneManager
	{
	public:
		// variables
		Scene dont_destroy_on_load_;

		// methods
		static SceneManager *Instance();

		HRESULT Init();
		void Uninit();
		void Update();
		void Draw();

		int SceneCount();
		Scene *GetCurrentScene();
		int GetCurrentSceneIndex();
		Scene *GetSceneByIndex(int index);

	protected:
		SceneManager();
		~SceneManager();

		// methods

	private:
		// variables
		static SceneManager *instance_;

		std::vector<Scene *>scenes_;

		Scene *current_scene_;
		int current_scene_index_;

		// methods

		// ���p�֎~
		SceneManager &operator=(const SceneManager &) { return *this; };
	};
}

#endif