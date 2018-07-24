//==========================================================
// 概要  :タイルマップの当たり判定
// Author:Itsuki Namito
// Copyright(c) Utsurugi.All right reserved.
//==========================================================

#ifndef _BASE_PHYSICS_ELEMENT_TILEMAP_COLLIDER_H_
#define _BASE_PHYSICS_ELEMENT_TILEMAP_COLLIDER_H_

//**********************************************************
// インクルードファイル
//**********************************************************
#include "collider.h"

using namespace shadowpartner;

namespace physics
{
	struct ContourTrackingTemp;

	//==========================================================
	// 概要  :タイルマップの初期化情報
	// 注意  :collision_existはnewで確保したものを渡してください。内部でdeleteするので、
	//       :newだけしたらdeleteは意識する必要はありません。
	//==========================================================
	struct TileMapInitializer
	{
		Vector2 pos_;			// タイルマップの中心位置
		int x_lenght_;			// X方向のタイルの数
		int y_lenght_;			// Y方向のタイルの数
		float width_;			// 横幅
		float height_;			// 縦幅
		bool *collision_exist;	// collision_exist[y * x_length_ + x]にコリジョンが存在する？
		float density_;			// 密度
		float friction_;		// 摩擦係数
		float bounciness_;		// 反発係数

		TileMapInitializer()
			:pos_(Vector2::zero())
			,x_lenght_(0)
			,y_lenght_(0)
			, width_(1.0f)
			, height_(1.0f)
			, density_(1.0f)
			, friction_(0.6f)
			, bounciness_(0.0f)
		{
		}
	};

	//==========================================================
	// 概要  :全コライダーの基底クラス
	//==========================================================
	class TileMapCollider : public Collider
	{
	public:
		TileMapCollider(const TileMapInitializer &initializer);
		virtual ~TileMapCollider() {};

		// ariables
		// methods
		Vector2 GetSize();
	protected:

		// methods
		void Start();

		virtual void OnCollisionEnter(Collider *hit) {};
		virtual void OnCollisionStay(Collider *hit) {};
		virtual void OnCollisionExit(Collider *hit) {};
		virtual void OnTriggerEnter(Collider *hit) {};
		virtual void OnTriggerStay(Collider *hit) {};
		virtual void OnTriggerExit(Collider *hit) {};

	private:
		// variables
		Vector2 size_;

		// methods
		int RasterScan(int start, ContourTrackingTemp *ctt, int tile_max);
		void CreatePolygonOutLineCollider(int start,std::vector<int> chain_list,bool is_outer,int x_length,int y_length);
		void FillArea(int fill_index);	// 与えられたタイルとつながっているタイルをチェック済みに塗りつぶします
		void ContourTracking(int start, ContourTrackingTemp *ctt, int x_length, int y_length, bool is_outer = true);
	};
}

#endif