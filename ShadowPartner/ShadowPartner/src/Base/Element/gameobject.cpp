//==========================================================
// �T�v  :�V�[���̍\���P��
// Author:Itsuki Namito
// Copyright(c) Utsurugi.All right reserved.
//==========================================================
#include "gameobject.h"

namespace shadowpartner
{

//**********************************************************
// �}�N��
//**********************************************************

	//**********************************************************
	// �萔
	//**********************************************************

	// �R���X�g���N�^
	GameObject::GameObject()
		:is_active_(true)
		,tag_(Tag::Untagged)
		, layer_(Layer::Default)
	{
		transform_ = new Transform();

		AddComponent(transform_);

		Init();
	}

	// �f�X�g���N�^
	GameObject::~GameObject()
	{
		Uninit();

		if (transform_ != nullptr)
		{
			delete transform_;
		}
	}

	HRESULT GameObject::Init()
	{
		return S_OK;
	}

	void GameObject::Uninit()
	{
		for (int i = 0;i < components_.size();++i)
		{
			if (components_[i] != nullptr)
			{
				delete components_[i];
				components_[i] = nullptr;
			}
		}
	}

	void GameObject::Update()
	{
		for (int i = 0;i < components_.size();++i)
		{
			components_[i]->UpdateComponent();
		}
	}

	void GameObject::Draw()
	{
		for (int i = 0;i < components_.size();++i)
		{
			components_[i]->DrawComponent();
		}
	}

	//==========================================================
	// �T�v  :GameObject�ɃR���|�[�l���g���������܂�
	// ����  :��������R���|�[�l���g
	//==========================================================
	void GameObject::AddComponent(Component *component)
	{
		component->gameObject_ = this;
		component->transform_ = transform_;

		component->tag_ = tag_;

		components_.push_back(component);
	}

	//==========================================================
	// �T�v  :�w�肳�ꂽComponent�̔h���N���X�ւ̃|�C���^�̎擾�����݂܂��B
	// ����  :�擾������Component�̔h���N���X�ւ�type_info(typeid���g���Ă�������)
	// �߂�l:Component�̔h���N���X�ւ̃|�C���^(�����Ȃ�������nullptr)
	//==========================================================
	Component *GameObject::GetComponent(type_info &type)
	{
		for (int i = 0; i < components_.size(); ++i)
		{
			if (typeid(*components_[i]) == type)
			{
				return components_[i];
			}
		}

		return nullptr;
	}
}
