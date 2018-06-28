//==========================================================
// �T�v  :�����̃e�X�g�V�[��
// Author:Itsuki Namito
// Copyright(c) Utsurugi.All right reserved.
//==========================================================

#ifndef _TEST_SCENE_PHYSICS_TEST_SCENE_H_
#define _TEST_SCENE_PHYSICS_TEST_SCENE_H_

//**********************************************************
// �C���N���[�h�t�@�C��
//**********************************************************
#include "../../Base/System/scene.h"

namespace shadowpartner
{
	//==========================================================
	// �T�v  :�`��̃e�X�g�p�V�[��
	//==========================================================
	class PhysicsTestScene:public Scene
	{
	public:
		PhysicsTestScene();
		virtual ~PhysicsTestScene();
		
		// variables

		// methods

	protected:

		// methods
		HRESULT Init();
		void Update();
		void Uninit();

	private:
		// variables
		GameObject *camera_object;
		GameObject *static_box;
		GameObject *dynamic_box;
		GameObject *static_circle;
		GameObject *dynamic_circle;

		GameObject *hinge_joint;

		GameObject *pyramids_[15];

		GameObject *chain_object;

		// methods



		// ���p�֎~
	};
}

#endif