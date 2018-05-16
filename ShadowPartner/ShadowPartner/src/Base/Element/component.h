//==========================================================
// �T�v  :�V�[���ɔz�u����v�f�P��
// Author:Itsuki Namito
// Copyright(c) Utsurugi.All right reserved.
//==========================================================

#ifndef _BASE_ELEMENT_GAMEOBJECT_H_
#define _BASE_ELEMENT_GAMEOBJECT_H_

//**********************************************************
// �C���N���[�h�t�@�C��
//**********************************************************
#include <windows.h>


namespace shadowpartner
{

	//==========================================================
	// �T�v  :�A�v���P�[�V�����̓y�䕔��
	// ����  :
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

		// ���p�֎~
		Application &operator=(const Application &) { return *this; };

	};
}

#endif