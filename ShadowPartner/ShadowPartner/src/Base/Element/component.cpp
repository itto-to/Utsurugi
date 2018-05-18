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

	//==========================================================
	// �T�v  :�w�肳�ꂽComponent�̔h���N���X�ւ̃|�C���^�̎擾�����݂܂��B
	// ����  :�擾������Component�̔h���N���X�ւ�type_info(typeid���g���Ă�������)
	// �߂�l:Component�̔h���N���X�ւ̃|�C���^(�����Ȃ�������nullptr)
	//==========================================================
	Component *Component::GetComponent(type_info &type)
	{
		return gameObject_->GetComponent(type);
	}
}
