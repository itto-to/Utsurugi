//==========================================================
// 概要  :シーンの構成単位
// Author:Itsuki Namito
// Copyright(c) Utsurugi.All right reserved.
//==========================================================
#include "gameobject.h"

namespace shadowpartner
{

//**********************************************************
// マクロ
//**********************************************************

	//**********************************************************
	// 定数
	//**********************************************************

	// コンストラクタ
	GameObject::GameObject()
		:tag_(Tag::Untagged)
		, layer_(Layer::Default)
	{
		transform_ = new Transform();

		Init();
	}

	// デストラクタ
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
