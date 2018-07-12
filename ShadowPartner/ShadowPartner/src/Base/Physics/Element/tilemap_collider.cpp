//==========================================================
// 概要  :矩形の当たり判定
// Author:Itsuki Namito
// Copyright(c) Utsurugi.All right reserved.
//==========================================================
#include "tilemap_collider.h"
#include "../World/physics_world.h"

namespace physics
{
	//**********************************************************
	// マクロ
	//**********************************************************

	//**********************************************************
	// 輪郭追跡用構造体
	//**********************************************************
	struct ContourTrackingTemp
	{
		bool isChecked;		// 走査済み
		bool isCollider;	// コライダーがある？
		int label;			// 領域のラベル。-1は背景

		ContourTrackingTemp()
			:isChecked(false)
			,isCollider(false)
			,label(-1)
		{}
	};


	// コンストラクタ
	TileMapCollider::TileMapCollider(const TileMapInitializer &ini)
	{
		shape_ = PhysicsShape::kBox;

		// タイルマップコライダーのbody
		b2BodyDef tilemap_body_def;

		tilemap_body_def.type = b2_staticBody;

		tilemap_body_def.position.Set(ini.pos_.x, ini.pos_.y);

		body_ = PhysicsWorld::CreateBody(this, &tilemap_body_def);
		body_->SetUserData((void *)this);

		//int current = 0;

		//// 輪郭追跡用のデータ配列の生成
		//ContourTrackingTemp *ctt = new ContourTrackingTemp[ini.x_lenght_ * ini.y_lenght_];

		//for (int y = 0;y < ini.y_lenght_;++y)
		//{
		//	for (int x = 0;x < ini.x_lenght_;++x)
		//	{
		//		ctt[y * ini.x_lenght_ + x].isCollider = ini.collision_exist[y * ini.x_lenght_ + x];
		//	}
		//}

		//int start;	// 輪郭追跡のスタート地点
		//while (start = RasterScan(current, ctt, ini.x_lenght_ * ini.y_lenght_))
		//{
		//	ContourTracking(start, ctt, ini.x_lenght_, ini.y_lenght_);

		//	current = start + 1;
		//}

		//delete[] ctt;

		Vector2 offset = Vector2(- ini.width_ * ((float)ini.x_lenght_ / 2.0f - 0.5f),ini.height_ * ((float)ini.y_lenght_ / 2.0f -0.5f));

		for (int y = 0;y < ini.y_lenght_;++y,offset.y -= ini.height_)
		{
			// オフセットのX座標の位置を左はじに戻す
			offset.x = - ini.width_ * ((float)ini.x_lenght_ / 2.0f - 0.5f);

			for (int x = 0;x < ini.x_lenght_;++x,offset.x += ini.width_)
			{
				if (ini.collision_exist[y * ini.x_lenght_ + x])
				{
					b2PolygonShape box;
					b2FixtureDef tilemap_fixture_def;

					box.SetAsBox(ini.width_ / 2.0f, ini.height_ / 2.0f, b2Vec2(offset.x, offset.y), 0.0f);

					tilemap_fixture_def.shape = &box;

					tilemap_fixture_def.density = ini.density_;
					tilemap_fixture_def.friction = ini.friction_;

					body_->CreateFixture(&tilemap_fixture_def);
				}
			}
		}
		size_ = Vector2(ini.width_, ini.height_);
	}

	void TileMapCollider::Start()
	{

	}

	//==========================================================
	// 概要  :TileMapColliderの縦横の大きさを記録したsize_を返します。
	// 戻り値:縦横の大きさ
	//==========================================================
	Vector2 TileMapCollider::GetSize()
	{
		return size_;
	}

	//==========================================================
	// 概要  :ラスタースキャンでコライダーを持ったタイルを探します
	// 戻り値:見つけたタイルのインデックス
	// 引数  :
	//  start   :
	//  ctt     :
	//  tile_max:
	//==========================================================
	int TileMapCollider::RasterScan(int start, ContourTrackingTemp *ctt, int tile_max)
	{
		int current = start;

		while (current < tile_max)
		{
			if (!ctt[current].isChecked && ctt[current].isCollider)
			{
				// まだコライダーを作っていないタイルを探す
				return current;
			}

			ctt[current].isChecked = true;

			++current;
		}
	}


}
