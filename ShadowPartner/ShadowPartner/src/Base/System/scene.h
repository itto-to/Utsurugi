//==========================================================
// �T�v  :�V�[��
// Author:Itsuki Namito
// Copyright(c) Utsurugi.All right reserved.
//==========================================================

#ifndef _BASE_SYSTEM_SCENE_H_
#define _BASE_SYSTEM_SCENE_H_

//**********************************************************
// �C���N���[�h�t�@�C��
//**********************************************************
#include <windows.h>
#include <vector>
#include "../Element/gameobject.h"

namespace shadowpartner
{

	//==========================================================
	// �T�v  :�A
	//==========================================================
	class Scene
	{
	public:
		Scene();
		virtual ~Scene();
		
		// variables
		bool is_active_;
		std::vector<GameObject *> gameObjects_;

		// methods
		void UpdateScene();
		void DrawScene();

	protected:

		// methods
		virtual HRESULT Init() { return S_OK; };
		virtual void Uninit() {};
		virtual void Update() {};
		virtual void Draw() {};

	private:
		// variables

		// methods

		// ���p�֎~
	};
}

#endif