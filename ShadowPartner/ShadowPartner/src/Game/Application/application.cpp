//==========================================================
// �T�v  :�A�v���P�[�V����
// Author:Itsuki Namito
// Copyright(c) Utsurugi.All right reserved.
//==========================================================
#include "application.h"
#include "../../Base/System/scene_manager.h"

#include "../../Base/Time/time.h"

namespace shadowpartner
{

//**********************************************************
// �}�N��
//**********************************************************
#ifndef WINDOW_CLASSNAME
#define WINDOW_CLASSNAME "ShadowPartner"
#endif

	//**********************************************************
	// �萔
	//**********************************************************
	const int SCREEN_WIDTH = 1920;
	const int SCREEN_HEIGHT = 1080;

	const D3DCOLOR BACKGROUND_COLOR = D3DCOLOR_RGBA(255, 255, 255, 255);

	//**********************************************************
	// Static
	//**********************************************************
	Application *Application::instance_ = nullptr;

	Application *Application::Instance()
	{
		if (instance_ == nullptr)
		{
			instance_ = new Application();
		}

		return instance_;
	}

	// �R���X�g���N�^
	Application::Application()
		:h_instance_(nullptr)
		,h_wnd_(nullptr)
		,d3d(nullptr)
		,device(nullptr)
	{
	}

	// �f�X�g���N�^
	Application::~Application()
	{
		if (instance_ != nullptr)
		{
			delete instance_;
			instance_ = nullptr;
		}
	}

	//**********************************************************
	// ���\�b�h
	//**********************************************************

	//==========================================================
	// �T�v  :�A�v���P�[�V���������s����
	//==========================================================
	void Application::Run()
	{
		if (FAILED(InitWindow()))
		{
			return;
		}

		if (FAILED(InitDirect3D()))
		{
			return;
		}

		MainLoop();

		UninitDirect3D();
		UninitWindow();

		// �E�B���h�E�N���X�̓o�^������
		UnregisterClass(WINDOW_CLASSNAME, h_instance_);

		// �I������

		Uninit();

		timeEndPeriod(1);				// ����\��߂�
	}

	//==========================================================
	// �T�v  :�Q�[���̃��C�����[�v����
	//==========================================================
	int Application::MainLoop()
	{
		MSG msg;

		// ���b�Z�[�W���[�v
		while (1)
		{
			if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
			{
				if (msg.message == WM_QUIT)
				{	// PostQuitMessage()���Ă΂ꂽ�烋�[�v�I��
					break;
				}
				else
				{
					// ���b�Z�[�W�̖|��Ƒ��o
					TranslateMessage(&msg);
					DispatchMessage(&msg);
				}
			}
			else
			{
				Time::Instance()->Update();	// �^�C�}�[�����X�V

				if (Time::Instance()->CheckUpdate())
				{
					Update();
					Draw();
				}
			}
		}

		return (int)msg.wParam;
	}

	//==========================================================
	// �T�v  :���b�Z�[�W�v���V�[�W���B
	//==========================================================
	LRESULT CALLBACK Application::MsgProc(HWND h_wnd, UINT u_msg, WPARAM w_param, LPARAM l_param)
	{
		switch (u_msg)
		{
		case WM_DESTROY:
			PostQuitMessage(0);
			break;

		case WM_COMMAND:
		{

		}

		case WM_KEYDOWN:
		{
			switch (w_param)
			{
			case VK_ESCAPE:
			{
				DestroyWindow(h_wnd);	// �I��
			}
			break;

			case VK_F1:
			{
				// F1�L�[���������Ƃ��̓���
			}
			break;

			case VK_F2:
			{
				// F2�L�[���������Ƃ��̓���
			}
			break;

			default:
				break;
			}
		}
		break;

		default:
			break;
		}

		return DefWindowProc(h_wnd, u_msg, w_param, l_param);
	}

	//==========================================================
	// �T�v  :����������
	//==========================================================
	HRESULT Application::Init()
	{

		return S_OK;
	}

	//==========================================================
	// �T�v  : �E�B���h�E�̏��������s��
	// �߂�l: �������̌���
	// ����  : �E�B���h�E�̐ݒ�A�o�^�A�쐬�A�\�����s��
	//==========================================================
	HRESULT Application::InitWindow()
	{
		// �C���X�^���X�n���h�����擾.
		h_instance_ = GetModuleHandle(nullptr);
		if (!h_instance_)
		{
			return E_FAIL;
		}

		// �g���E�B���h�E�N���X�̐ݒ�.
		WNDCLASSEX wc =
		{
			sizeof(WNDCLASSEX),
			CS_CLASSDC,
			instance_->MsgProc,
			0,
			0,
			h_instance_,
			NULL,
			LoadCursor(NULL, IDC_ARROW),
			(HBRUSH)(COLOR_WINDOW + 1),
			NULL,
			WINDOW_CLASSNAME,
			NULL
		};

		// �E�B���h�E�N���X�̓o�^
		RegisterClassEx(&wc);

		// �E�B���h�E�̍쐬
		h_wnd_ = CreateWindowEx
			(
				0,
				WINDOW_CLASSNAME,
				"Shadow Partner",
				WS_OVERLAPPEDWINDOW,
				CW_USEDEFAULT,
				CW_USEDEFAULT,
				SCREEN_WIDTH + GetSystemMetrics(SM_CXDLGFRAME) * 2,
				SCREEN_HEIGHT + GetSystemMetrics(SM_CYDLGFRAME) * 2 + GetSystemMetrics(SM_CYCAPTION),
				NULL,
				NULL,
				h_instance_,
				NULL
				);

		if (!h_wnd_)
		{
			return E_FAIL;
		}

		// �E�B���h�E��\��
		ShowWindow(h_wnd_, SW_SHOWNORMAL);
		UpdateWindow(h_wnd_);

		// ����I��.
		return S_OK;
	}

	//==========================================================
	// �T�v  �F Direct3D�̏��������s��
	// �߂�l�F �������̌���
	// ����  �F Direct3D�I�u�W�F�N�g�ƃf�o�C�X�I�u�W�F�N�g�̍쐬�A�ݒ���s��
	//==========================================================
	HRESULT Application::InitDirect3D(void)
	{
		D3DPRESENT_PARAMETERS d3dpp;
		D3DDISPLAYMODE d3ddm;

		// Direct3D�I�u�W�F�N�g�̍쐬
		d3d = Direct3DCreate9(D3D_SDK_VERSION);
		if (d3d == NULL)
		{
			return E_FAIL;
		}

		// ���݂̃f�B�X�v���C���[�h���擾
		if (FAILED(d3d->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
		{
			return E_FAIL;
		}

		// �f�o�C�X�̃v���[���e�[�V�����p�����[�^�̐ݒ�
		ZeroMemory(&d3dpp, sizeof(d3dpp));			// ���[�N���[���N���A
		d3dpp.BackBufferCount = 1;					// �o�b�N�o�b�t�@�̐�
		d3dpp.BackBufferWidth = SCREEN_WIDTH;		// �Q�[����ʃT�C�Y(��)
		d3dpp.BackBufferHeight = SCREEN_HEIGHT;		// �Q�[����ʃT�C�Y(����)
		d3dpp.BackBufferFormat = d3ddm.Format;		// �o�b�N�o�b�t�@�t�H�[�}�b�g�̓f�B�X�v���C���[�h�ɍ��킹�Ďg��
		d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;	// �f���M���ɓ������ăt���b�v����
		d3dpp.Windowed = TRUE;						// �E�B���h�E���[�h
		d3dpp.EnableAutoDepthStencil = TRUE;		// �f�v�X�o�b�t�@�i�y�o�b�t�@�j�ƃX�e���V���o�b�t�@���쐬
		d3dpp.AutoDepthStencilFormat = D3DFMT_D16;	// �f�v�X�o�b�t�@�Ƃ���16bit���g��

		if (TRUE)
		{// �E�B���h�E���[�h
			d3dpp.FullScreen_RefreshRateInHz = 0;						// ���t���b�V�����[�g
			d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;	// �C���^�[�o��
		}
		else
		{// �t���X�N���[�����[�h
			d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;	// ���t���b�V�����[�g
			d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;	// �C���^�[�o��
		}

		// �f�o�C�X�I�u�W�F�N�g�̐���
		// [�f�o�C�X�쐬����]<�`��>��<���_����>���n�[�h�E�F�A�ōs�Ȃ�
		if (FAILED(d3d->CreateDevice(D3DADAPTER_DEFAULT,
			D3DDEVTYPE_HAL,
			h_wnd_,
			D3DCREATE_HARDWARE_VERTEXPROCESSING,
			&d3dpp, &device)))
		{
			// ��L�̐ݒ肪���s������
			// [�f�o�C�X�쐬����]<�`��>���n�[�h�E�F�A�ōs���A<���_����>��CPU�ōs�Ȃ�
			if (FAILED(d3d->CreateDevice(D3DADAPTER_DEFAULT,
				D3DDEVTYPE_HAL,
				h_wnd_,
				D3DCREATE_SOFTWARE_VERTEXPROCESSING,
				&d3dpp, &device)))
			{
				// ��L�̐ݒ肪���s������
				// [�f�o�C�X�쐬����]<�`��>��<���_����>��CPU�ōs�Ȃ�
				if (FAILED(d3d->CreateDevice(D3DADAPTER_DEFAULT,
					D3DDEVTYPE_REF,
					h_wnd_,
					D3DCREATE_SOFTWARE_VERTEXPROCESSING,
					&d3dpp, &device)))
				{
					// ���������s
					return E_FAIL;
				}
			}
		}

		// �����_�[�X�e�[�g�p�����[�^�̐ݒ�
		device->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);				// ���ʂ��J�����O
		device->SetRenderState(D3DRS_ZENABLE, TRUE);						// Z�o�b�t�@���g�p
		device->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);				// ���u�����h���s��
		device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);		// ���\�[�X�J���[�̎w��
		device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);	// ���f�X�e�B�l�[�V�����J���[�̎w��

		device->SetRenderState(D3DRS_LIGHTING, TRUE);					//���C�g�g��
		device->SetRenderState(D3DRS_AMBIENT, 0xff050505);				//�����̐ݒ�A��������D3DCOLOR

																		// �T���v���[�X�e�[�g�p�����[�^�̐ݒ�
		device->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);	// �e�N�X�`���A�h���b�V���O���@(U�l)��ݒ�
		device->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);	// �e�N�X�`���A�h���b�V���O���@(V�l)��ݒ�
		device->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);	// �e�N�X�`���k���t�B���^���[�h��ݒ�
		device->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);	// �e�N�X�`���g��t�B���^���[�h��ݒ�

																		// �e�N�X�`���X�e�[�W�X�e�[�g�̐ݒ�
		device->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);	// �A���t�@�u�����f�B���O������ݒ�
		device->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);	// �ŏ��̃A���t�@����
		device->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);	// �Q�Ԗڂ̃A���t�@����

		Time::Instance();

		if (FAILED(Init()))
		{
			return E_FAIL;
		}

		return S_OK;
	}

	//==========================================================
	// �T�v  :�I������
	//==========================================================
	void Application::Uninit()
	{

	}

	//==========================================================
	// �T�v  :�E�B���h�E�̏I���������s���B
	//==========================================================
	void Application::UninitWindow()
	{
		// �E�B���h�E�N���X�̓o�^������
		if (h_instance_)
		{
			UnregisterClassA(WINDOW_CLASSNAME, h_instance_);
		}
		h_instance_ = nullptr;
		h_wnd_ = nullptr;
	}

	//==========================================================
	// �T�v  :Direct3D�̏I���������s��
	//==========================================================
	void Application::UninitDirect3D()
	{
		Uninit();

		// Direct3D�̉��
		if (device != NULL)
		{// �f�o�C�X�I�u�W�F�N�g�̊J��
			device->Release();
			device = NULL;
		}

		if (d3d != NULL)
		{// Direct3D�I�u�W�F�N�g�̊J��
			d3d->Release();
			d3d = NULL;
		}
	}

	//==========================================================
	// �T�v  :�X�V�������s���B
	//==========================================================
	void Application::Update()
	{
		SceneManager::Instance()->Update();
	}

	//==========================================================
	// �T�v  :�`�揈�����s���B
	//==========================================================
	void Application::Draw()
	{
		// �o�b�N�o�b�t�@���y�o�b�t�@�̃N���A
		device->Clear(0, NULL, (D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER), BACKGROUND_COLOR, 1.0f, 0);

		// �`��̊J�n
		if (SUCCEEDED(device->BeginScene()))
		{
			SceneManager::Instance()->Draw();

			// �`��̏I��
			device->EndScene();
		}

		// �o�b�N�o�b�t�@�ƃt�����g�o�b�t�@�̓���ւ�
		device->Present(NULL, NULL, NULL, NULL);
	}


}
