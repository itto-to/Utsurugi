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
		:gameObject_(nullptr)
		,tag_(Tag::Untagged)
		,transform_(nullptr)
	{

	}

	Component::Component(Component &copy)
	{
		*this = copy;
	}

	void Component::UpdateComponent()
	{
		Update();
	}

	void Component::DrawComponent()
	{
		Draw();
	}

	//==========================================================
	// 概要  :指定されたComponentの派生クラスへのポインタの取得を試みます。
	// 引数  :取得したいComponentの派生クラスへのtype_info(typeidを使ってください)
	// 戻り値:Componentの派生クラスへのポインタ(もしなかったらnullptr)
	//==========================================================
	Component *Component::GetComponent(type_info &type)
	{
		return gameObject_->GetComponent(type);
	}
}
