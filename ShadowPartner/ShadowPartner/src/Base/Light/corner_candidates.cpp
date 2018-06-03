//==========================================================
// 概要  :光の候補点の集合
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
	// マクロ
	//**********************************************************

	//**********************************************************
	// 定数
	//**********************************************************

	// Staticメンバ
	CornerCandidates *CornerCandidates::instance_ = nullptr;
	vector<Vector2> CornerCandidates::static_points_;

	// コンストラクタ
	void CornerCandidates::Init()
	{
		if (instance_ == nullptr)
		{
			instance_ = new CornerCandidates();
		}
	}

	// デストラクタ
	void CornerCandidates::Uninit()
	{
		if (instance_ != nullptr)
		{
			delete instance_;
			instance_ = nullptr;
		}
	}

	//==========================================================
	// 概要  :与えられたタイル情報を元に候補点を事前計算します。
	// 引数  :タイルステージのコンテナ
	//==========================================================
	void CornerCandidates::PreCalculate(vector<Stage *> stages)
	{

	}

	//==========================================================
	// 概要  :与えられたコライダーを元に候補点を事前計算します。
	// 引数  :コライダーのコンテナ
	//==========================================================
	void CornerCandidates::PreCalculate(vector<Collider *> colliders)
	{
		vector<Vector2> additional;	// 追加する候補点の集合

		// 一つ一つのコライダーの種類ごとに候補点の取得を行う。
		for (int i = 0;i < colliders.size();++i)
		{
			if (colliders[i]->Is<BoxCollider>())
			{
				// BoxColliderの場合
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
				// CircleColliderの場合
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
	// 概要  :事前計算した頂点をクリア
	//==========================================================
	void CornerCandidates::Clear()
	{
		instance_->static_points_.clear();
	}
	
	// コライダーの中心が
	static const float REGARD_AS_SAME_OBJECT = 0.01f;

	//==========================================================
	// 概要  :ライトの頂点の候補点の集合を返します。
	// 引数  :
	//	colliders:光を遮る動的なコライダー
	//	center   :光の中心点
	//	distance :光の届く距離
	// 戻り値:候補点の集合
	//==========================================================
	vector<Vector2> CornerCandidates::GetCandidatePoints
		(
			std::vector<physics::Collider *> colliders,
			const math::Vector2 &light_center,
			const float &distance
			)
	{
		vector<Vector2> candidate_points;	// 候補点の集合

		// あらかじめ探した点の中から光の届きうる範囲に入っているものを探す
		for (int i = 0;i < static_points_.size();++i)
		{
			if (LengthSq(static_points_[i] - light_center) < distance * distance)
			{
				candidate_points.push_back(static_points_[i]);
			}
		}

		vector<Vector2> additional;	// 追加する候補点の集合

		// 一つ一つのコライダーの種類ごとに候補点の取得を行う。
		for (int i = 0;i < colliders.size();++i)
		{
			if (LengthSq(light_center - colliders[i]->transform_->position_) < REGARD_AS_SAME_OBJECT)
				continue;

			if (colliders[i]->Is<BoxCollider>())
			{
				// BoxColliderの場合
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
				// CircleColliderの場合
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
	// 概要  :BoxColliderを元に候補点を返します。
	// 引数  :
	//	box     :光を遮るboxコライダー
	//	center  :光の中心点
	//	distance:光の届く距離
	// 戻り値:候補点の集合
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

			// もし光源からの距離が光の範囲以内であれば追加
			if (LengthSq(point - light_center) < distance * distance)
			{
				additional_point.push_back(point);
			}
		}
		return additional_point;
	}

	//==========================================================
	// 概要  :CircleColliderを元に候補点を返します。
	// 引数  :
	//	circle  :光を遮るcircleコライダー
	//	center  :光の中心点
	//	distance:光の届く距離
	// 戻り値:候補点の集合
	//==========================================================
	vector<Vector2> CornerCandidates::GetCandidatesFromCircle(Collider *collider, const math::Vector2 &light_center, const float &distance)
	{
		CircleCollider *circle = (CircleCollider *)collider;

		Vector2 circle_center = circle->transform_->position_;
		float radius = circle->GetRadius();

		Vector2 light_to_cirlce = circle_center - light_center;	// 光源からCircleColliderまでのベクトル
		Vector2 light_to_cirlce_normal;							// ↑の法線ベクトル

		// 光源からCircleColliderへの接線の接点までの距離
		float light_to_contact = sqrtf(LengthSq(light_to_cirlce) - (radius * radius));

		// ライトと円の中心を結ぶ線分に、接点から下した垂線の足までの距離
		float vertical = radius * light_to_contact / Length(light_to_cirlce);

		// ライトからverticalまでの距離
		float light_to_vertical = light_to_contact * vertical / radius;

		light_to_cirlce.Normalize();
		light_to_cirlce_normal = Vector2(-light_to_cirlce.y, light_to_cirlce.x);

		Vector2 contact1, contact2;	// ライトから円までの二つの接点

		contact1 = light_center + (light_to_vertical * light_to_cirlce) + (vertical * light_to_cirlce_normal);

		contact2 = light_center + (light_to_vertical * light_to_cirlce) + (vertical * -light_to_cirlce_normal);

		vector<Vector2> additional_point;

		additional_point.push_back(contact1);
		additional_point.push_back(contact2);

		return additional_point;
	}
}
