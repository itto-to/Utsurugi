//==========================================================
// �T�v  :�ʒu�A�p���A�g�k�A�e�q�֌W�̊Ǘ�
// Author:Itsuki Namito
// Copyright(c) Utsurugi.All right reserved.
//==========================================================
#include "transform.h"

namespace shadowpartner
{
	// �R���X�g���N�^
	Transform::Transform()
		:position_(Vector2::zero())
		,rotation_(0.0f)
		,scale_(Vector2::zero())
		,parent_(nullptr)
	{
		Init();
	}

	// �f�X�g���N�^
	Transform::~Transform()
	{
		Uninit();

		for (int i = 0; i < children_.size(); ++i)
		{
			if (children_[i] != nullptr)
			{
				delete children_[i];
				children_[i] = nullptr;
			}
		}

		children_.clear();
	}

	HRESULT Transform::Init()
	{
		return S_OK;
	}

	void Transform::Uninit()
	{

	}

	void Transform::Update()
	{
		Vector2 world_position;
		if (parent_ != nullptr)
		{
			
		}
	}
}
