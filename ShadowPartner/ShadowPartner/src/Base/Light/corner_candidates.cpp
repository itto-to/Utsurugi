//==========================================================
// �T�v  :���̌��_�̏W��
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
// �}�N��
//**********************************************************

	//**********************************************************
	// �萔
	//**********************************************************

	// Static�����o
	CornerCandidates *CornerCandidates::instance_ = nullptr;

	// �R���X�g���N�^
	void CornerCandidates::Init()
	{
		if (instance_ == nullptr)
		{
			instance_ = new CornerCandidates();
		}
	}

	// �f�X�g���N�^
	void CornerCandidates::Uninit()
	{
		if (instance_ != nullptr)
		{
			delete instance_;
			instance_ = nullptr;
		}
	}

	//==========================================================
	// �T�v  :�^����ꂽ�^�C���������Ɍ��_�����O�v�Z���܂��B
	// ����  :�^�C���X�e�[�W�̃R���e�i
	//==========================================================
	void CornerCandidates::PreCalculate(vector<Stage *> stages)
	{

	}

	//==========================================================
	// �T�v  :�^����ꂽ�R���C�_�[�����Ɍ��_�����O�v�Z���܂��B
	// ����  :�R���C�_�[�̃R���e�i
	//==========================================================
	void CornerCandidates::PreCalculate(vector<Collider *> colliders)
	{

	}

	//==========================================================
	// �T�v  :���O�v�Z�������_���N���A
	//==========================================================
	void CornerCandidates::Clear()
	{
		instance_->static_points_.clear();
	}

	//==========================================================
	// �T�v  :
}
