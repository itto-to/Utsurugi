//==========================================================
// 概要  :ライトクラス
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
	// マクロ
	//**********************************************************

		//**********************************************************
		// 定数
		//**********************************************************

		// コンストラクタ
	Light::Light(const LightInitializer initializer)
		:light_vertices_(nullptr)
		, direction_(initializer.direction_)
		, angle_(initializer.angle_)
		, radius_(initializer.radius_)
		, light_color_(initializer.color_)
	{
	}

	// デストラクタ
	Light::~Light()
	{

	}

	// 描画処理
	void Light::Draw()
	{
		Vector3 world_pos = Vector3(transform_->GetWorldPosition(), 0.0f);
		Vector3 draw_pos = Vector3(world_pos.x, -world_pos.y, 0.0f) / Camera::main_->GetZoom();	// スクリーン上の描画位置.まずy軸の方向を変える
		Vector3 screen_center = Vector3(Application::Instance()->GetScreenWidth() / 2, Application::Instance()->GetScreenHeight() / 2, 0.0f);
		draw_pos += screen_center - Vector3(Camera::main_->transform_->position_, 0.0f) * PIXEL_PER_UNIT;

		//float zoom = Camera::main_->GetZoom();
		//Vector2 world_scale = transform_->GetWorldScale();
		//float width, height;
		//width = texture_.GetWidth() * world_scale.x / zoom;
		//height = texture_.GetHeight() * world_scale.y / zoom;

		ReMesh();		// 光の形を再計算する

		SetVertex(draw_pos);	// カメラの位置やズームを踏まえ、描画の位置に頂点を合わせる

		texture_.DrawTriangleFan(light_vertices_, vertex_count_ - 2);	//	描画する
	}

	//==========================================================
	// 概要  :頂点の設定を行います。
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
	// 概要  :光の色を変更します。
	// 引数  :変更したい色。
	//==========================================================
	void Light::SetColor(const D3DCOLOR &color)
	{
		light_color_ = color;
	}

	//==========================================================
	// 概要  :ライトの光の向きを設定します。
	// 引数  :ライトの光の向き
	//==========================================================
	void Light::SetDirection(const Vector2 &direction)
	{
		direction_ = Angle(direction);
	}

	//==========================================================
	// 概要  :ライトの広さを設定する（度数法）。
	// 引数  :ライトの広さ
	//==========================================================
	void Light::SetAngle(const float &angle)
	{
		angle_ = D3DXToRadian(angle);
	}

	//==========================================================
	// 概要  :ライトの届く範囲を指定します。
	// 引数  :届く範囲
	//==========================================================
	void Light::SetRadius(const float &radius)
	{
		radius_ = radius;
	}

	//==========================================================
	// 概要  :ソート済みのライトの頂点座標を返す。
	// 引数  :頂点格納用コンテナ
	//==========================================================
	void Light::GetVertices(std::vector<math::Vector2>& vertices)
	{
		for (int i = 0; i < vertex_count_ - 1; ++i)
		{
			vertices.push_back(light_world_vertices_[i]);
		}
	}

	//==========================================================
	// 概要  :光の形を再計算する。
	//==========================================================
	void Light::ReMesh()
	{
		vector<Vector2> new_light_vertices;			// 新しい光の頂点の集合

		SearchLightVertices(new_light_vertices);	// 新しい光の頂点を計算する

		SortByAngle(new_light_vertices);			// 最後にソートする
	}

	// レイを撃つ時にdirectionをどれだけずらすか
	static const float SHIFT_DEGREE = 0.00003f;
	// レイの長さがこの値以上の割合なら遮られずに到達したとみなす。
	static const float VALID_RAY_LENGTH_RATE = 0.99f;
	// 光源の点を除いた光の頂点の最小値
	static const int LIGHT_VERTEX_MIN = 72;
	//==========================================================
	// 概要  :新しい光の頂点を計算する。
	// 引数  :光の頂点の入れ物となるコンテナ
	//==========================================================
	void Light::SearchLightVertices(vector<Vector2> &new_light_vertices)
	{
		// まずは光源となる点を追加する
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

		// 候補点を集める
		vector<Vector2> candidate_points = CornerCandidates::GetCandidatePoints(
			physics::PhysicsWorld::instance_->colliders_, transform_->position_,
			radius_);

		// ライトの光の方向と角度から有効なレイの角度を求める
		float valid_angle_min = Angle(Vector2::right(), direction_) - (angle_ / 2.0f);
		float valid_angle_max = Angle(Vector2::right(), direction_) + (angle_ / 2.0f);

		Vector2 ray_direction_base;		// レイの方向
		float ray_angle;				// レイの角度

		// 光の当たっている点を追加していく
		for (int i = 0;i < candidate_points.size();++i)
		{
			ray_direction_base = candidate_points[i] - transform_->position_;

			ray_angle = Angle(ray_direction_base);

			// レイの角度が有効でなければSkip
			if (ray_angle < valid_angle_min || ray_angle > valid_angle_max)
				continue;

			// レイを±少しずらして２つ撃つ
			// １つ目
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

			// 2つ目
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
	// 概要  :TriangleFanで上手く描画できるようにするために角度でソートします
	// 引数  :ソートさせたいコンテナ
	//==========================================================
	void Light::SortByAngle(const vector<Vector2> &points)
	{
		// ソート用バッファをクリア
		sort_buffer_.clear();

		Vector2 light_center = transform_->position_;	// ライトの光源の位置

		sort_buffer_.push_back(SortTemp(0, FLT_MAX));

		// 光源から光の頂点までのベクトルがなす角度とインデックスを全ての頂点において追加
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
		// クイックソートを行う
		//QuickSort(1, sort_buffer_.size() - 1);

		// マージソートを行う
		//MergeSort(sort_buffer_);

		// バブルソートを行う。
		BubbleSort();

#ifdef _DEBUG
		debug::Debug::StopWatchFinish(2);
#endif

		sort_buffer_.push_back(sort_buffer_[1]);
		vertex_count_ = sort_buffer_.size();

		// 前回の頂点が残っていたら削除する。
		if (light_vertices_ != nullptr)
		{
			delete[] light_vertices_;
		}

		// 光の頂点分の配列を用意する
		light_vertices_ = new Vertex2D[vertex_count_];

		if (light_world_vertices_ != nullptr)
		{
			delete[] light_world_vertices_;
		}
		light_world_vertices_ = new Vector2[vertex_count_];

		// ソート通りに頂点を格納していく
		for (int i = 0;i < vertex_count_ - 1;++i)
		{
			light_world_vertices_[i] = points[sort_buffer_[i].index_] * PIXEL_PER_UNIT;
		}

		light_world_vertices_[vertex_count_ - 1] = points[sort_buffer_[1].index_] * PIXEL_PER_UNIT;
	}

	//==========================================================
	// 概要  :クイックソートを行います。
	// 引数  :
	//	first      :最初のインデックス
	//	last       :最後のインデックス
	//==========================================================
	void Light::QuickSort(int first, int last)
	{
		// サイズが3以上
		if (last - first > 1)
		{
			int less = first, greater = last;

			// 軸要素の設定
			int pivot_index = DecisionPivot(less, last);

			if (pivot_index == -1)return;	// 全て同値

			const float pivot_angle = (sort_buffer_[first].angle_ + sort_buffer_[pivot_index].angle_) / 2.0f;

			// 判定軸が交差するまで、軸要素以上と以下の要素を入れ替える。
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

			// 前半・後半それぞれのブロックの要素が２つ以上なら再帰
			if (less >= first + 2)   QuickSort(first, less - 1);
			if (greater <= last - 2) QuickSort(greater + 1, last);
		}
		else
		{
			// サイズが２なのでただ比較してソートして終了
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
	// 概要  :軸要素を決定します。
	// 引数  :
	//	first      :最初のインデックス
	//	last       :最後のインデックス
	// 戻り値:軸要素のインデックス(-1ならすべて同値)
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
	// 概要  :最初と最後、そしてその間のインデックスが指す値の中央値を返します
	// 引数  :
	//	first      :最初のインデックス
	//	last       :最後のインデックス
	// 戻り値:中央値のインデックス
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
	// 概要  :マージソートを行います。
	// 引数  :
	//	first      :最初のインデックス
	//	last       :最後のインデックス
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
	// 概要  :マージします。
	// 引数  :
	//	first      :最初のインデックス
	//	last       :最後のインデックス
	//==========================================================
	void Light::Merge(std::vector<SortTemp> early, std::vector<SortTemp> late, std::vector<SortTemp> a)
	{
		int e = 0, l = 0;

		// 両方の配列に要素が残っている
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
	// 概要  :バブルソートを行います。
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
