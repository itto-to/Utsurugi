//==========================================================
// 概要  :位置、姿勢、拡縮、親子関係の管理
// Author:Itsuki Namito
// Copyright(c) Utsurugi.All right reserved.
//==========================================================

#ifndef _BASE_ELEMENT_TRANSFORM_H_
#define _BASE_ELEMENT_TRANSFORM_H_

class shadowpartner::Transform;

//**********************************************************
// インクルードファイル
//**********************************************************
#include <windows.h>
#include <vector>
#include "../Math/math.h"
#include "gameobject.h"

namespace shadowpartner
{

	//==========================================================
	// 概要  :位置、姿勢、拡縮、親子関係の管理
	//==========================================================
	class Transform:public Component
	{
	public:
		Transform();
		~Transform();

		// variables
		Vector2 position;
		float rotation;
		Vector2 scale;

		Transform *parent;
		std::vector<Transform *>children;

		// methods

	protected:

		// methods
		HRESULT Init();
		void Uninit();
		void Update();
		void Draw();

	private:
		// variables

		// methods

	};
}

#endif