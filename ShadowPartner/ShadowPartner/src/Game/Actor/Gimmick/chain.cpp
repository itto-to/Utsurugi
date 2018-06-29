//==========================================================
// �T�v  :�|�؃R���|�[�l���g
// Author:Ittoto
// Copyright(c) Utsurugi.All right reserved.
//==========================================================
#include "chain.h"

#include "../../../Base/Physics/physics.h"
#include "../../../Base/2D/sprite.h"
#include "../../../Base/System/scene.h"

using namespace physics;

#define CHAIN_PIECE_TEXTURE_NAME "Resources/Texture/Stage/IvyTemp.png"

namespace shadowpartner
{
	//==========================================================
	// �T�v  :�`�F�[���𐶐����܂��B
	// ����  :��������`�F�[���Ɋւ���ݒ���܂Ƃ߂��\����
	//==========================================================
	Chain::Chain(ChainInitializer init,Scene *scene)
	{
		GameObject *next_chain_ = new GameObject();
		next_chain_->transform_->position_ = init.first_pos_;

		// �ŏ��̃`�F�[���̃s�[�X�����
		BoxInitializer box_init;

		box_init.pos_ = init.first_pos_;
		box_init.width_ = init.piece_width_;
		box_init.height_ = init.piece_height_;
		box_init.fixed_rotation_ = false;

		next_chain_->AddComponent(new BoxCollider(box_init));

		Sprite *sprite = new Sprite(CHAIN_PIECE_TEXTURE_NAME);
		sprite->SetSize(Vector2(init.piece_width_, init.piece_height_));
		sprite->SetColor(D3DCOLOR_RGBA(0xff, 0xff, 0xff, 0xff));
		next_chain_->AddComponent(sprite);

		chain_pieces_.push_back(next_chain_);
		scene->AddGameObject(next_chain_);

		RevoluteInitializer revolute_init;
		revolute_init.collide_connected_ = false;
		revolute_init.enable_limit_ = true;
		revolute_init.lower_angle_ = -60.0f;
		revolute_init.upper_angle_ = 60.0f;
		revolute_init.world_pos_ = box_init.pos_ + (init.next_diff_ / 2.0f);

		for (int i = 0;i < init.pieces_count_ - 1;++i)
		{
			next_chain_ = new GameObject();
			next_chain_->transform_->position_ = init.first_pos_ + (init.next_diff_ * (i + 1));

			// ���̃`�F�[���̃{�b�N�X�R���C�_�[�̐ݒ�
			box_init.pos_ += init.next_diff_;

			next_chain_->AddComponent(new BoxCollider(box_init));
			
			sprite = new Sprite(CHAIN_PIECE_TEXTURE_NAME);
			sprite->SetSize(Vector2(init.piece_width_, init.piece_height_));
			sprite->SetColor(D3DCOLOR_RGBA(0xff, 0xff, 0xff, 0xff));
			next_chain_->AddComponent(sprite);
			
			chain_pieces_.push_back(next_chain_);
			scene->AddGameObject(next_chain_);

			// �W���C���g�̐ݒ�
			revolute_init.collider_a_ = chain_pieces_[i]->GetComponent<BoxCollider>();
			revolute_init.collider_b_ = chain_pieces_[i + 1]->GetComponent<BoxCollider>();

			revolute_init.local_anchor_a_ = init.next_diff_ / 2.0f;
			revolute_init.local_anchor_b_ = -init.next_diff_ / 2.0f;

			// �W���C���g�����
			chain_joints_.push_back(new RevoluteJoint(revolute_init));

			revolute_init.world_pos_ += init.next_diff_;
		}

		first_ = chain_pieces_[0]->GetComponent<BoxCollider>();
		last_ = chain_pieces_[init.pieces_count_ - 1]->GetComponent<BoxCollider>();

		// ���[�v�̐ݒ�
		RopeInitializer rope_init;
		rope_init.collider_a_ = first_;
		rope_init.collider_b_ = last_;

		rope_init.max_length_ = Length(init.next_diff_ * init.pieces_count_ - init.first_pos_) + 0.01f;

		// ���[�v�̍쐬
		rope_joint_ = new RopeJoint(rope_init);
	}

	void Chain::Start()
	{
	}

}	// namespace shadowpartner