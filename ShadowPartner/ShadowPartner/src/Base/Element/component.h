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
#include <typeinfo>

namespace physics
{
	class Collider;
}


namespace shadowpartner
{
	class GameObject;
	class Transform;

	enum Tag
	{
		kUntagged = 0,
		kPlayer,
		kShadow,
		kEnemy,
		kLargeLight,
		kMiddleLight,
		kSmallLight,
		kClimb,
		kTree,
		kPlayerTrigger,
		kPlayerLandingTrigger,
		kGimmick,
	};

	//==========================================================
	// 概要  :GameObjectの構成単位の基底クラス
	//==========================================================
	class Component
	{
	public:
		Component();
		Component(Component &copy);
		virtual ~Component() {};
		
		// variables
		bool is_active_;
		GameObject *game_object_;
		Tag tag_;
		Transform *transform_;

		// methods
		void UpdateComponent();
		void DrawComponent();

		virtual void SetActive(bool is_active);

		void Attached(GameObject *game_object, Transform *transform, Tag tag);

		//==========================================================
		// 概要  :指定されたComponentの派生クラスへのポインタの取得を試みます。
		// 戻り値:Componentの派生クラスへのポインタ(もしなかったらnullptr)
		//==========================================================
		template <typename T>
		T *GetComponent() 
		{
			return game_object_->GetComponent<T>();
		}

		//==========================================================
		// 概要  :指定されたComponentの派生クラスTまたはTを継承したクラスへのポインタの取得を試みます。
		// 戻り値:Componentの派生クラスTまたはTを継承したクラスへのポインタ(もしなかったらnullptr)
		//==========================================================
		template <typename T>
		T *GetComponentInherit()
		{
			return game_object_->GetComponentInherit<T>();
		}

		//==========================================================
		// 概要  :Componentの実体が指定されたクラスであるか調べる。
		// 戻り値:クラスが同じならtrue、違うならfalse
		//==========================================================
		template <typename T>
		bool Is()
		{
			if (typeid(*this) == typeid(T))
			{
				return true;
			}
			return false;
		}

		virtual void OnCollisionEnter(physics::Collider *collider) {}
		virtual void OnCollisionExit(physics::Collider *collider) {}
		virtual void OnCollisionStay(physics::Collider *collider) {}
		virtual void OnTriggerEnter(physics::Collider *collider) {}
		virtual void OnTriggerExit(physics::Collider *collider) {}
		virtual void OnTriggerStay(physics::Collider *collider) {}

		//virtual void OnCollisionEnter(physics::Collider *collider) {}
		//virtual void OnCollisionExit(physics::Collider *collider) {}
		//virtual void OnCollisionStay(physics::Collider *collider) {}
		//virtual void OnTriggerEnter(physics::Collider *collider) {}
		//virtual void OnTriggerExit(physics::Collider *collider) {}
		//virtual void OnTriggerStay(physics::Collider *collider) {}

	protected:

		// methods
		virtual HRESULT Awake() { return S_OK; };	// コンストラクタで呼ばれます.game_object_やtransform_はnullptrです。
		virtual void Start() {};					// ゲームオブジェクトにアタッチされたタイミングやSetActive(true)で呼ばれます。
		virtual void Uninit() {};
		virtual void Update() {};
		virtual void FixedUpdate() {};
		virtual void Draw() {};

	private:
		// variables

		// methods
	};
}

#include "gameobject.h"
#include "transform.h"

#endif