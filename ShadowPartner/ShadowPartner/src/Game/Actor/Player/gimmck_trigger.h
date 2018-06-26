//==========================================================
// �T�v  :�M�~�b�N�Ƃ̏Փˌ��o�p�g���K�[
// Author:Ittoto
// Copyright(c) Utsurugi.All right reserved.
//==========================================================

#ifndef _GAME_ACTOR_PLAYER_GIMMICKTRIGGER_H_
#define _GAME_ACTOR_PLAYER_GIMMICKTRIGGER_H_

#include "../../../Base/Physics/Element/box_collider.h"

namespace shadowpartner
{
	enum LightType {
		kLarge,
		kMiddle,
		kSmall,
		kLightNone,
	};

	class GimmickTrigger : public physics::BoxCollider
	{
	public:

		GimmickTrigger(const physics::BoxInitializer &box_init);
		void OnTriggerEnter(Collider *col) override;
		void OnTriggerExit(Collider *col) override;

		LightType HittingLightType();
		bool CanClimb();
		bool IsHitLight();

	protected:
		int small_light_count_;
		int middle_light_count_;
		int large_light_count_;
		int climb_count_;		// ���ݏՓ˂��Ă���o���I�u�W�F�N�g�̃J�E���^�[
	};
}

#endif