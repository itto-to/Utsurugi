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
	const float ZOOM_MAX = 10.0f;

	const float SMOOTHNESS_MIN = 0.0f;
	const float SMOOTHNESS_MAX = 99.9f;
	
	//**********************************************************
	// static
	//**********************************************************
	Camera *Camera::main_ = nullptr;

	// コンストラクタ
	Camera::Camera()
		:current_zoom_(1.0f)
		, target_zoom_(1.0f)
		, smoothness_(97.0f)
	{
		if (main_ == nullptr)
		{
			main_ = this;
		}
	}
	
	// デストラクタ
	Camera::~Camera()
	{

	}

	// 更新処理
	void Camera::Update()
	{
		//current_zoom_ = 
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
	void Camera::SetSmoothness(const float &smoothness)
	{
		smoothness_ = (smoothness > SMOOTHNESS_MAX) ? SMOOTHNESS_MAX :
			          (smoothness < SMOOTHNESS_MIN) ? SMOOTHNESS_MIN : smoothness;
	}
}
