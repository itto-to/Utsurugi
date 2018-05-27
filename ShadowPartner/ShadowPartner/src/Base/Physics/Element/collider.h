//==========================================================
// 概要  :全コライダーの基底クラス
// Author:Itsuki Namito
// Copyright(c) Utsurugi.All right reserved.
//==========================================================

#ifndef _BASE_PHYSICS_ELEMENT_COLLIDER_H_
#define _BASE_PHYSICS_ELEMENT_COLLIDER_H_

//**********************************************************
// インクルードファイル
//**********************************************************
#include <Box2D\Box2D.h>
#include "../../Element/component.h"
#include <windows.h>
#include <typeinfo>

#ifdef _DEBUG
#pragma comment (lib,"liquidfun_debug.lib")
#else
#pragma comment (lib, "liquidfun_release.lib")
#endif

using namespace shadowpartner;

namespace physics
{
	enum PhysicsShape
	{
		kBox,
		kCircle,
		kPolygon,
		kEdge,
		kShapeCount
	};

	//==========================================================
	// 概要  :全コライダーの基底クラス
	//==========================================================
	class Collider : public Component
	{
	public:
		Collider();
		Collider(Collider &copy);
		virtual ~Collider() {};

		// variables
		PhysicsShape shape_;
		bool is_trigger_;	// トリガーとして設定するかどうか

		float friction_;	// 動摩擦係数
		float bounciness_;	// 反発係数

		int index_;	// ワールドに紐づけられたインデックス
		// methods
		void SetTransform(const Vector2 &pos, const float &ori);

		Vector2 GetPosition();
		float GetAngle();

		void Stop();

	protected:
		// variables
		b2Body *body_;

		// methods
		void FixedUpdate();

		virtual void OnCollisionEnter(Collider *hit) {};
		virtual void OnCollisionStay(Collider *hit) {};
		virtual void OnCollisionExit(Collider *hit) {};
		virtual void OnTriggerEnter(Collider *hit) {};
		virtual void OnTriggerStay(Collider *hit) {};
		virtual void OnTriggerExit(Collider *hit) {};

	private:
		// variables


		// methods

	};
}

#endif