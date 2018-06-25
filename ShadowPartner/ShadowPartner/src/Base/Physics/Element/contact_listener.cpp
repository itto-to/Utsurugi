//==========================================================
// �T�v  :�Փ˃��X�i�[
// Author:Ittoto
// Copyright(c) Utsurugi.All right reserved.
//==========================================================
#include "contact_listener.h"

#include <cassert>

#include "../World/physics_world.h"

namespace physics {

	ContactListener *ContactListener::instance_ = nullptr;

	void ContactListener::Init()
	{
		assert(instance_ == nullptr);
		instance_ = new ContactListener();
	}

	void ContactListener::Uninit()
	{
		assert(instance_ != nullptr);
		delete instance_;
		instance_ = nullptr;
	}

	ContactListener::ContactListener()
	{
		PhysicsWorld::instance_->world_.SetContactListener(this);
	}

	void ContactListener::BeginContact(b2Contact *contact)
	{
		Collider *col_a = static_cast<Collider*>(contact->GetFixtureA()->GetBody()->GetUserData());
		Collider *col_b = static_cast<Collider*>(contact->GetFixtureB()->GetBody()->GetUserData());

		if (col_a == nullptr || col_b == nullptr)
			return;

		if (col_a->is_trigger_ || col_b->is_trigger_) {
			col_a->OnTriggerEnter(col_b);
			col_b->OnTriggerEnter(col_a);
		}
		else {
			col_a->OnCollisionEnter(col_b);
			col_b->OnCollisionEnter(col_a);
		}


		////
		//if (col_a->tag_ == Tag::kPlayerTrigger || col_b->tag_ == Tag::kPlayerTrigger)
		//{

		//}

		//// �͈͓��ɂȂ������C�g�̐����v���X
		//if (other->tag_ == kLargeLight)
		//{
		//	hit_large_light++;
		//}
		//else if (other->tag_ == kMiddleLight)
		//{
		//	hit_middle_light++;
		//}
		//else if (other->tag_ == kSmallLight)
		//{
		//	hit_small_light++;
		//}

		//// �͈͓��ɂȂ����c�^�̐����v���X
		//if (other->tag_ == Tag::kClimb)
		//{
		//	hit_climb++;
		//}

	}

	void ContactListener::EndContact(b2Contact *contact)
	{
		Collider *col_a = static_cast<Collider*>(contact->GetFixtureA()->GetBody()->GetUserData());
		Collider *col_b = static_cast<Collider*>(contact->GetFixtureB()->GetBody()->GetUserData());

		if (col_a == nullptr || col_b == nullptr)
			return;

		if (col_a->is_trigger_ || col_b->is_trigger_) {
			col_a->OnTriggerExit(col_b);
			col_b->OnTriggerExit(col_a);
		}
		else {
			col_a->OnCollisionExit(col_b);
			col_b->OnCollisionExit(col_a);
		}
	}

	void ContactListener::PreSolve(b2Contact * contact, const b2Manifold *old_manifold)
	{
	}

	void ContactListener::PostSolve(b2Contact * contact, const b2ContactImpulse *impulse)
	{
		Collider *col_a = static_cast<Collider*>(contact->GetFixtureA()->GetBody()->GetUserData());
		Collider *col_b = static_cast<Collider*>(contact->GetFixtureB()->GetBody()->GetUserData());


		if (col_a == nullptr || col_b == nullptr)
			return;

		if (col_a->is_trigger_) {
			col_a->OnTriggerStay(col_b);
			col_b->OnTriggerStay(col_a);
		}
		else
		{
			col_a->OnCollisionStay(col_b);
			col_b->OnCollisionStay(col_a);
		}

	}

}	// namespace physics