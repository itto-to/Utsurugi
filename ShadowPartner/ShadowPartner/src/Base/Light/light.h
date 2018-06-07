//==========================================================
// 概要  :ライトクラス
// Author:Itsuki Namito
// Copyright(c) Utsurugi.All right reserved.
//==========================================================

#ifndef _BASE_LIGHT_LIGHT_H_
#define _BASE_LIGHT_LIGHT_H_

//**********************************************************
// インクルードファイル
//**********************************************************
#include "../2D/texture.h"
#include "../Element/component.h"

//==========================================================
// マクロ
//==========================================================

namespace shadowpartner
{
#define LIGHT_DEFAULT_COLOR D3DCOLOR_RGBA(0xff,0xff,0x99,0xff)

	//==========================================================
	struct LightInitializer
	{
		Vector2 direction_;
		float angle_;
		float radius_;
		D3DCOLOR color_;

		LightInitializer()
			:direction_(Vector2::down())
			, angle_(360.0f)
			, radius_(FLT_MAX)
			, color_(LIGHT_DEFAULT_COLOR)
		{
		}
	};

	//==========================================================
	// 2Dオブジェクトの描画用クラス
	//==========================================================
	class Light :public Component
	{
	public:
		Light(const LightInitializer initializer);
		~Light();

		//variables

		//methods
		void SetColor(const D3DCOLOR &color);
		void SetDirection(const math::Vector2 &direction);
		void SetAngle(const float &angle);
		void SetRadius(const float &radius);


	protected:
		void Update();
		void Draw();

	private:
		// variables
		Texture texture_;
		Vertex2D *light_vertices_;
		int vertex_count_;
		math::Vector2 direction_;	// 光の向き
		float angle_;		// 光の弧の広さ(度数法)
		float radius_;		// 光の届く長さ

		D3DCOLOR light_color_;	// 光の色

		Transform *player_tran_;

		// プレイヤー関係
		void IlluminateCheck();
		void SetPlayer(Transform *player_tran);

		// 光生成関係
		void ReMesh();		// 光の形を再計算する
		void SearchLightVertices(std::vector<math::Vector2> &new_light_vertices);	// 光の

		void SetVertex(const Vector3 &center);

		// ソート関係
		struct SortTemp
		{
			int index_;
			float angle_;

			SortTemp(int index, float angle)
				:index_(index),angle_(angle)
			{}
		};
		std::vector<SortTemp> sort_buffer_;	// ソートされた頂点インデックス
		void SortByAngle(const std::vector<math::Vector2> &points);	// 点の集合をx軸正方向とのなす角度でソートする
		void QuickSort(int first,int last);
		int DecisionPivot(int first, int last);
		int MedianIndex(int first, int last);

		// QuickSortだと極めて近い値だけの配列の場合軸要素の決定が上手くいかず、無限ループに入ることがあるので、他の方法でソートさせる。
		void MergeSort(std::vector<SortTemp> &a);
		void Merge(std::vector<SortTemp> &early, std::vector<SortTemp> &late, std::vector<SortTemp> &a);

		void BubbleSort();
	};
}

#endif