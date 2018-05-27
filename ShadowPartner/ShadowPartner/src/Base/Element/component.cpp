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
		, tag_(Tag::kUntagged)
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
}
