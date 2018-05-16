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

		// methods
		static SceneManager *Instance();

		HRESULT Init();
		void Uninit();
		void Update();
		void Draw();

		int CountCurrentScene();
		Scene *GetSceneByIndex(int index);

	protected:
		SceneManager();
		~SceneManager();

		// methods

	private:
		// variables
		static SceneManager *instance_;

		// methods
		HRESULT InitWindow();
		HRESULT InitDirect3D();

		void UninitWindow();
		void UninitDirect3D();

		int MainLoop();

		static LRESULT CALLBACK MsgProc(HWND h_wnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

		// 利用禁止
		Application &operator=(const Application &) { return *this; };

	};
}

#endif