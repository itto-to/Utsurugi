//==========================================================
// �T�v  :GameObject�̍\���P�ʂ̊��N���X
// Author:Itsuki Namito
// Copyright(c) Utsurugi.All right reserved.
//==========================================================

#ifndef _BASE_ELEMENT_COMPONENT_H_
#define _BASE_ELEMENT_COMPONENT_H_

//**********************************************************
// �C���N���[�h�t�@�C��
//**********************************************************
#include <windows.h>

namespace shadowpartner
{
	class GameObject;
	class Transform;

	enum Tag
	{
		Untagged = 0,
	};

	//==========================================================
	// �T�v  :GameObject�̍\���P�ʂ̊��N���X
	//==========================================================
	class Component
	{
	public:
		Component();
		Component(Component &copy);
		virtual ~Component() {};
		
		// variables
		GameObject *gameObject_;
		Tag tag_;
		Transform *transform_;

		// methods
		void UpdateComponent();
		void DrawComponent();

	protected:

		// methods
		virtual HRESULT Awake() { return S_OK; };
		virtual void Start() {};
		virtual void Uninit() {};
		virtual void Update() {};
		virtual void Draw() {};

	private:
		// variables

		// methods

	};
}

#include "gameobject.h"
#include "transform.h"

#endif