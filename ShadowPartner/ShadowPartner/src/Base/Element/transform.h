//==========================================================
// �T�v  :�ʒu�A�p���A�g�k�A�e�q�֌W�̊Ǘ�
// Author:Itsuki Namito
// Copyright(c) Utsurugi.All right reserved.
//==========================================================

#ifndef _BASE_ELEMENT_TRANSFORM_H_
#define _BASE_ELEMENT_TRANSFORM_H_

//**********************************************************
// �C���N���[�h�t�@�C��
//**********************************************************
#include <windows.h>
#include <vector>
#include "../Math/math.h"
#include "component.h"

using namespace math;

namespace shadowpartner
{
	//==========================================================
	// �T�v  :�ʒu�A�p���A�g�k�A�e�q�֌W�̊Ǘ�
	//==========================================================
	class Transform:public Component
	{
	public:
		Transform();
		~Transform();

		// variables
		Vector2 position_;
		float rotation_;
		Vector2 scale_;

		Transform *parent_;
		std::vector<Transform *> children_;

		// methods
		Vector2 GetWorldPosition();
		float GetWorldRotation();
		Vector2 GetWorldScale();

	protected:

		// methods
		HRESULT Init();
		void Uninit();
		void Update();

	private:
		// variables
		
		// methods

	};
}

#endif