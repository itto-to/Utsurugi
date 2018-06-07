//==========================================================
// �T�v  :���C�g�N���X
// Author:Itsuki Namito
// Copyright(c) Utsurugi.All right reserved.
//==========================================================

#ifndef _BASE_LIGHT_LIGHT_H_
#define _BASE_LIGHT_LIGHT_H_

//**********************************************************
// �C���N���[�h�t�@�C��
//**********************************************************
#include "../2D/texture.h"
#include "../Element/component.h"

//==========================================================
// �}�N��
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
	// 2D�I�u�W�F�N�g�̕`��p�N���X
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
		math::Vector2 direction_;	// ���̌���
		float angle_;		// ���̌ʂ̍L��(�x���@)
		float radius_;		// ���̓͂�����

		D3DCOLOR light_color_;	// ���̐F

		Transform *player_tran_;

		// �v���C���[�֌W
		void IlluminateCheck();
		void SetPlayer(Transform *player_tran);

		// �������֌W
		void ReMesh();		// ���̌`���Čv�Z����
		void SearchLightVertices(std::vector<math::Vector2> &new_light_vertices);	// ����

		void SetVertex(const Vector3 &center);

		// �\�[�g�֌W
		struct SortTemp
		{
			int index_;
			float angle_;

			SortTemp(int index, float angle)
				:index_(index),angle_(angle)
			{}
		};
		std::vector<SortTemp> sort_buffer_;	// �\�[�g���ꂽ���_�C���f�b�N�X
		void SortByAngle(const std::vector<math::Vector2> &points);	// �_�̏W����x���������Ƃ̂Ȃ��p�x�Ń\�[�g����
		void QuickSort(int first,int last);
		int DecisionPivot(int first, int last);
		int MedianIndex(int first, int last);

		// QuickSort���Ƌɂ߂ċ߂��l�����̔z��̏ꍇ���v�f�̌��肪��肭�������A�������[�v�ɓ��邱�Ƃ�����̂ŁA���̕��@�Ń\�[�g������B
		void MergeSort(std::vector<SortTemp> &a);
		void Merge(std::vector<SortTemp> &early, std::vector<SortTemp> &late, std::vector<SortTemp> &a);

		void BubbleSort();
	};
}

#endif