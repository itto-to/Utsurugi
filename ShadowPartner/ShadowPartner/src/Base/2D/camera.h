//==========================================================
// �T�v  :�`��̒��S��Y�[���̐ݒ���s���܂��B
// Author:Itsuki Namito
// Copyright(c) Utsurugi.All right reserved.
//==========================================================

#ifndef _BASE_2D_CAMERA_H_
#define _BASE_2D_CAMERA_H_

//**********************************************************
// �C���N���[�h�t�@�C��
//**********************************************************
#include "../Element/component.h"
#include "../Math/math.h"

//==========================================================
// �}�N��
//==========================================================

namespace shadowpartner
{
	//==========================================================
	// �`��̒��S��Y�[���̐ݒ���s�����߂̃N���X
	//==========================================================
	class Camera :public Component
	{
	public:
		Camera();
		~Camera();

		//variables
		static Camera *main_;

		//methods
		float GetZoom();
		float GetTargetZoom();
		void SetZoom(const float &zoom);
		void SetSmoothness(const float &smoothness);
	protected:
		void Update();

	private:
		// variables
		float current_zoom_;
		float target_zoom_;
		float smoothness_;

		// methods
	};
}

#endif