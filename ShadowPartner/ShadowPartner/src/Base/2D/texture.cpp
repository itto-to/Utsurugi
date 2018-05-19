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

	// �摜�ǂݍ���
	void Texture::Load(const char *file_name)
	{
		D3DXCreateTextureFromFile(Application::Instance()->device, (LPCSTR)file_name, &tex_);
	}

	//==========================================================
	// �T�v  :TriangleStrip�ŕ`�悵�܂��B
	// ����  :���_�z��̐擪�|�C���^
	//==========================================================
	void Texture::DrawTriangleStrip(const Vertex2D *vertices)
	{
		LPDIRECT3DDEVICE9 device = Application::Instance()->device;

		device->SetTexture(0, tex_);
		device->SetFVF(FVF_VERTEX_2D);
		device->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, vertices, sizeof(Vertex2D));
	}

	//==========================================================
	// �T�v  :TriangleFan�ŕ`�悵�܂��B
	// ����  :���_�z��̐擪�|�C���^
	//==========================================================
	void Texture::DrawTriangleFan(const Vertex2D *vertices, UINT primitive_count)
	{
		LPDIRECT3DDEVICE9 device = Application::Instance()->device;

		device->SetTexture(0, tex_);
		device->SetFVF(FVF_VERTEX_2D);
		device->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, primitive_count, vertices, sizeof(Vertex2D));
	}

	//==========================================================
	// �T�v  :�e�N�X�`���[�̃T�C�Y���w�肵�܂��B
	// ����  :
	//	width :����
	//	height:�c��
	//==========================================================
	void Texture::SetSize(float width, float height)
	{
		width_ = width;
		height_ = height;
	}

	//==========================================================
	// �T�v  :�e�N�X�`���[�̉������w�肵�܂��B
	// ����  :����
	//==========================================================
	void Texture::SetWidth(float width)
	{
		width_ = width;
	}

	//==========================================================
	// �T�v  :�e�N�X�`���[�̉������擾���܂��B
	// �߂�l:����
	//==========================================================
	float Texture::GetWidth()
	{
		return width_;
	}

	//==========================================================
	// �T�v  :�e�N�X�`���[�̏c�����w�肵�܂��B
	// ����  :�c��
	//==========================================================
	void Texture::SetHeight(float height)
	{
		height_ = height;
	}

	//==========================================================
	// �T�v  :�e�N�X�`���[�̏c�����擾���܂��B
	// �߂�l:�c��
	//==========================================================
	float Texture::GetHeight()
	{
		return height_;
	}
}
