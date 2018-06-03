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
	void CornerCandidates::PreCalculate(vector<Stage *> stages)
	{

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
			if (LengthSq(light_center - colliders[i]->transform_->position_) < REGARD_AS_SAME_OBJECT)
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

		Vector2 box_center = box->transform_->position_;
		Vector2 size = box->GetSize();

		Vector2 point;

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

		Vector2 circle_center = circle->transform_->position_;
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

		vector<Vector2> additional_point;

		additional_point.push_back(contact1);
		additional_point.push_back(contact2);

		return additional_point;
	}
}
