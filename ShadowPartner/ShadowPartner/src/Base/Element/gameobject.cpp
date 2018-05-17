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
		:tag_(Tag::Untagged)
		, layer_(Layer::Default)
	{
		transform_ = new Transform();

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
	}

	void GameObject::Uninit()
	{

	}

	void GameObject::Update()
	{
		for (int i = 0;i < components_.size();++i)
		{
			components_[i].UpdateComponent();
		}
	}

	void GameObject::Draw()
	{
		for (int i = 0;i < components_.size();++i)
		{
			components_[i].DrawComponent();
		}
	}
}
