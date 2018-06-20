//==========================================================
// �T�v  :���C�g�N���X
// Author:Itsuki Namito
// Copyright(c) Utsurugi.All right reserved.
//==========================================================
#include "light.h"
#include "../2D/camera.h"
#include "../../Game/Application/application.h"

#include "corner_candidates.h"

#ifdef _DEBUG
#include "../Debug/debugger.h"
#endif

using namespace std;

namespace shadowpartner
{
	//**********************************************************
	// �}�N��
	//**********************************************************

		//**********************************************************
		// �萔
		//**********************************************************

		// �R���X�g���N�^
	Light::Light(const LightInitializer initializer)
		:light_vertices_(nullptr)
		, direction_(initializer.direction_)
		, angle_(initializer.angle_)
		, radius_(initializer.radius_)
		, light_color_(initializer.color_)
	{
	}

	// �f�X�g���N�^
	Light::~Light()
	{

	}

	// �`�揈��
	void Light::Draw()
	{
		Vector3 world_pos = Vector3(transform_->GetWorldPosition(), 0.0f);
		Vector3 draw_pos = Vector3(world_pos.x, -world_pos.y, 0.0f) / Camera::main_->GetZoom();	// �X�N���[����̕`��ʒu.�܂�y���̕�����ς���
		Vector3 screen_center = Vector3(Application::Instance()->GetScreenWidth() / 2, Application::Instance()->GetScreenHeight() / 2, 0.0f);
		draw_pos += screen_center - Vector3(Camera::main_->transform_->position_, 0.0f) * PIXEL_PER_UNIT;

		//float zoom = Camera::main_->GetZoom();
		//Vector2 world_scale = transform_->GetWorldScale();
		//float width, height;
		//width = texture_.GetWidth() * world_scale.x / zoom;
		//height = texture_.GetHeight() * world_scale.y / zoom;

		ReMesh();		// ���̌`���Čv�Z����

		SetVertex(draw_pos);	// �J�����̈ʒu��Y�[���𓥂܂��A�`��̈ʒu�ɒ��_�����킹��

		texture_.DrawTriangleFan(light_vertices_, vertex_count_ - 2);	//	�`�悷��
	}

	//==========================================================
	// �T�v  :���_�̐ݒ���s���܂��B
	//==========================================================
	void Light::SetVertex(const Vector3 &center)
	{
		for (int i = 0;i < vertex_count_;++i)
		{
			light_vertices_[i].vertex_ = center + 
				Vector3(Vector2(light_world_vertices_[i].x, -light_world_vertices_[i].y), 0.0f) / Camera::main_->GetZoom();
			//center;
			light_vertices_[i].rhw_ = 1.0f;
			light_vertices_[i].diffuse_ = light_color_;
			light_vertices_[i].tex_coor_ = 0.0f;
		}
	}

	//==========================================================
	// �T�v  :���̐F��ύX���܂��B
	// ����  :�ύX�������F�B
	//==========================================================
	void Light::SetColor(const D3DCOLOR &color)
	{
		light_color_ = color;
	}

	//==========================================================
	// �T�v  :���C�g�̌��̌�����ݒ肵�܂��B
	// ����  :���C�g�̌��̌���
	//==========================================================
	void Light::SetDirection(const Vector2 &direction)
	{
		direction_ = Angle(direction);
	}

	//==========================================================
	// �T�v  :���C�g�̍L����ݒ肷��i�x���@�j�B
	// ����  :���C�g�̍L��
	//==========================================================
	void Light::SetAngle(const float &angle)
	{
		angle_ = D3DXToRadian(angle);
	}

	//==========================================================
	// �T�v  :���C�g�̓͂��͈͂��w�肵�܂��B
	// ����  :�͂��͈�
	//==========================================================
	void Light::SetRadius(const float &radius)
	{
		radius_ = radius;
	}

	//==========================================================
	// �T�v  :�\�[�g�ς݂̃��C�g�̒��_���W��Ԃ��B
	// ����  :���_�i�[�p�R���e�i
	//==========================================================
	void Light::GetVertices(std::vector<math::Vector2>& vertices)
	{
		for (int i = 0; i < vertex_count_ - 1; ++i)
		{
			vertices.push_back(light_world_vertices_[i]);
		}
	}

	//==========================================================
	// �T�v  :���̌`���Čv�Z����B
	//==========================================================
	void Light::ReMesh()
	{
		vector<Vector2> new_light_vertices;			// �V�������̒��_�̏W��

		SearchLightVertices(new_light_vertices);	// �V�������̒��_���v�Z����

		SortByAngle(new_light_vertices);			// �Ō�Ƀ\�[�g����
	}

	// ���C��������direction���ǂꂾ�����炷��
	static const float SHIFT_DEGREE = 0.00003f;
	// ���C�̒��������̒l�ȏ�̊����Ȃ�Ղ�ꂸ�ɓ��B�����Ƃ݂Ȃ��B
	static const float VALID_RAY_LENGTH_RATE = 0.99f;
	// �����̓_�����������̒��_�̍ŏ��l
	static const int LIGHT_VERTEX_MIN = 72;
	//==========================================================
	// �T�v  :�V�������̒��_���v�Z����B
	// ����  :���̒��_�̓��ꕨ�ƂȂ�R���e�i
	//==========================================================
	void Light::SearchLightVertices(vector<Vector2> &new_light_vertices)
	{
		// �܂��͌����ƂȂ�_��ǉ�����
		new_light_vertices.push_back(transform_->position_);

		Vector2 point;

		physics::RaycastHit hit_info;
		float angle_unit = 2 * D3DX_PI / LIGHT_VERTEX_MIN;
		for (int i = 0;i < LIGHT_VERTEX_MIN;++i)
		{
			Vector2 direction = Vector2(cosf(angle_unit * i), sinf(angle_unit * i));

			if (!InFan(direction, direction_ - angle_ / 2.0f, direction_ + angle_ / 2.0f))
				continue;

			hit_info = physics::PhysicsFunc::Raycast(transform_->position_, direction, radius_);
			if (hit_info.collider != nullptr)
				new_light_vertices.push_back(hit_info.hit_point);
			else
				new_light_vertices.push_back(transform_->position_ + direction * radius_);
		}

		// ���_���W�߂�
		vector<Vector2> candidate_points = CornerCandidates::GetCandidatePoints(
			physics::PhysicsWorld::instance_->colliders_, transform_->position_,
			radius_);

		// ���C�g�̌��̕����Ɗp�x����L���ȃ��C�̊p�x�����߂�
		float valid_angle_min = Angle(Vector2::right(), direction_) - (angle_ / 2.0f);
		float valid_angle_max = Angle(Vector2::right(), direction_) + (angle_ / 2.0f);

		Vector2 ray_direction_base;		// ���C�̕���
		float ray_angle;				// ���C�̊p�x

		// ���̓������Ă���_��ǉ����Ă���
		for (int i = 0;i < candidate_points.size();++i)
		{
			ray_direction_base = candidate_points[i] - transform_->position_;

			ray_angle = Angle(ray_direction_base);

			// ���C�̊p�x���L���łȂ����Skip
			if (ray_angle < valid_angle_min || ray_angle > valid_angle_max)
				continue;

			// ���C���}�������炵�ĂQ����
			// �P��
			{
				hit_info = physics::PhysicsFunc::Raycast(transform_->position_,
					Rotate(ray_direction_base, SHIFT_DEGREE), radius_);

				if (hit_info.collider != nullptr)
				{
					if (fabsf(hit_info.hit_point.x - transform_->position_.x) >
						fabsf(candidate_points[i].x - transform_->position_.x) * VALID_RAY_LENGTH_RATE)
					{
						new_light_vertices.push_back(hit_info.hit_point);
					}
				}
				else
					new_light_vertices.push_back(transform_->position_ + Normalize(ray_direction_base) * radius_);
			}

			// 2��
			{
				hit_info = physics::PhysicsFunc::Raycast(transform_->position_,
					Rotate(ray_direction_base, -SHIFT_DEGREE), radius_);

				if (hit_info.collider != nullptr)
				{
					if (fabsf(hit_info.hit_point.x - transform_->position_.x) >
						fabsf(candidate_points[i].x - transform_->position_.x) * VALID_RAY_LENGTH_RATE)
					{
						new_light_vertices.push_back(hit_info.hit_point);
					}
				}
				else
					new_light_vertices.push_back(transform_->position_ + Normalize(ray_direction_base) * radius_);
			}
		}
	}

	//==========================================================
	// �T�v  :TriangleFan�ŏ�肭�`��ł���悤�ɂ��邽�߂Ɋp�x�Ń\�[�g���܂�
	// ����  :�\�[�g���������R���e�i
	//==========================================================
	void Light::SortByAngle(const vector<Vector2> &points)
	{
		// �\�[�g�p�o�b�t�@���N���A
		sort_buffer_.clear();

		Vector2 light_center = transform_->position_;	// ���C�g�̌����̈ʒu

		sort_buffer_.push_back(SortTemp(0, FLT_MAX));

		// ����������̒��_�܂ł̃x�N�g�����Ȃ��p�x�ƃC���f�b�N�X��S�Ă̒��_�ɂ����Ēǉ�
		for (int i = 1;i < points.size();++i)
		{
			if (transform_->position_.y <= points[i].y)
				sort_buffer_.push_back(SortTemp(i, Angle(points[i] - light_center)));
			else
				sort_buffer_.push_back(SortTemp(i, 360.0f - Angle(points[i] - light_center)));
		}


#ifdef _DEBUG
		debug::Debug::StopWatchStart(2);
#endif
		// �N�C�b�N�\�[�g���s��
		//QuickSort(1, sort_buffer_.size() - 1);

		// �}�[�W�\�[�g���s��
		//MergeSort(sort_buffer_);

		// �o�u���\�[�g���s���B
		BubbleSort();

#ifdef _DEBUG
		debug::Debug::StopWatchFinish(2);
#endif

		sort_buffer_.push_back(sort_buffer_[1]);
		vertex_count_ = sort_buffer_.size();

		// �O��̒��_���c���Ă�����폜����B
		if (light_vertices_ != nullptr)
		{
			delete[] light_vertices_;
		}

		// ���̒��_���̔z���p�ӂ���
		light_vertices_ = new Vertex2D[vertex_count_];

		if (light_world_vertices_ != nullptr)
		{
			delete[] light_world_vertices_;
		}
		light_world_vertices_ = new Vector2[vertex_count_];

		// �\�[�g�ʂ�ɒ��_���i�[���Ă���
		for (int i = 0;i < vertex_count_ - 1;++i)
		{
			light_world_vertices_[i] = points[sort_buffer_[i].index_] * PIXEL_PER_UNIT;
		}

		light_world_vertices_[vertex_count_ - 1] = points[sort_buffer_[1].index_] * PIXEL_PER_UNIT;
	}

	//==========================================================
	// �T�v  :�N�C�b�N�\�[�g���s���܂��B
	// ����  :
	//	first      :�ŏ��̃C���f�b�N�X
	//	last       :�Ō�̃C���f�b�N�X
	//==========================================================
	void Light::QuickSort(int first, int last)
	{
		// �T�C�Y��3�ȏ�
		if (last - first > 1)
		{
			int less = first, greater = last;

			// ���v�f�̐ݒ�
			int pivot_index = DecisionPivot(less, last);

			if (pivot_index == -1)return;	// �S�ē��l

			const float pivot_angle = (sort_buffer_[first].angle_ + sort_buffer_[pivot_index].angle_) / 2.0f;

			// ���莲����������܂ŁA���v�f�ȏ�ƈȉ��̗v�f�����ւ���B
			while (less < greater)
			{
				while (sort_buffer_[less].angle_ <= pivot_angle)++less;
				while (sort_buffer_[greater].angle_ > pivot_angle)--greater;

				if (less < greater)
				{
					SortTemp temp = sort_buffer_[less];
					sort_buffer_[less] = sort_buffer_[greater];
					sort_buffer_[greater] = temp;
					++less;--greater;
				}
			}

			if (less == greater)
			{
				if (sort_buffer_[less].angle_ < pivot_angle)++less;
				else if (sort_buffer_[greater].angle_ > pivot_angle)--greater;
			}

			// �O���E�㔼���ꂼ��̃u���b�N�̗v�f���Q�ȏ�Ȃ�ċA
			if (less >= first + 2)   QuickSort(first, less - 1);
			if (greater <= last - 2) QuickSort(greater + 1, last);
		}
		else
		{
			// �T�C�Y���Q�Ȃ̂ł�����r���ă\�[�g���ďI��
			if (sort_buffer_[first].angle_ > sort_buffer_[last].angle_)
			{
				SortTemp temp = sort_buffer_[first];
				sort_buffer_[first] = sort_buffer_[last];
				sort_buffer_[last] = temp;
				return;
			}
		}
	}

	//==========================================================
	// �T�v  :���v�f�����肵�܂��B
	// ����  :
	//	first      :�ŏ��̃C���f�b�N�X
	//	last       :�Ō�̃C���f�b�N�X
	// �߂�l:���v�f�̃C���f�b�N�X(-1�Ȃ炷�ׂē��l)
	//==========================================================
	int Light::DecisionPivot(int first, int last)
	{
		int k = first + 1;
		while (k <= last && sort_buffer_[first].angle_ == sort_buffer_[k].angle_)
			++k;

		if (k > last) return -1;

		return k;
	}

	//==========================================================
	// �T�v  :�ŏ��ƍŌ�A�����Ă��̊Ԃ̃C���f�b�N�X���w���l�̒����l��Ԃ��܂�
	// ����  :
	//	first      :�ŏ��̃C���f�b�N�X
	//	last       :�Ō�̃C���f�b�N�X
	// �߂�l:�����l�̃C���f�b�N�X
	//==========================================================
	int Light::MedianIndex(int first, int last)
	{
		int middle = first + (last - first) / 2;

		if (sort_buffer_[first].angle_ < sort_buffer_[last].angle_)
		{
			return (sort_buffer_[last].angle_ < sort_buffer_[middle].angle_) ? last :
				(sort_buffer_[first].angle_ < sort_buffer_[middle].angle_) ? middle : first;
		}
		else
		{
			return (sort_buffer_[last].angle_ > sort_buffer_[middle].angle_) ? last :
				(sort_buffer_[first].angle_ > sort_buffer_[middle].angle_) ? middle : first;
		}
	}

	//==========================================================
	// �T�v  :�}�[�W�\�[�g���s���܂��B
	// ����  :
	//	first      :�ŏ��̃C���f�b�N�X
	//	last       :�Ō�̃C���f�b�N�X
	//==========================================================
	void Light::MergeSort(vector<SortTemp> a)
	{
		if (a.size() > 1)
		{
			int half = a.size() / 2;
			int rest = a.size() - half;

			vector<SortTemp> early, late;

			for (int i = 0;i < half;++i)early.push_back(a[i]);
			for (int i = 0; i < rest;++i)late.push_back(a[half + i]);

			MergeSort(early);
			MergeSort(late);

			Merge(early, late, a);
		}
	}

	//==========================================================
	// �T�v  :�}�[�W���܂��B
	// ����  :
	//	first      :�ŏ��̃C���f�b�N�X
	//	last       :�Ō�̃C���f�b�N�X
	//==========================================================
	void Light::Merge(std::vector<SortTemp> early, std::vector<SortTemp> late, std::vector<SortTemp> a)
	{
		int e = 0, l = 0;

		// �����̔z��ɗv�f���c���Ă���
		while (e < early.size() && l < late.size())
		{
			if (early[e].angle_ <= late[l].angle_)
			{
				a[e + l] = early[e];
				++e;
			}
			else
			{
				a[e + l] = late[l];
				++l;
			}
		}

		for (;e < early.size();++e)
			a[e + l] = early[e];
		for (;l < late.size();++l)
			a[e + l] = late[l];
	}

	//==========================================================
	// �T�v  :�o�u���\�[�g���s���܂��B
	//==========================================================
	void Light::BubbleSort()
	{
		for (int last = sort_buffer_.size() - 1;last > 1;--last)
		{
			for (int i = 0;i < last;++i)
			{
				if (sort_buffer_[i].angle_ < sort_buffer_[i + 1].angle_)
				{
					SortTemp temp = sort_buffer_[i];
					sort_buffer_[i] = sort_buffer_[i + 1];
					sort_buffer_[i + 1] = temp;
				}
			}
		}
	}
}
