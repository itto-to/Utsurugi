//==========================================================
// Tv  :ΚuAp¨AgkAeqΦWΜΗ
// Author:Itsuki Namito
// Copyright(c) Utsurugi.All right reserved.
//==========================================================

#ifndef _BASE_ELEMENT_TRANSFORM_H_
#define _BASE_ELEMENT_TRANSFORM_H_

//**********************************************************
// CN[ht@C
//**********************************************************
#include <windows.h>
#include <vector>
#include "../Math/math.h"
#include "component.h"

namespace shadowpartner
{
	//==========================================================
	// Tv  :ΚuAp¨AgkAeqΦWΜΗ
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

	protected:

		// methods
		HRESULT Init();
		void Uninit();
		void Update();

	private:
		// variables
		Vector2 offsetPosition_;	// eTransformπξΖ΅½Position

		// methods

	};
}

#endif