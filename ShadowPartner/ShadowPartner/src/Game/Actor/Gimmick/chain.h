//==========================================================
// �T�v  :�|�؃R���|�[�l���g
// Author:Ittoto
// Copyright(c) Utsurugi.All right reserved.
//==========================================================
#ifndef _GAME_ACTOR_GIMMICK_CHAIN_H_
#define _GAME_ACTOR_GIMMICK_CHAIN_H_

#include "../../../Base/Element/component.h"

namespace physics
{
	class BoxCollider;
	class RevoluteJoint;
	class RopeJoint;
}

namespace shadowpartner
{
	class Sprite;
	class Scene;

	struct ChainInitializer
	{
		math::Vector2 first_pos_;	// �ŏ��̃`�F�[��������ꏊ
		math::Vector2 next_diff_;	// ����̃`�F�[��������ꏊ�܂ł̍���
		int pieces_count_;			// �`�F�[���͂����̃s�[�X�łł��Ă���̂�
		float piece_width_;
		float piece_height_;

		ChainInitializer()
			:first_pos_(Vector2::zero())
			, next_diff_(Vector2::right())
			, pieces_count_(2)
			, piece_width_(0.1f)
			, piece_height_(0.1f)
		{

		}
	};

	class Chain : public Component
	{
	public:
		Chain(ChainInitializer initializer,Scene *scene);

		void Start() override;

		void Cutting(int cut_joint_index_);

	protected:

	private:
		int piece_count_;
		int joint_count_;
		physics::RopeJoint *rope_joint_;
		std::vector <GameObject *>chain_pieces_;		// 
		std::vector <physics::RevoluteJoint *>chain_joints_;
	};

}	// namespace shadowpartner

#endif	// _GAME_ACTOR_GIMMICK_TREE_H_