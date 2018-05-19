//==========================================================
// 概要  :位置、姿勢、拡縮、親子関係の管理
// Author:Itsuki Namito
// Copyright(c) Utsurugi.All right reserved.
//==========================================================
#include "transform.h"

namespace shadowpartner
{
	// コンストラクタ
	Transform::Transform()
		:position_(Vector2::zero())
		,rotation_(0.0f)
		,scale_(Vector2::one())
		,parent_(nullptr)
	{
		Init();
	}

	// デストラクタ
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
	// 概要  :親子関係を考慮してワールド座標を取得します。
	// 戻り値:ワールド座標
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
	// 概要  :親子関係を考慮してワールドでの回転を取得します。
	// 戻り値:ワールドでの回転
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
	// 概要  :親子関係を考慮してワールドでのScaleを取得します。
	// 戻り値:ワールドでのScale
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
