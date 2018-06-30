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
#define LIGHT_RECEIVABLE_LAYER (1 << Layer::kDefaultLayer + 1 << Layer::kPlayerLayer)

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
	void CornerCandidates::PreCalculate(Stage *stages)
	{
		if (stages->game_object_->layer_ & ~LIGHT_RECEIVABLE_LAYER)
			return;

		vector<Vector2> additional;
		additional = GetCandidatesFromTilemap(stages->tilemap_collider, Vector2::zero(), FLT_MAX);

		static_points_.insert(static_points_.end(), additional.begin(), additional.end());
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
			if (!((1 << colliders[i]->game_object_->layer_) & LIGHT_RECEIVABLE_LAYER))
				continue;

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
			// ここではStaticBodyは追加しない
			if (colliders[i]->body_->GetType() == b2BodyType::b2_staticBody)
				continue;

			if (!((1 << colliders[i]->game_object_->layer_) & ~LIGHT_RECEIVABLE_LAYER))
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
			else if (colliders[i]->Is<TileMapCollider>())
			{
				// TilemapColliderの場合
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

		b2Vec2 p = box->body_->GetTransform().p;
		Vector2 box_center = Vector2(p.x, p.y);
		Vector2 size = box->GetSize();

		Vector2 point;

		// 追加する候補点
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

		b2Vec2 p = circle->body_->GetTransform().p;
		Vector2 circle_center = Vector2(p.x, p.y);
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

		// 追加する候補点
		vector<Vector2> additional_point;

		additional_point.push_back(contact1);
		additional_point.push_back(contact2);

		return additional_point;
	}

	//==========================================================
	// 概要  :TilemapColliderを元に候補点を返します。
	// 引数  :
	//	circle  :光を遮るcircleコライダー
	//	center  :光の中心点
	//	distance:光の届く距離
	// 戻り値:候補点の集合
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

		// 追加する候補点
		vector<Vector2> additional_point;

		// チェックする格子点を囲む四方の格子にコライダーがあるかどうか
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
				// この格子点が光の頂点になりうるかどうかを確認する
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
					// 候補点ではないので何もしない。
				}
				break;

				default:
				{
					// 候補点なので追加する
					additional_point.push_back(tilemap_upper_left + Vector2(w * x, h * y));
				}
				break;
				}

				// 次の格子点にずらす
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
