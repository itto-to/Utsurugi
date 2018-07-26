//==========================================================
// 概要  :ギミック作動用インターフェース
// Author:Ittoto
// Copyright(c) Utsurugi.All right reserved.
//==========================================================
#ifndef _GAME_ACTOR_COMMON_GIMMICKINTERFACE_H_
#define _GAME_ACTOR_COMMON_GIMMICKINTERFACE_H_

#include "../../../Base/Element/component.h"
#include "../../../Base/Physics/physics.h"

namespace shadowpartner
{
	class GameObject;

	class GimmickInterface : public physics::BoxCollider
	{
	public:
		GimmickInterface();
		GimmickInterface(const physics::BoxInitializer &ini);
		virtual void ActivateGimmick(GameObject *activator) = 0;
		bool IsTouching();
		bool IsActivated() {return is_activated_;}

	protected:
		bool is_activated_;
		bool is_touching_;

		virtual void EnterAction() {};
		virtual void ExitAction() {};
		void OnTriggerEnter(Collider *col) override;
		void OnTriggerExit(Collider *col) override;
	};
}

#endif