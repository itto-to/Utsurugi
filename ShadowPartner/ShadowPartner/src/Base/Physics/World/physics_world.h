//==========================================================
// 概要  :ワールド
// Author:Itsuki Namito
// Copyright(c) Utsurugi.All right reserved.
//==========================================================

#ifndef _BASE_PHYSICS_WORLD_PHYSICS_WORLD_H_
#define _BASE_PHYSICS_WORLD_PHYSICS_WORLD_H_

//**********************************************************
// インクルードファイル
//**********************************************************
#include "../Element/collider.h"

namespace physics
{
	//==========================================================
	// 概要  :ワールド
	//==========================================================
	class PhysicsWorld
	{
	public:
		// variables
		
		// methods
		static b2Body *CreateBody(const b2BodyDef *body_def);

		static void Init();
		static void Uninit();
		static void Step();

		// Accessor・Mutator
		static void SetTimeStep(const float &value);
		static float GetTimeStep();
		static void SetVelocityIteration(const int &value);
		static int GetVelocityIteration();
		static void SetPositionIteration(const int &value);
		static int GetPositionIteration();

	private:
		PhysicsWorld();
		void operator=(const PhysicsWorld &obj) {};
		PhysicsWorld(const PhysicsWorld &obj) :world_(b2World(b2Vec2(0,0))){};

		// variables
		static PhysicsWorld *instance_;
		b2World world_;
		float time_step_;
		int velocity_iteration_;
		int position_iteration_;

		std::vector<Collider *> colliders_;

		// methods

	};
}

#endif