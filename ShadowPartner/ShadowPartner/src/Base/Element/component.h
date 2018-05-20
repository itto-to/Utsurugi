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

namespace shadowpartner
{
	class GameObject;
	class Transform;

	enum Tag
	{
		Untagged = 0,
		Player,
		Enemy,
		
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

		void SetActive(bool is_active);

		void Attached(GameObject *game_object, Transform *transform, Tag tag);
		Component *GetComponent(type_info &type);

	protected:

		// methods
		virtual HRESULT Awake() { return S_OK; };	// コンストラクタで呼ばれます.game_object_やtransform_はnullptrです。
		virtual void Start() {};					// ゲームオブジェクトにアタッチされたタイミングやSetActive(true)で呼ばれます。
		virtual void Uninit() {};
		virtual void Update() {};
		virtual void Draw() {};

	private:
		// variables

		// methods

	};
}

#include "gameobject.h"
#include "transform.h"

#endif