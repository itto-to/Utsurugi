//==========================================================
// �T�v  :�V�[���̍\���P��
// Author:Itsuki Namito
// Copyright(c) Utsurugi.All right reserved.
//==========================================================

#ifndef _BASE_ELEMENT_GAMEOBJECT_H_
#define _BASE_ELEMENT_GAMEOBJECT_H_

//**********************************************************
// �C���N���[�h�t�@�C��
//**********************************************************
#include <windows.h>
#include <vector>
#include "component.h"

namespace shadowpartner
{
	class GameObject;
#include "transform.h"

	//==========================================================
	// �T�v  :�V�[���̍\���P��
	//==========================================================
	class GameObject
	{
	public:
		GameObject();
		~GameObject();

		// variables
		std::vector<Component> components_;
		

		// methods
		HRESULT Init();
		void Uninit();
		void Update();
		void Draw();

	protected:

		// methods

	private:
		// variables

		// methods

	};
}

#endif