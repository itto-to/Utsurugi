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
	// �T�v  :�����E�񊈐���ݒ肵�܂��BGameObject�ɃA�^�b�`����Ă��Ȃ���Δ񊈐��ł��B
	// ����  :�����������邩�ǂ����B�����V���Ɋ�����������Ȃ�Start���Ă΂�܂��B
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
	// �T�v  :GameObject�ɃA�^�b�`���܂��B
	// ����  :�A�^�b�`����GameObject�Ƃ���Transform��Tag
	//==========================================================
	void Component::Attached(GameObject *game_object, Transform *transform, Tag tag)
	{
		game_object_ = game_object;
		transform_ = transform;
		tag_ = tag;

		SetActive(true);
	}

	//==========================================================
	// �T�v  :�w�肳�ꂽComponent�̔h���N���X�ւ̃|�C���^�̎擾�����݂܂��B
	// ����  :�擾������Component�̔h���N���X�ւ�type_info(typeid���g���Ă�������)
	// �߂�l:Component�̔h���N���X�ւ̃|�C���^(�����Ȃ�������nullptr)
	//==========================================================
	Component *Component::GetComponent(type_info &type)
	{
		return game_object_->GetComponent(type);
	}
}
