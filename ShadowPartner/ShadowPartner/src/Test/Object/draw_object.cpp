//==========================================================
// �T�v  :�`��̃e�X�g�p�I�u�W�F�N�g
// Author:Itsuki Namito
// Copyright(c) Utsurugi.All right reserved.
//==========================================================
#include "draw_object.h"

#define TEST_TEXTURE_NAME "Resources/Texture/Fox1.png"

namespace shadowpartner
{
	// �R���X�g���N�^
	DrawObject::DrawObject()
	{

	}

	// �f�X�g���N�^
	DrawObject::~DrawObject()
	{

	}

	// �I������
	void DrawObject::Uninit()
	{

	}

	// 
	void DrawObject::Awake()
	{
		gameObject_->AddComponent(new Sprite(TEST_TEXTURE_NAME));
	}

	// �X�V����
	void DrawObject::Update()
	{

	}

	// �`�揈��
	void DrawObject::Draw()
	{

	}

}
