//==========================================================
// �T�v  :�X�e�[�W�V�[���̊��N���X
// Author:Itsuki Namito
// Copyright(c) Utsurugi.All right reserved.
//==========================================================
#include "stage_scene.h"
#include "../../Base/2D/camera.h"
#include "../../Base/2D/sprite.h"
#include "../../Base/Light/light.h"
#include "../../Base/Input/input.h"
#include "../../Base/System/scene_manager.h"

#ifdef _DEBUG
#include "../../Base/Debug/debugger.h"
#endif

#include "../../Base/Physics/physics.h"
#include "../../Base/Time/time.h"

namespace shadowpartner
{
	// �R���X�g���N�^
	StageScene::StageScene(int phase_num)
		:phase_num_(phase_num)
	{

	}

	// �f�X�g���N�^
	StageScene::~StageScene()
	{

	}

	// ����������
	HRESULT StageScene::Init()
	{
#ifdef _DEBUG
		debug::Debug::Log("�V�[���̐؂�ւ��F�����e�X�g");
#endif
		// �J�����I�u�W�F�N�g�𐶐�
		{
			camera_object_ = new GameObject();
			camera_object_->transform_->position_ = Vector2(0.0f, 0.0f);
			Camera *camera = new Camera();
			camera_object_->AddComponent(camera);

			AddGameObject(camera_object_);
		}

		// ���̌��𐶐�
		{
			moon_light_ = new GameObject();
			moon_light_->transform_->position_ = Vector2(0.0f, 0.0f);

			LightInitializer light_init;
			light_init.radius_ = 200.0f;
			light_init.color_ = D3DCOLOR_RGBA(0xff, 0xff, 0xff, 0x30);
			Light *light = new Light(light_init);
			moon_light_->AddComponent(light);

			AddGameObject(moon_light_);
		}

		current_phase_ = 0;

		return S_OK;
	}

	static int light_radius_scale = 0;

	void StageScene::Update()
	{
	}

	void StageScene::Uninit()
	{

	}

	void StageScene::NextPhase()
	{
		if (current_phase_ < phase_num_)
		{
			++current_phase_;

			CameraAdjustToCurrentPhase();
		}
	}

	void StageScene::PrevPhase()
	{
		if (current_phase_ > 0)
		{
			--current_phase_;

			CameraAdjustToCurrentPhase();
		}
	}

	void StageScene::CameraAdjustToCurrentPhase()
	{
		Camera::main_->SetPosition(Vector2(current_phase_ * 1120.0f, 0.0f));
	}
}