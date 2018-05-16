//==========================================================
// 概要  :シーンに配置する要素単位
// Author:Itsuki Namito
// Copyright(c) Utsurugi.All right reserved.
//==========================================================

#ifndef _BASE_ELEMENT_GAMEOBJECT_H_
#define _BASE_ELEMENT_GAMEOBJECT_H_

//**********************************************************
// インクルードファイル
//**********************************************************
#include <windows.h>


namespace shadowpartner
{

	//==========================================================
	// 概要  :アプリケーションの土台部分
	// 説明  :
	//==========================================================
	class Application
	{
	public:
		// variables
		HINSTANCE h_instance_;
		HWND h_wnd_;
		LPDIRECT3D9 d3d;
		LPDIRECT3DDEVICE9 device;

		// methods
		static Application *Instance();
		void Run();

	protected:
		Application();

		// methods
		HRESULT Init();
		void Uninit();
		void Update();
		void Draw();

	private:
		// variables
		static Application *instance_;

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