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
		kDefaultLayer = 0,
		kLightLayer,
		kPlayerLayer,
		kTestLayer,
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

		//==========================================================
		// 概要  :指定されたComponentの派生クラスへのポインタの取得を試みます。
		// 戻り値:Componentの派生クラスへのポインタ(もしなかったらnullptr)
		//==========================================================
		template <typename T>
		T *GetComponent()
		{
			for (int i = 0; i < components_.size(); ++i)
			{
				if (typeid(*components_[i]) == typeid(T))
				{
					return (T *)components_[i];
				}
			}

			return nullptr;
		}

		//==========================================================
		// 概要  :指定されたComponentの派生クラスTまたはTを継承したクラスへのポインタの取得を試みます。
		// 戻り値:Componentの派生クラスTまたはTを継承したクラスへのポインタ(もしなかったらnullptr)
		//==========================================================
		template <typename T>
		T *GetComponentInherit()
		{
			for (int i = 0; i < components_.size(); ++i)
			{
				T *p = dynamic_cast<T *>(components_[i]);
				if (p != nullptr)
				{
					return p;
				}
			}

			return nullptr;
		}

	protected:

		// methods

	private:
		// variables
		std::vector<Component *> components_;

		// methods

	};

}


#endif