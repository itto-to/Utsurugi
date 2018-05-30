//==========================================================
// �T�v  :�`��̒��S��Y�[���̐ݒ���s���܂��B
// Author:Itsuki Namito
// Copyright(c) Utsurugi.All right reserved.
//==========================================================
#include "camera.h"

namespace shadowpartner
{
//**********************************************************
// �}�N��
//**********************************************************

	//**********************************************************
	// �萔
	//**********************************************************
	const float ZOOM_MIN = 0.5f;
	const float ZOOM_MAX = 1.5f;

	const float SMOOTHNESS_MIN = 0.0f;
	const float SMOOTHNESS_MAX = 0.99f;
	
	//**********************************************************
	// static
	//**********************************************************
	Camera *Camera::main_ = nullptr;

	// �R���X�g���N�^
	Camera::Camera()
		:current_zoom_(1.0f)
		, target_zoom_(1.0f)
		, smoothness_(0.97f)
	{
		if (main_ == nullptr)
		{
			main_ = this;
		}
	}
	
	// �f�X�g���N�^
	Camera::~Camera()
	{
		if (main_ == this)
		{
			main_ = nullptr;
		}
	}

	// �X�V����
	void Camera::Update()
	{
		current_zoom_ = current_zoom_ * smoothness_ + target_zoom_ * (1.0f - smoothness_);
	}

	//==========================================================
	// �T�v  :�Y�[�����擾���܂��B
	// �߂�l:���݂̃Y�[��
	//==========================================================
	float Camera::GetZoom()
	{
		return current_zoom_;
	}

	//==========================================================
	// �T�v  :�Y�[���̖ڕW�l���擾���܂��B
	// �߂�l:���݂̃Y�[��
	//==========================================================
	float Camera::GetTargetZoom()
	{
		return target_zoom_;
	}

	//==========================================================
	// �T�v  :�Y�[����ݒ肵�܂��B��������ŃN�����v���܂��B
	// ����  :�ݒ肵�����Y�[���l
	//==========================================================
	void Camera::SetZoom(const float &zoom)
	{
		target_zoom_ = (zoom > ZOOM_MAX) ? ZOOM_MAX : 
			           (zoom < ZOOM_MIN) ? ZOOM_MIN : zoom;
	}

	//==========================================================
	// �T�v  :
	// ����  :�L�k�̊���
	//==========================================================
	void Camera::SetSmoothness(const float &smoothness)
	{
		smoothness_ = (smoothness > SMOOTHNESS_MAX) ? SMOOTHNESS_MAX :
			          (smoothness < SMOOTHNESS_MIN) ? SMOOTHNESS_MIN : smoothness;
	}
}
