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

namespace shadowpartner
{
	class CornerCandidates;
}

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

	enum BodyType
	{
		kDynamicBody,
		kKinematicBody,
		kStaticBody,
	};

	//==========================================================
	// 概要  :全コライダーの基底クラス
	//==========================================================
	class Collider : public Component
	{
	public:

		Collider();
		Collider(Collider &copy);
		virtual ~Collider();

		// variables
		PhysicsShape shape_;
		bool is_trigger_;	// トリガーとして設定するかどうか

		float friction_;	// 動摩擦係数
		float bounciness_;	// 反発係数

		int index_;	// ワールドに紐づけられたインデックス

		unsigned short category_bits_;
		unsigned short mask_bits_;
		

		// methods
		virtual void SetActive(bool is_active) override;
		void SetSleepingAllowed(bool flag);

		virtual void SetTransform(const Vector2 &pos, const float &ori);

		virtual Vector2 GetPosition();
		virtual float GetAngle();

		void AddForce(const Vector2 &force);
		void AddForceToPoint(const Vector2 &force, const Vector2 &point);
		void AddTorque(const float torque);
		void Move(const Vector2 &move);

		void SetVelocity(const Vector2 &velo);
		Vector2 Velocity() const;
		float VelocityX() const;
		void SetVelocityX(float x);
		float VelocityY() const;
		void SetVelocityY(float y);
		float GravityScale() const;
		void SetGravityScale(float scale);

		void SetAwake(bool flag);

		void Stop();

		friend class PhysicsWorld;
		friend class PhysicsFunc;
		friend class Joint;
		friend class RevoluteJoint;
		friend class shadowpartner::CornerCandidates;

	protected:
		// variables
		b2Body *body_;
		Vector2 offset_;

		// methods
		void FixedUpdate();

		//virtual void OnCollisionEnter(Collider *hit) {};
		//virtual void OnCollisionStay(Collider *hit) {};
		//virtual void OnCollisionExit(Collider *hit) {};
		//virtual void OnTriggerEnter(Collider *hit) {};
		//virtual void OnTriggerStay(Collider *hit) {};
		//virtual void OnTriggerExit(Collider *hit) {};

	private:
		// variables


		// methods

	};
}

#endif