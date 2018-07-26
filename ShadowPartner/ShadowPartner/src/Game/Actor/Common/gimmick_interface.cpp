//==========================================================
// �T�v  :�M�~�b�N�쓮�p�C���^�[�t�F�[�X
// Author:Ittoto
// Copyright(c) Utsurugi.All right reserved.
//==========================================================
#include "gimmick_interface.h"

using namespace physics;

namespace shadowpartner
{

	const BoxInitializer DEFAULT_BOX_INIT =
		BoxInitializer(Vector2::zero(),Vector2::zero(),1.0f,1.0f,kStaticBody,
			true,true,1.0f,0.6f,0.0f,CollisionFilter::kGimmickTrigger,
			CollisionFilter::kPlayer,1.0f);

	//==========================================================
	// �T�v  :�]����Z�L�[�������ꂽ�ꍇ�ɔ�������M�~�b�N�p��
	//       :�f�t�H���g�R���X�g���N�^
	//==========================================================
	GimmickInterface::GimmickInterface()
		:BoxCollider(DEFAULT_BOX_INIT)
		,is_activated_(false)
		,is_touching_(false)
	{

	}

	//==========================================================
	// �T�v  :
	// ����  :
	//==========================================================
	GimmickInterface::GimmickInterface(const BoxInitializer &ini)
		:BoxCollider(ini)
		,is_activated_(false)
		,is_touching_(false)
		
	{

	}

	bool GimmickInterface::IsTouching()
	{
		return is_touching_;
	}

	void GimmickInterface::OnTriggerEnter(Collider *col)
	{
		is_touching_ = true;
		EnterAction();
	}

	void GimmickInterface::OnTriggerExit(Collider *col)
	{
		is_touching_ = false;
		ExitAction();
	}

}