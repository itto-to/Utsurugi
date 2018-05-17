//==========================================================
// �T�v  :GameObject�̍\���P�ʂ̊��N���X
// Author:Itsuki Namito
// Copyright(c) Utsurugi.All right reserved.
//==========================================================
#include "component.h"

namespace shadowpartner
{
//**********************************************************
// �}�N��
//**********************************************************

	//**********************************************************
	// �萔
	//**********************************************************

	// �R���X�g���N�^
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
}
