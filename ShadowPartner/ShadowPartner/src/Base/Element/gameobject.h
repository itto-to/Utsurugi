//==========================================================
// 概要  :シーンの構成単位
// Author:Itsuki Namito
// Copyright(c) Utsurugi.All right reserved.
//==========================================================

#ifndef _BASE_ELEMENT_GAMEOBJECT_H_
#define _BASE_ELEMENT_GAMEOBJECT_H_

//**********************************************************
// インクルードファイル
//**********************************************************
#include <windows.h>
#include <vector>
#include "component.h"
#include "transform.h"

namespace shadowpartner
{

	enum Layer
	{
		kDefault = 0,
	};

	//==========================================================
	// 概要  :シーンの構成単位
	//==========================================================
	class GameObject
	{
	public:
		GameObject();
		~GameObject();

		// variables
		bool is_active_;
		Tag tag_;
		Layer layer_;

		Transform *transform_;

		// methods
		HRESULT Init();
		void Uninit();
		void Update();
		void Draw();

		void AddComponent(Component *component);
		Component *GetComponent(type_info &type);

		void Destroy();
		void Destroy(float delay);

	protected:

		// methods

	private:
		// variables
		std::vector<Component *> components_;

		// methods

	};

}


#endif