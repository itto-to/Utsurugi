//==========================================================
// 概要  :描画の中心やズームの設定を行います。
// Author:Itsuki Namito
// Copyright(c) Utsurugi.All right reserved.
//==========================================================
#include "camera.h"

namespace shadowpartner
{
//**********************************************************
// マクロ
//**********************************************************

	//**********************************************************
	// 定数
	//**********************************************************
	const float ZOOM_MIN = 0.5f;
	const float ZOOM_MAX = 1.5f;

	const float ZOOM_SMOOTHNESS_MIN = 0.0f;
	const float ZOOM_SMOOTHNESS_MAX = 0.99f;
	
	const float POSITION_SMOOTHNESS_MIN = 0.0f;
	const float POSITION_SMOOTHNESS_MAX = 0.99f;

	//**********************************************************
	// static
	//**********************************************************
	Camera *Camera::main_ = nullptr;

	// コンストラクタ
	Camera::Camera()
		:current_zoom_(1.0f)
		, target_zoom_(1.0f)
		, zoom_smoothness_(0.97f)
		, target_position_(Vector2::zero())
		, position_smoothness_(0.97f)
	{
		if (main_ == nullptr)
		{
			main_ = this;
		}
	}
	
	// デストラクタ
	Camera::~Camera()
	{
		if (main_ == this)
		{
			main_ = nullptr;
		}
	}

	// 更新処理
	void Camera::Update()
	{
		current_zoom_ = current_zoom_ * zoom_smoothness_ + target_zoom_ * (1.0f - zoom_smoothness_);
		transform_->position_ = transform_->position_ * position_smoothness_ + target_position_ * (1.0f - position_smoothness_);
	}

	//==========================================================
	// 概要  :ズームを取得します。
	// 戻り値:現在のズーム
	//==========================================================
	float Camera::GetZoom()
	{
		return current_zoom_;
	}

	//==========================================================
	// 概要  :ズームの目標値を取得します。
	// 戻り値:現在のズーム
	//==========================================================
	float Camera::GetTargetZoom()
	{
		return target_zoom_;
	}

	//==========================================================
	// 概要  :ズームを設定します。上限下限でクランプします。
	// 引数  :設定したいズーム値
	//==========================================================
	void Camera::SetZoom(const float &zoom)
	{
		target_zoom_ = (zoom > ZOOM_MAX) ? ZOOM_MAX : 
			           (zoom < ZOOM_MIN) ? ZOOM_MIN : zoom;
	}

	//==========================================================
	// 概要  :
	// 引数  :伸縮の割合
	//==========================================================
	void Camera::SetZoomSmoothness(const float &smoothness)
	{
		zoom_smoothness_ = (smoothness > ZOOM_SMOOTHNESS_MAX) ? ZOOM_SMOOTHNESS_MAX :
			          (smoothness < ZOOM_SMOOTHNESS_MIN) ? ZOOM_SMOOTHNESS_MIN : smoothness;
	}

	//==========================================================
	// 概要  :
	// 引数  :伸縮の割合
	//==========================================================
	void Camera::SetPositionSmoothness(const float &position_smoothness)
	{
		position_smoothness_ = (position_smoothness > POSITION_SMOOTHNESS_MAX) ? POSITION_SMOOTHNESS_MAX :
			(position_smoothness < POSITION_SMOOTHNESS_MIN) ? POSITION_SMOOTHNESS_MIN : position_smoothness;
	}

	//==========================================================
	// 概要  :カメラの位置を設定します。
	// 引数  :カメラの位置
	//==========================================================
	void Camera::SetPosition(const Vector2 &pos)
	{
		target_position_ = pos;
	}
}
