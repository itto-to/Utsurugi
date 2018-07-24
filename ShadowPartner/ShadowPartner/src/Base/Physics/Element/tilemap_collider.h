//==========================================================
// �T�v  :�^�C���}�b�v�̓����蔻��
// Author:Itsuki Namito
// Copyright(c) Utsurugi.All right reserved.
//==========================================================

#ifndef _BASE_PHYSICS_ELEMENT_TILEMAP_COLLIDER_H_
#define _BASE_PHYSICS_ELEMENT_TILEMAP_COLLIDER_H_

//**********************************************************
// �C���N���[�h�t�@�C��
//**********************************************************
#include "collider.h"

using namespace shadowpartner;

namespace physics
{
	struct ContourTrackingTemp;

	//==========================================================
	// �T�v  :�^�C���}�b�v�̏��������
	// ����  :collision_exist��new�Ŋm�ۂ������̂�n���Ă��������B������delete����̂ŁA
	//       :new����������delete�͈ӎ�����K�v�͂���܂���B
	//==========================================================
	struct TileMapInitializer
	{
		Vector2 pos_;			// �^�C���}�b�v�̒��S�ʒu
		int x_lenght_;			// X�����̃^�C���̐�
		int y_lenght_;			// Y�����̃^�C���̐�
		float width_;			// ����
		float height_;			// �c��
		bool *collision_exist;	// collision_exist[y * x_length_ + x]�ɃR���W���������݂���H
		float density_;			// ���x
		float friction_;		// ���C�W��
		float bounciness_;		// �����W��

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
	// �T�v  :�S�R���C�_�[�̊��N���X
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
		void FillArea(int fill_index);	// �^����ꂽ�^�C���ƂȂ����Ă���^�C�����`�F�b�N�ς݂ɓh��Ԃ��܂�
		void ContourTracking(int start, ContourTrackingTemp *ctt, int x_length, int y_length, bool is_outer = true);
	};
}

#endif