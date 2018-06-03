//==========================================================
// 概要  :光の候補点の集合
// Author:Itsuki Namito
// Copyright(c) Utsurugi.All right reserved.
//==========================================================

#ifndef _BASE_LIGHT_CORNER_CANDIDATES_H_
#define _BASE_LIGHT_CORNER_CANDIDATES_H_

//**********************************************************
// インクルードファイル
//**********************************************************
#include "../Physics/physics.h"
#include "../../Game/Stage/stage.h"
#include <vector>

//==========================================================
// マクロ
//==========================================================

namespace shadowpartner
{
	//==========================================================
	// 光の候補点の集合
	//==========================================================
	class CornerCandidates
	{
	public:
		// methods
		static void Init();
		static void Uninit();

		static void PreCalculate(std::vector<Stage *> stages);
		static void PreCalculate(std::vector<physics::Collider *> colliders);
		static void Clear();

		// 与えられたコライダーから光の候補点を集合を計算して返す
		static std::vector<math::Vector2> GetCandidatePoints
			(
				std::vector<physics::Collider *> colliders,
				const math::Vector2 &center, 
				const float &distance = FLT_MAX
				);
	private:
		// variables
		static CornerCandidates *instance_;
		static std::vector<math::Vector2> static_points_;

		static std::vector<math::Vector2> GetCandidatesFromBox(physics::Collider *collider,const math::Vector2 &light_center,const float &distance);
		static std::vector<math::Vector2> GetCandidatesFromCircle(physics::Collider *collider, const math::Vector2 &light_center, const float &distance);
	};
}

#endif