//==========================================================
// 概要  :移動コンポーネント
// Author:Ittoto
// Copyright(c) Utsurugi.All right reserved.
//==========================================================
#ifndef _GAME_ACTOR_COMMON_MOVABLE_H_
#define _GAME_ACTOR_COMMON_MOVABLE_H_

#include "../../../Base/Element/component.h"

namespace physics
{
class Collider;
}

namespace shadowpartner
{

class Movable : public Component
{
public:
	Movable();
	virtual ~Movable() {};

	// methods
	void Start() override;
	void AddForce(const Vector2 &move);
	void Move(const Vector2 &move);

protected:
	// variables
	physics::Collider *collider_;

	float max_speed_x_;
	float max_speed_y_;

private:

};

}	// namespace shadowpartner

#endif