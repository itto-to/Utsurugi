//==========================================================
// 概要  :ライトの当たり判定
// Author:Ittoto
// Copyright(c) Utsurugi.All right reserved.
//==========================================================

#ifndef _BASE_PHYSICS_ELEMENT_LIGHTCOLLIDER_H_
#define _BASE_PHYSICS_ELEMENT_LIGHTCOLLIDER_H_

//**********************************************************
// インクルードファイル
//**********************************************************
#include "collider.h"

namespace shadowpartner
{
	class Light;
}

namespace physics
{
	class LightCollider : public Collider
	{
	public:
		LightCollider();
		virtual ~LightCollider();

		// methods
		void Start() override;
		void Update() override;

		//void SetTransform(const Vector2 &pos, const float &ori) override;
		//Vector2 GetPosition() override;
		//float GetAngle() override;


	protected:
		int num_triangle_;
		int body_idx_;
		shadowpartner::Light *light_;

		void DestroyLightCollider();

	};
}

#endif