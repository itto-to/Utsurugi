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
		:is_active_(true)
		,tag_(Tag::Untagged)
		, layer_(Layer::Default)
	{
		transform_ = new Transform();

		AddComponent(transform_);

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
	// 概要  :GameObjectにコンポーネントをくっつけます
	// 引数  :くっつけるコンポーネント
	//==========================================================
	void GameObject::AddComponent(Component *component)
	{
		component->gameObject_ = this;
		component->transform_ = transform_;

		component->tag_ = tag_;

		components_.push_back(component);
	}

	//==========================================================
	// 概要  :指定されたComponentの派生クラスへのポインタの取得を試みます。
	// 引数  :取得したいComponentの派生クラスへのtype_info(typeidを使ってください)
	// 戻り値:Componentの派生クラスへのポインタ(もしなかったらnullptr)
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
