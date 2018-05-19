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
		,scale_(Vector2::one())
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

	//==========================================================
	// �T�v  :�e�q�֌W���l�����ă��[���h���W���擾���܂��B
	// �߂�l:���[���h���W
	//==========================================================
	Vector2 Transform::GetWorldPosition()
	{
		Vector2 world_pos = position_;

		Transform *check_transform = this;

		while (check_transform->parent_ != nullptr)
		{
			world_pos += check_transform->parent_->position_;

			check_transform = check_transform->parent_;
		}

		return world_pos;
	}

	//==========================================================
	// �T�v  :�e�q�֌W���l�����ă��[���h�ł̉�]���擾���܂��B
	// �߂�l:���[���h�ł̉�]
	//==========================================================
	float Transform::GetWorldRotation()
	{
		float world_rot = rotation_;

		Transform *check_transform = this;

		while (check_transform->parent_ != nullptr)
		{
			world_rot += check_transform->parent_->rotation_;

			check_transform = check_transform->parent_;
		}

		return world_rot;
	}

	//==========================================================
	// �T�v  :�e�q�֌W���l�����ă��[���h�ł�Scale���擾���܂��B
	// �߂�l:���[���h�ł�Scale
	//==========================================================
	Vector2 Transform::GetWorldScale()
	{
		Vector2 world_scale = scale_;

		Transform *check_transform = this;

		while (check_transform->parent_ != nullptr)
		{
			world_scale = MulPerElem(world_scale,check_transform->parent_->scale_);

			check_transform = check_transform->parent_;
		}

		return world_scale;
	}
}
