//==========================================================
// 概要  :シーン管理クラス
// Author:Itsuki Namito
// Copyright(c) Utsurugi.All right reserved.
//==========================================================

#ifndef _BASE_SYSTEM_SCENE_MANAGER_H_
#define _BASE_SYStEM_SCENE_MANAGER_H_

//**********************************************************
// インクルードファイル
//**********************************************************
#include "scene.h"
#include <vector>

//**********************************************************
// ライブラリへのリンク
//**********************************************************
#pragma comment (lib,"d3d9.lib")
#pragma comment (lib,"d3dx9.lib")
#pragma comment (lib,"dxguid.lib")
#pragma comment (lib,"dinput8.lib")
#pragma comment (lib,"winmm.lib")

namespace shadowpartner
{

	//==========================================================
	// 概要  :シーンの管理や遷移の制御を行います。
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

		// 利用禁止
		SceneManager &operator=(const SceneManager &) { return *this; };
	};
}

#endif