//==========================================================
// 概要  :倒木コンポーネント
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
		math::Vector2 first_pos_;	// 最初のチェーンがある場所
		math::Vector2 next_diff_;	// 一つ次のチェーンがある場所までの差分
		int pieces_count_;			// チェーンはいくつのピースでできているのか
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