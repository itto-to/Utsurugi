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
		kDefaultLayer = 0,
		kLightLayer,
		kPlayerLayer,
		kTestLayer,
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

		// methods
		HRESULT Init();
		void Uninit();
		void Update();
		void Draw();

		void AddComponent(Component *component);

		//==========================================================
		// �T�v  :�w�肳�ꂽComponent�̔h���N���X�ւ̃|�C���^�̎擾�����݂܂��B
		// �߂�l:Component�̔h���N���X�ւ̃|�C���^(�����Ȃ�������nullptr)
		//==========================================================
		template <typename T>
		T *GetComponent()
		{
			for (int i = 0; i < components_.size(); ++i)
			{
				if (typeid(*components_[i]) == typeid(T))
				{
					return (T *)components_[i];
				}
			}

			return nullptr;
		}

		//==========================================================
		// �T�v  :�w�肳�ꂽComponent�̔h���N���XT�܂���T���p�������N���X�ւ̃|�C���^�̎擾�����݂܂��B
		// �߂�l:Component�̔h���N���XT�܂���T���p�������N���X�ւ̃|�C���^(�����Ȃ�������nullptr)
		//==========================================================
		template <typename T>
		T *GetComponentInherit()
		{
			for (int i = 0; i < components_.size(); ++i)
			{
				T *p = dynamic_cast<T *>(components_[i]);
				if (p != nullptr)
				{
					return p;
				}
			}

			return nullptr;
		}

	protected:

		// methods

	private:
		// variables
		std::vector<Component *> components_;

		// methods

	};

}


#endif