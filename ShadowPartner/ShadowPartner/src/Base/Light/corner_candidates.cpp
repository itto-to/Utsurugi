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

	}

	//==========================================================
	// 概要  :事前計算した頂点をクリア
	//==========================================================
	void CornerCandidates::Clear()
	{
		instance_->static_points_.clear();
	}

	//==========================================================
	// 概要  :
}
