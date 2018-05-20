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
#include <typeinfo>

namespace shadowpartner
{
	class GameObject;
	class Transform;

	enum Tag
	{
		Untagged = 0,
		Player,
		Enemy,
		
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
		bool is_active_;
		GameObject *game_object_;
		Tag tag_;
		Transform *transform_;

		// methods
		void UpdateComponent();
		void DrawComponent();

		void SetActive(bool is_active);

		void Attached(GameObject *game_object, Transform *transform, Tag tag);
		Component *GetComponent(type_info &type);

	protected:

		// methods
		virtual HRESULT Awake() { return S_OK; };	// �R���X�g���N�^�ŌĂ΂�܂�.game_object_��transform_��nullptr�ł��B
		virtual void Start() {};					// �Q�[���I�u�W�F�N�g�ɃA�^�b�`���ꂽ�^�C�~���O��SetActive(true)�ŌĂ΂�܂��B
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