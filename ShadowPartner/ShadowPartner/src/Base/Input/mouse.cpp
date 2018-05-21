//==========================================================
// �T�v  :�}�E�X����
// Author:Itsuki Namito
// Copyright(c) Utsurugi.All right reserved.
//==========================================================
#include "mouse.h"
#include "Input.h"

namespace input
{
	//*****************************************************************************
	// static�����o
	//*****************************************************************************

	//=============================================================================
	// �}�E�X�̏���������
	//=============================================================================
	HRESULT Mouse::Init(HINSTANCE hInst, HWND hWnd, LPDIRECTINPUT8 pDInput)
	{
		HRESULT hr;

		// �f�o�C�X�I�u�W�F�N�g���쐬
		hr = pDInput->CreateDevice(GUID_SysMouse, &pMouse, NULL);
		if (FAILED(hr) || pMouse == NULL)
		{
			MessageBox(hWnd, "�}�E�X������܂���", "�x���I", MB_ICONWARNING);
			return hr;
		}

		// �f�[�^�t�H�[�}�b�g��ݒ�
		hr = pMouse->SetDataFormat(&c_dfDIMouse2);
		if (FAILED(hr))
		{
			MessageBox(hWnd, "�}�E�X�̃f�[�^�t�H�[�}�b�g��ݒ�ł��܂���ł����B", "�x���I", MB_ICONWARNING);
			return hr;
		}

		// �������[�h��ݒ�i�t�H�A�O���E���h����r�����[�h�j
		hr = pMouse->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE));
		if (FAILED(hr))
		{
			MessageBox(hWnd, "�}�E�X�̋������[�h��ݒ�ł��܂���ł����B", "�x���I", MB_ICONWARNING);
			return hr;
		}

		// �f�o�C�X�̐ݒ�
		DIPROPDWORD prop;
		prop.diph.dwSize = sizeof(prop);
		prop.diph.dwHeaderSize = sizeof(prop.diph);
		prop.diph.dwObj = 0;
		prop.diph.dwHow = DIPH_DEVICE;
		prop.dwData = DIPROPAXISMODE_REL;

		hr = pMouse->SetProperty(DIPROP_AXISMODE, &prop.diph);
		if (FAILED(hr))
		{
			MessageBox(hWnd, "�}�E�X�̃v���p�e�B��ݒ�ł��܂���ł����B", "�x��!", MB_ICONWARNING);
			return hr;
		}

		// �}�E�X�ւ̃A�N�Z�X�����l��(���͐���J�n)
		pMouse->Acquire();

		doubleInterval = INPUT_DOUBLE_DEFAULT_INTERVAL;

		return S_OK;
	}

	//=============================================================================
	// �}�E�X�̏I������
	//=============================================================================
	void Mouse::Uninit(void)
	{
		if (pMouse)
		{
			pMouse->Unacquire();
			// �f�o�C�X�I�u�W�F�N�g�̊J��
			pMouse->Release();
			pMouse = NULL;
		}
	}

	//=============================================================================
	// �}�E�X�̍X�V����
	//=============================================================================
	HRESULT Mouse::Update(void)
	{
		HRESULT hr;
		DIMOUSESTATE2 oldMouseState = mouseState;

		// �f�o�C�X����f�[�^���擾
		hr = pMouse->GetDeviceState(sizeof(mouseState), &mouseState);
		if (SUCCEEDED(hr))
		{
			mouseDown.lX = mouseState.lX;
			mouseDown.lY = mouseState.lY;
			mouseDown.lZ = mouseState.lZ;

			//�}�E�X�̏��
			for (int i = 0; i < 8; ++i)
			{
				//�V���������ꂽ���ǂ���
				mouseDown.rgbButtons[i] = ((oldMouseState.rgbButtons[i] ^ mouseState.rgbButtons[i]) & mouseState.rgbButtons[i]);

				//
				mouseStay.rgbButtons[i] = mouseState.rgbButtons[i];
				mouseDouble.rgbButtons[i] = 0;

				//�����ꂽ���ǂ���
				mouseUp.rgbButtons[i] = ((oldMouseState.rgbButtons[i] ^ mouseState.rgbButtons[i]) & ~mouseState.rgbButtons[i]);	// ~�͔��]������

				if (mouseDown.rgbButtons[i])
				{
					mouseStayCnt[i]++;
					if (mouseStayCnt[i] >= 20)
					{
						mouseStay.rgbButtons[i] = mouseState.rgbButtons[i];
					}

					if (mouseIntervalCnt[i] >= doubleInterval)
						mouseDouble.rgbButtons[i] = mouseState.rgbButtons[i];
					mouseIntervalCnt[i] = 0;
				}
				else
				{
					if (mouseIntervalCnt[i] != 0)
						++mouseIntervalCnt[i];
					else if (mouseStayCnt[i] != 0)
						++mouseIntervalCnt[i];

					mouseStayCnt[i] = 0;
					mouseStay.rgbButtons[i] = 0;
				}
			}
		}
		else
		{
			//�A�N�Z�X���𓾂�
			hr = pMouse->Acquire();
		}

		return hr;
	}

	void Mouse::SetDoubleInterval(DWORD _interval)
	{
		doubleInterval = _interval;
	}
}