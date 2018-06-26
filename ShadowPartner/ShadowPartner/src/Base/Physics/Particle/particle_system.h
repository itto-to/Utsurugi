////==========================================================
//// 概要  :パーティクルシステム（物理シミュレーションあり）
//// Author:Itsuki Namito
//// Copyright(c) Utsurugi.All right reserved.
////==========================================================
//
//#ifndef _BASE_PHYSICS_PARTICLE_PARTICLE_SYSTEM_H_
//#define _BASE_PHYSICS_PARTICLE_PARTICLE_SYSTEM_H_
//
////**********************************************************
//// インクルードファイル
////**********************************************************
//#include "collider.h"
//
//using namespace shadowpartner;
//
//namespace physics
//{
//	struct ParticleInitializer
//	{
//		float density_;
//		float gravity_scale_;
//		float radius_;
//		
//		//Vector2 pos_;			// 位置
//		//Vector2 offset_;
//		//float width_;			// 横幅
//		//float height_;			// 縦幅
//		//BodyType body_type_;	// ボディーのタイプ
//		//bool is_trigger_;		// トリガーかどうか
//		//bool fixed_rotation_;	// trueで回転を許可しない
//		//float density_;			// 密度
//		//float friction_;		// 摩擦係数
//		//float bounciness_;		// 反発係数
//
//		ParticleInitializer()
//			:density_(1.0f)
//			, gravity_scale_(1.0f)
//			, radius_(1.0f)
//		//	:pos_(Vector2::zero())
//		//	, offset_(Vector2::zero())
//		//	, width_(1.0f)
//		//	, height_(1.0f)
//		//	, body_type_(kDynamicBody)
//		//	, is_trigger_(false)
//		//	, fixed_rotation_(true)
//		//	, density_(1.0f)
//		//	, friction_(0.6f)
//		//	, bounciness_(0.0f)
//		{
//		}
//	};
//
//	//==========================================================
//	// 概要  :全コライダーの基底クラス
//	//==========================================================
//	class ParticleSystem : public Collider
//	{
//	public:
//		ParticleSystem(const ParticleInitializer &initializer);
//		virtual ~ParticleSystem() {};
//
//		// ariables
//		// methods
//		Vector2 GetSize();
//
//		void ReSet(const ParticleInitializer &initializer);
//
//		void SetOffset(const Vector2 &offset);
//
//	protected:
//
//		// methods
//		void Start();
//
//	private:
//		// variables
//		b2ParticleSystem *particle_system_;
//
//		// methods
//	};
//}
//
//#endif