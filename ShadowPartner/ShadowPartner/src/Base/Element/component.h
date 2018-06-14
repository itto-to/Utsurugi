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
		kUntagged = 0,
		kPlayer,
		kEnemy,
		kLargeLight,
		kMiddleLight,
		kSmallLight,
		kClimb,
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

		//==========================================================
		// �T�v  :�w�肳�ꂽComponent�̔h���N���X�ւ̃|�C���^�̎擾�����݂܂��B
		// �߂�l:Component�̔h���N���X�ւ̃|�C���^(�����Ȃ�������nullptr)
		//==========================================================
		template <typename T>
		T *GetComponent() 
		{
			return game_object_->GetComponent<T>();
		}

		//==========================================================
		// �T�v  :Component�̎��̂��w�肳�ꂽ�N���X�ł��邩���ׂ�B
		// �߂�l:�N���X�������Ȃ�true�A�Ⴄ�Ȃ�false
		//==========================================================
		template <typename T>
		bool Is()
		{
			if (typeid(*this) == typeid(T))
			{
				return true;
			}
			return false;
		}

	protected:

		// methods
		virtual HRESULT Awake() { return S_OK; };	// �R���X�g���N�^�ŌĂ΂�܂�.game_object_��transform_��nullptr�ł��B
		virtual void Start() {};					// �Q�[���I�u�W�F�N�g�ɃA�^�b�`���ꂽ�^�C�~���O��SetActive(true)�ŌĂ΂�܂��B
		virtual void Uninit() {};
		virtual void Update() {};
		virtual void FixedUpdate() {};
		virtual void Draw() {};

	private:
		// variables

		// methods

	};
}

#include "gameobject.h"
#include "transform.h"

#endif