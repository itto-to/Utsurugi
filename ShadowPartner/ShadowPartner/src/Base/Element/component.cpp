//==========================================================
// 概要  :GameObjectの構成単位の基底クラス
// Author:Itsuki Namito
// Copyright(c) Utsurugi.All right reserved.
//==========================================================
#include "component.h"

namespace shadowpartner
{
	//**********************************************************
	// マクロ
	//**********************************************************

		//**********************************************************
		// 定数
		//**********************************************************

		// コンストラクタ
	Component::Component()
		:is_active_(false)
		, game_object_(nullptr)
		, tag_(Tag::Untagged)
		, transform_(nullptr)
	{
		Awake();
	}

	Component::Component(Component &copy)
	{
		*this = copy;
	}

	void Component::UpdateComponent()
	{
		if (is_active_)
		{
			Update();
		}
	}

	void Component::DrawComponent()
	{
		if (is_active_)
		{
			Draw();
		}
	}

	//==========================================================
	// 概要  :活性・非活性を設定します。GameObjectにアタッチされていなければ非活性です。
	// 引数  :活性化させるかどうか。もし新たに活性化させるならStartが呼ばれます。
	//==========================================================
	void Component::SetActive(bool is_active)
	{
		if (game_object_ == nullptr || !is_active)
		{
			is_active_ = false;
		}
		else if (!is_active_ && is_active)
		{
			is_active_ = true;
			Start();
		}
	}

	//==========================================================
	// 概要  :GameObjectにアタッチします。
	// 引数  :アタッチするGameObjectとそのTransformとTag
	//==========================================================
	void Component::Attached(GameObject *game_object, Transform *transform, Tag tag)
	{
		game_object_ = game_object;
		transform_ = transform;
		tag_ = tag;

		SetActive(true);
	}

	//==========================================================
	// 概要  :指定されたComponentの派生クラスへのポインタの取得を試みます。
	// 引数  :取得したいComponentの派生クラスへのtype_info(typeidを使ってください)
	// 戻り値:Componentの派生クラスへのポインタ(もしなかったらnullptr)
	//==========================================================
	Component *Component::GetComponent(type_info &type)
	{
		return game_object_->GetComponent(type);
	}
}
