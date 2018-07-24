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
		,width_(10.0f)
		,height_(10.0f)
		,order_in_layer_(0)
	{
		if (tex_ != nullptr)
		{
			tex_->Release();
			tex_ = nullptr;
		}
	}

	Texture::Texture(const char *file_name)
		:tex_(nullptr)
		,width_(10.0f)
		,height_(10.0f)
		,order_in_layer_(0)
	{
		if (FAILED(D3DXCreateTextureFromFile(Application::Instance()->device, (LPCSTR)file_name, &tex_)))
		{
			MessageBox(NULL, "�e�N�X�`���[�̓ǂݍ��݂Ɏ��s���܂����B", "�x���I", MB_ICONWARNING);
		}
	}

	Texture::~Texture()
	{
		if (tex_ != nullptr)
		{
			tex_->Release();
			tex_ = nullptr;
		}
	}

	// �摜�ǂݍ���
	void Texture::Load(const char *file_name)
	{
		if (FAILED(D3DXCreateTextureFromFile(Application::Instance()->device, (LPCSTR)file_name, &tex_)))
		{
			MessageBox(NULL, "�e�N�X�`���[�̓ǂݍ��݂Ɏ��s���܂����B", "�x���I", MB_ICONWARNING);
		}
	}

	//==========================================================
	// �T�v  :TriangleStrip�ŕ`�悵�܂��B
	// ����  :���_�z��̐擪�|�C���^
	//==========================================================
	void Texture::DrawTriangleStrip(const Vertex2D *vertices)
	{
		LPDIRECT3DDEVICE9 device = Application::Instance()->device;

		// �X�e���V���o�b�t�@�g��
		//device->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
		//device->SetRenderState(D3DRS_STENCILENABLE, TRUE);
		//device->SetRenderState(D3DRS_STENCILMASK, 0xff);				// �X�e���V���}�X�N�̐ݒ�B�f�[�^�͂��̂܂܎g���B
		//device->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_GREATEREQUAL);	// ���݂̃X�e���V���l�ȏ�Ȃ獇�i
		//device->SetRenderState(D3DRS_COLORWRITEENABLE, 0x00);			// �o�b�N�o�b�t�@��RGB�l���������܂Ȃ�

		//device->SetRenderState(D3DRS_STENCILFAIL, D3DSTENCILCAPS_REPLACE);
		//device->SetRenderState(D3DRS_STENCILZFAIL, D3DSTENCILCAPS_REPLACE);

		//device->SetRenderState(D3DRS_STENCILPASS,D3DSTENCILCAPS_REPLACE);	// �e�X�g�ɍ��i�����珑��������

		//device->SetRenderState(D3DRS_STENCILREF, order_in_layer_);		// �X�e���V���o�b�t�@�̒l�Ɣ�r����Q�ƒl
		//device->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_LESSEQUAL);	// ��r�֐��@�������^�̂Ƃ��X�e���V���e�X�g���i
		//device->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILOP_KEEP);	// �X�e���V���e�X�g�ɍ��i�����ꍇ�X�e���V���l�ɂ͉������Ȃ�

		//device->SetRenderState(D3DRS_COLORWRITEENABLE,
		//	D3DCOLORWRITEENABLE_RED |
		//	D3DCOLORWRITEENABLE_GREEN |
		//	D3DCOLORWRITEENABLE_BLUE |
		//	D3DCOLORWRITEENABLE_ALPHA);


		//device->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
		// �X�e���V���o�b�t�@�����܂�

		// �`�揈��
		device->SetTexture(0, tex_);
		device->SetFVF(FVF_VERTEX_2D);
		device->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, vertices, sizeof(Vertex2D));

		//device->SetRenderState(D3DRS_STENCILENABLE, FALSE);
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

	void Texture::SetOrderInLayer(const int &layer)
	{
		order_in_layer_ = layer;
	}
}
