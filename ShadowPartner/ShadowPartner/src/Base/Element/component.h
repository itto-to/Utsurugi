//==========================================================
// �T�v  :GameObject�̍\���P�ʂ̊��N���X
// Author:Itsuki Namito
// Copyright(c) Utsurugi.All right reserved.
//==========================================================

#ifndef _BASE_ELEMENT_COMPONENT_H_
#define _BASE_ELEMENT_COMPONENT_H_

class shadowpartner::Component;

//**********************************************************
// �C���N���[�h�t�@�C��
//**********************************************************
#include <windows.h>
#include "gameobject.h"
#include "transform.h"

namespace shadowpartner
{
	//==========================================================
	// �T�v  :GameObject�̍\���P�ʂ̊��N���X
	//==========================================================
	class Component
	{
	public:
		Component();
		Component(Component &copy);
		virtual ~Component() = 0;
		
		// variables
		GameObject *gameObject;
		Tag tag;
		Transform *transform;

		// methods
		void UpdateComponent();
		void DrawComponent();

	protected:

		// methods
		virtual HRESULT Awake() = 0;
		virtual void Start() = 0;
		virtual void Uninit() = 0;
		virtual void Update() = 0;
		virtual void Draw() = 0;

	private:
		// variables

		// methods

	};
}

#endif