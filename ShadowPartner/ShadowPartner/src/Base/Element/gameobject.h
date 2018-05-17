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
#include "transform.h"

namespace shadowpartner
{

	enum Layer
	{
		Default = 0,
	};

	//==========================================================
	// �T�v  :�V�[���̍\���P��
	//==========================================================
	class GameObject
	{
	public:
		GameObject();
		~GameObject();

		// variables
		bool is_active_;
		Tag tag_;
		Layer layer_;

		Transform *transform_;

		std::vector<Component *> components_;

		// methods
		HRESULT Init();
		void Uninit();
		void Update();
		void Draw();

		void Destroy();
		void Destroy(float delay);

	protected:

		// methods

	private:
		// variables

		// methods

	};

}


#endif