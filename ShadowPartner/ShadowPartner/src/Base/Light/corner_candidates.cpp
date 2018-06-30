//==========================================================
// �T�v  :���̌��_�̏W��
// Author:Itsuki Namito
// Copyright(c) Utsurugi.All right reserved.
//==========================================================
#include "corner_candidates.h"

using namespace std;
using namespace math;
using namespace physics;

namespace shadowpartner
{
	//**********************************************************
	// �}�N��
	//**********************************************************
#define LIGHT_RECEIVABLE_LAYER (1 << Layer::kDefaultLayer + 1 << Layer::kPlayerLayer)

	//**********************************************************
	// �萔
	//**********************************************************

	// Static�����o
	CornerCandidates *CornerCandidates::instance_ = nullptr;
	vector<Vector2> CornerCandidates::static_points_;

	// �R���X�g���N�^
	void CornerCandidates::Init()
	{
		if (instance_ == nullptr)
		{
			instance_ = new CornerCandidates();
		}
	}

	// �f�X�g���N�^
	void CornerCandidates::Uninit()
	{
		if (instance_ != nullptr)
		{
			delete instance_;
			instance_ = nullptr;
		}
	}

	//==========================================================
	// �T�v  :�^����ꂽ�^�C���������Ɍ��_�����O�v�Z���܂��B
	// ����  :�^�C���X�e�[�W�̃R���e�i
	//==========================================================
	void CornerCandidates::PreCalculate(Stage *stages)
	{
		if (stages->game_object_->layer_ & ~LIGHT_RECEIVABLE_LAYER)
			return;

		vector<Vector2> additional;
		additional = GetCandidatesFromTilemap(stages->tilemap_collider, Vector2::zero(), FLT_MAX);

		static_points_.insert(static_points_.end(), additional.begin(), additional.end());
	}

	//==========================================================
	// �T�v  :�^����ꂽ�R���C�_�[�����Ɍ��_�����O�v�Z���܂��B
	// ����  :�R���C�_�[�̃R���e�i
	//==========================================================
	void CornerCandidates::PreCalculate(vector<Collider *> colliders)
	{
		vector<Vector2> additional;	// �ǉ�������_�̏W��

		// ���̃R���C�_�[�̎�ނ��ƂɌ��_�̎擾���s���B
		for (int i = 0;i < colliders.size();++i)
		{
			if (!((1 << colliders[i]->game_object_->layer_) & LIGHT_RECEIVABLE_LAYER))
				continue;

			if (colliders[i]->Is<BoxCollider>())
			{
				// BoxCollider�̏ꍇ
				additional = GetCandidatesFromBox
					(
						colliders[i],
						Vector2::zero(),
						FLT_MAX
						);
				static_points_.insert(static_points_.end(), additional.begin(), additional.end());
			}
			else if (colliders[i]->Is<CircleCollider>())
			{
				// CircleCollider�̏ꍇ
				additional = GetCandidatesFromCircle
					(
						colliders[i],
						Vector2::zero(),
						FLT_MAX
						);
				static_points_.insert(static_points_.end(), additional.begin(), additional.end());
			}
		}
	}

	//==========================================================
	// �T�v  :���O�v�Z�������_���N���A
	//==========================================================
	void CornerCandidates::Clear()
	{
		instance_->static_points_.clear();
	}

	// �R���C�_�[�̒��S��
	static const float REGARD_AS_SAME_OBJECT = 0.01f;

	//==========================================================
	// �T�v  :���C�g�̒��_�̌��_�̏W����Ԃ��܂��B
	// ����  :
	//	colliders:�����Ղ铮�I�ȃR���C�_�[
	//	center   :���̒��S�_
	//	distance :���̓͂�����
	// �߂�l:���_�̏W��
	//==========================================================
	vector<Vector2> CornerCandidates::GetCandidatePoints
		(
			std::vector<physics::Collider *> colliders,
			const math::Vector2 &light_center,
			const float &distance
			)
	{
		vector<Vector2> candidate_points;	// ���_�̏W��

		// ���炩���ߒT�����_�̒�������̓͂�����͈͂ɓ����Ă�����̂�T��
		for (int i = 0;i < static_points_.size();++i)
		{
			if (LengthSq(static_points_[i] - light_center) < distance * distance)
			{
				candidate_points.push_back(static_points_[i]);
			}
		}

		vector<Vector2> additional;	// �ǉ�������_�̏W��
		// ���̃R���C�_�[�̎�ނ��ƂɌ��_�̎擾���s���B
		for (int i = 0;i < colliders.size();++i)
		{
			// �����ł�StaticBody�͒ǉ����Ȃ�
			if (colliders[i]->body_->GetType() == b2BodyType::b2_staticBody)
				continue;

			if (!((1 << colliders[i]->game_object_->layer_) & ~LIGHT_RECEIVABLE_LAYER))
				continue;

			if (colliders[i]->Is<BoxCollider>())
			{
				// BoxCollider�̏ꍇ
				additional = GetCandidatesFromBox
					(
						colliders[i],
						light_center,
						distance
						);
				candidate_points.insert(candidate_points.end(), additional.begin(), additional.end());
			}
			else if (colliders[i]->Is<CircleCollider>())
			{
				// CircleCollider�̏ꍇ
				additional = GetCandidatesFromCircle
					(
						colliders[i],
						light_center,
						distance
						);
				candidate_points.insert(candidate_points.end(), additional.begin(), additional.end());
			}
			else if (colliders[i]->Is<TileMapCollider>())
			{
				// TilemapCollider�̏ꍇ
				additional = GetCandidatesFromTilemap
					(
						colliders[i],
						light_center,
						distance
						);
				candidate_points.insert(candidate_points.end(), additional.begin(), additional.end());
			}
		}
		return candidate_points;
	}

	//==========================================================
	// �T�v  :BoxCollider�����Ɍ��_��Ԃ��܂��B
	// ����  :
	//	box     :�����Ղ�box�R���C�_�[
	//	center  :���̒��S�_
	//	distance:���̓͂�����
	// �߂�l:���_�̏W��
	//==========================================================
	vector<Vector2> CornerCandidates::GetCandidatesFromBox(Collider *collider, const math::Vector2 &light_center, const float &distance)
	{
		BoxCollider *box = (BoxCollider *)collider;

		b2Vec2 p = box->body_->GetTransform().p;
		Vector2 box_center = Vector2(p.x, p.y);
		Vector2 size = box->GetSize();

		Vector2 point;

		// �ǉ�������_
		vector<Vector2> additional_point;

		for (int i = 0; i < 4;++i)
		{
			point = box_center + Vector2
				(
					(i % 2 == 0) ? size.x : -size.x,
					(i / 2 == 0) ? size.y : -size.y
					);

			// ������������̋��������͈͈̔ȓ��ł���Βǉ�
			if (LengthSq(point - light_center) < distance * distance)
			{
				additional_point.push_back(point);
			}
		}
		return additional_point;
	}

	//==========================================================
	// �T�v  :CircleCollider�����Ɍ��_��Ԃ��܂��B
	// ����  :
	//	circle  :�����Ղ�circle�R���C�_�[
	//	center  :���̒��S�_
	//	distance:���̓͂�����
	// �߂�l:���_�̏W��
	//==========================================================
	vector<Vector2> CornerCandidates::GetCandidatesFromCircle(Collider *collider, const math::Vector2 &light_center, const float &distance)
	{
		CircleCollider *circle = (CircleCollider *)collider;

		b2Vec2 p = circle->body_->GetTransform().p;
		Vector2 circle_center = Vector2(p.x, p.y);
		float radius = circle->GetRadius();

		Vector2 light_to_cirlce = circle_center - light_center;	// ��������CircleCollider�܂ł̃x�N�g��
		Vector2 light_to_cirlce_normal;							// ���̖@���x�N�g��

		// ��������CircleCollider�ւ̐ڐ��̐ړ_�܂ł̋���
		float light_to_contact = sqrtf(LengthSq(light_to_cirlce) - (radius * radius));

		// ���C�g�Ɖ~�̒��S�����Ԑ����ɁA�ړ_���牺���������̑��܂ł̋���
		float vertical = radius * light_to_contact / Length(light_to_cirlce);

		// ���C�g����vertical�܂ł̋���
		float light_to_vertical = light_to_contact * vertical / radius;

		light_to_cirlce.Normalize();
		light_to_cirlce_normal = Vector2(-light_to_cirlce.y, light_to_cirlce.x);

		Vector2 contact1, contact2;	// ���C�g����~�܂ł̓�̐ړ_

		contact1 = light_center + (light_to_vertical * light_to_cirlce) + (vertical * light_to_cirlce_normal);

		contact2 = light_center + (light_to_vertical * light_to_cirlce) + (vertical * -light_to_cirlce_normal);

		// �ǉ�������_
		vector<Vector2> additional_point;

		additional_point.push_back(contact1);
		additional_point.push_back(contact2);

		return additional_point;
	}

	//==========================================================
	// �T�v  :TilemapCollider�����Ɍ��_��Ԃ��܂��B
	// ����  :
	//	circle  :�����Ղ�circle�R���C�_�[
	//	center  :���̒��S�_
	//	distance:���̓͂�����
	// �߂�l:���_�̏W��
	//==========================================================
	vector<Vector2> CornerCandidates::GetCandidatesFromTilemap(Collider *collider, const math::Vector2 &light_center, const float &distance)
	{
		TileMapCollider *tilemap = (TileMapCollider *)collider;
		Stage *stage = collider->GetComponent<Stage>();

		b2Vec2 p = tilemap->body_->GetTransform().p;
		Vector2 tilemap_center = Vector2(p.x, p.y);
		float w, h;
		w = tilemap->GetSize().x;
		h = tilemap->GetSize().y;

		Vector2 tilemap_upper_left = Vector2(tilemap_center.x - w * stage->cell_horizontal / 2.0f, tilemap_center.y + h * stage->cell_vertical);

		// �ǉ�������_
		vector<Vector2> additional_point;

		// �`�F�b�N����i�q�_���͂ގl���̊i�q�ɃR���C�_�[�����邩�ǂ���
		bool ul, ur, ll, lr; // upper left,upper right,lower left,lower right
		int check;

		for (int y = 0;y < stage->cell_vertical + 1;++y)
		{
			ul = false;
			ll = false;

			if (y > 0)
			{
				ur = stage->collision_exist[(y - 1) * stage->cell_horizontal];
			}
			else
			{
				ur = false;
			}

			if (y < stage->cell_vertical)
			{
				lr = stage->collision_exist[y * stage->cell_horizontal];
			}
			else
			{
				lr = false;
			}

			for (int x = 0;x < stage->cell_horizontal + 1;++x)
			{
				// ���̊i�q�_�����̒��_�ɂȂ肤�邩�ǂ������m�F����
				check = static_cast<int>(ul) << 0 + static_cast<int>(ur) << 1 + static_cast<int>(ll) << 2 + static_cast<int>(lr) << 3;

				switch (check)
				{
				case 0:
				case 3:
				case 5:
				case 10:
				case 12:
				case 15:
				{
					// ���_�ł͂Ȃ��̂ŉ������Ȃ��B
				}
				break;

				default:
				{
					// ���_�Ȃ̂Œǉ�����
					additional_point.push_back(tilemap_upper_left + Vector2(w * x, h * y));
				}
				break;
				}

				// ���̊i�q�_�ɂ��炷
				ul = ur;
				ll = lr;

				if (y > 0)
				{
					ur = stage->collision_exist[(y - 1) * stage->cell_horizontal + x];
				}
				else
				{
					ur = false;
				}

				if (y < stage->cell_vertical)
				{
					lr = stage->collision_exist[(y + 1) * stage->cell_horizontal + x];
				}
				else
				{
					lr = false;
				}
			}
		}

		return additional_point;
	}

}
