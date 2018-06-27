////==========================================================
//// �T�v  :�p�[�e�B�N���V�X�e���i�����V�~�����[�V��������j
//// Author:Itsuki Namito
//// Copyright(c) Utsurugi.All right reserved.
////==========================================================
//
//#ifndef _BASE_PHYSICS_PARTICLE_PARTICLE_SYSTEM_H_
//#define _BASE_PHYSICS_PARTICLE_PARTICLE_SYSTEM_H_
//
////**********************************************************
//// �C���N���[�h�t�@�C��
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
//		//Vector2 pos_;			// �ʒu
//		//Vector2 offset_;
//		//float width_;			// ����
//		//float height_;			// �c��
//		//BodyType body_type_;	// �{�f�B�[�̃^�C�v
//		//bool is_trigger_;		// �g���K�[���ǂ���
//		//bool fixed_rotation_;	// true�ŉ�]�������Ȃ�
//		//float density_;			// ���x
//		//float friction_;		// ���C�W��
//		//float bounciness_;		// �����W��
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
//	// �T�v  :�S�R���C�_�[�̊��N���X
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