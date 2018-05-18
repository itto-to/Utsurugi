//==========================================================
// �T�v  :�e�N�X�`���N���X
// Author:Itsuki Namito
// Copyright(c) Utsurugi.All right reserved.
//==========================================================
#include "../../Game/Application/application.h"
#include "texture.h"

namespace shadowpartner
{
//**********************************************************
// �}�N��
//**********************************************************

	//**********************************************************
	// �萔
	//**********************************************************

	// �R���X�g���N�^
	Texture::Texture()
		:tex_(nullptr)
	{

	}

	Texture::Texture(const char *file_name)
	{
		D3DXCreateTextureFromFile(Application::Instance()->device, (LPCSTR)file_name, &tex_);
	}

	Texture::~Texture()
	{

	}

	void Texture::Load(const char *file_name)
	{
		D3DXCreateTextureFromFile(Application::Instance()->device, (LPCSTR)file_name, &tex_);
	}

}
