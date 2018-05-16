//==========================================================
// 概要  :GameObjectの構成単位の基底クラス
// Author:Itsuki Namito
// Copyright(c) Utsurugi.All right reserved.
//==========================================================

#ifndef _BASE_ELEMENT_COMPONENT_H_
#define _BASE_ELEMENT_COMPONENT_H_

//**********************************************************
// インクルードファイル
//**********************************************************
#include <windows.h>

namespace shadowpartner
{

	//==========================================================
	// 概要  :GameObjectの構成単位の基底クラス
	//==========================================================
	class Component
	{
	public:
		Component();
		Component(Component &copy);
		virtual ~Component() = 0;
		
		// variables

		// methods
		virtual HRESULT Init() = 0;
		virtual void Uninit() = 0;
		virtual void Update() = 0;
		virtual void Draw() = 0;

	protected:

		// methods

	private:
		// variables

		// methods

	};
}

#endif