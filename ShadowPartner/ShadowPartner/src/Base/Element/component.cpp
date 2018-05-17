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
		:gameObject(nullptr)
		,tag(Tag::Untagged)
		,transform(nullptr)
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
}
