//==========================================================
// �T�v  :�v���C���[�̃e�X�g�V�[��
// Author:Ittoto
// Copyright(c) Utsurugi.All right reserved.
//==========================================================

#ifndef _TEST_SCENE_PLAYERTESTSCENE_H_
#define _TEST_SCENE_PLAYERTESTSCENE_H_

//**********************************************************
// �C���N���[�h�t�@�C��
//**********************************************************
#include "../../Base/System/scene.h"

namespace shadowpartner
{
	namespace {
		const int kMaxPlatform = 56;
	}

	//==========================================================
	// �T�v  :�v���C���[�̃e�X�g�p�V�[��
	//==========================================================
	class PlayerTestScene : public Scene
	{
	public:
		PlayerTestScene();
		virtual ~PlayerTestScene();

	protected:

		// methods
		HRESULT Init();
		void Uninit();
		void Update();

	private:

		// variables
		GameObject *player_;
		GameObject *shadow_;
		GameObject *camera_object_;
		GameObject *platform_[kMaxPlatform];
		GameObject *large_light_;
		GameObject *middle_light_;
		GameObject *small_light_;
	};

}	// namespace shadowpartner


#endif