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

namespace physics
{
	class Collider;
}


namespace shadowpartner
{
	class GameObject;
	class Transform;

	enum Tag
	{
		kUntagged = 0,
		kPlayer,
		kShadow,
		kEnemy,
		kLargeLight,
		kMiddleLight,
		kSmallLight,
		kClimb,
		kTree,
		kPlayerTrigger,
		kPlayerLandingTrigger,
		kGimmick,
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

		virtual void SetActive(bool is_active);

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
		// �T�v  :�w�肳�ꂽComponent�̔h���N���XT�܂���T���p�������N���X�ւ̃|�C���^�̎擾�����݂܂��B
		// �߂�l:Component�̔h���N���XT�܂���T���p�������N���X�ւ̃|�C���^(�����Ȃ�������nullptr)
		//==========================================================
		template <typename T>
		T *GetComponentInherit()
		{
			return game_object_->GetComponentInherit<T>();
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

		virtual void OnCollisionEnter(physics::Collider *collider) {}
		virtual void OnCollisionExit(physics::Collider *collider) {}
		virtual void OnCollisionStay(physics::Collider *collider) {}
		virtual void OnTriggerEnter(physics::Collider *collider) {}
		virtual void OnTriggerExit(physics::Collider *collider) {}
		virtual void OnTriggerStay(physics::Collider *collider) {}

		//virtual void OnCollisionEnter(physics::Collider *collider) {}
		//virtual void OnCollisionExit(physics::Collider *collider) {}
		//virtual void OnCollisionStay(physics::Collider *collider) {}
		//virtual void OnTriggerEnter(physics::Collider *collider) {}
		//virtual void OnTriggerExit(physics::Collider *collider) {}
		//virtual void OnTriggerStay(physics::Collider *collider) {}

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