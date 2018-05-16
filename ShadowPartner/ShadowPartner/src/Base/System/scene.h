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
		//std::vector<

		// methods
		virtual HRESULT Init() = 0;
		virtual void Uninit() = 0;
		virtual void Update() = 0;
		virtual void Draw() = 0;

		void SetActive(bool is_active);

	protected:

		// methods

	private:
		// variables
		bool is_active_;

		// methods

		// ���p�֎~
	};
}

#endif