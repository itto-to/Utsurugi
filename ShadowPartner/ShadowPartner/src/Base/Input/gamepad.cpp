//==========================================================
// �T�v  :�Q�[���p�b�h����
// Author:Itsuki Namito
// Copyright(c) Utsurugi.All right reserved.
//==========================================================
#include "gamepad.h"
#include "Input.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define DEADZONE (2500)
#define RANGE_MAX (1000)
#define RANGE_MIN (-1000)

namespace input
{
	//=============================================================================
	// �Q�[���p�b�h�̏���������
	//=============================================================================
	HRESULT Gamepad::Init(HINSTANCE hInst, HWND hWnd, LPDIRECTINPUT8 pDInput)
	{
		HRESULT hr;

		hr = pGamepad->SetDataFormat(&c_dfDIJoystick2);
		if (FAILED(hr))
		{
			MessageBox(hWnd, "�Q�[���p�b�h�̃f�[�^�t�H�[�}�b�g��ݒ�ł��܂���ł����B", "�x���I", MB_ICONWARNING);
			return hr;
		}

		// �������[�h��ݒ�i�t�H�A�O���E���h����r�����[�h�j
		hr = pGamepad->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE));
		if (FAILED(hr))
		{
			MessageBox(hWnd, "�Q�[���p�b�h�̋������[�h��ݒ�ł��܂���ł����B", "�x���I", MB_ICONWARNING);
			return hr;
		}

		// ���̒l���ݒ�
		// X���AY���̂��ꂼ��ɂ��āA�I�u�W�F�N�g��񍐉\�Ȓn����Z�b�g����
		// (max - min)�́A�ő�10000�B(max - min) / 2�������l
		DIPROPRANGE diprg;
		ZeroMemory(&diprg, sizeof(diprg));
		diprg.diph.dwSize = sizeof(diprg);
		diprg.diph.dwHeaderSize = sizeof(diprg.diph);
		diprg.diph.dwHow = DIPH_BYOFFSET;
		diprg.lMin = RANGE_MIN;
		diprg.lMax = RANGE_MAX;

		// X���͈̔͂�ݒ�
		diprg.diph.dwObj = DIJOFS_X;
		pGamepad->SetProperty(DIPROP_RANGE, &diprg.diph);
		// Y���͈̔͂�ݒ�
		diprg.diph.dwObj = DIJOFS_Y;
		pGamepad->SetProperty(DIPROP_RANGE, &diprg.diph);

		// �e�����Ƃɖ����]�[���l��ݒ肷��B
		DIPROPDWORD dipdw;
		dipdw.diph.dwSize = sizeof(DIPROPDWORD);
		dipdw.diph.dwHeaderSize = sizeof(dipdw.diph);
		dipdw.diph.dwHow = DIPH_BYOFFSET;
		dipdw.dwData = DEADZONE;

		// X���̖����]�[����ݒ�
		dipdw.diph.dwObj = DIJOFS_X;
		pGamepad->SetProperty(DIPROP_DEADZONE, &dipdw.diph);
		// Y���̖����]�[����ݒ�
		dipdw.diph.dwObj = DIJOFS_Y;
		pGamepad->SetProperty(DIPROP_DEADZONE, &dipdw.diph);

		// �Q�[���p�b�h�ւ̃A�N�Z�X�����l��(���͐���J�n)
		pGamepad->Acquire();

		doubleInterval = INPUT_DOUBLE_DEFAULT_INTERVAL;

		return S_OK;
	}

	//=============================================================================
	// �Q�[���p�b�h�̏I������
	//=============================================================================
	void Gamepad::Uninit(void)
	{
		if (pGamepad)
		{
			pGamepad->Unacquire();

			// �f�o�C�X�I�u�W�F�N�g�̊J��
			pGamepad->Release();
			pGamepad = NULL;
		}
	}

	//=============================================================================
	// �Q�[���p�b�h�̍X�V����
	//=============================================================================
	HRESULT Gamepad::Update(void)
	{
		HRESULT hr;
		DIJOYSTATE2 oldPadState = padState;

		hr = pGamepad->Poll();
		if (FAILED(hr))
		{
			hr = pGamepad->Acquire();
			while (hr == DIERR_INPUTLOST)
				hr = pGamepad->Acquire();
		}

		// �f�o�C�X����f�[�^���擾
		hr = pGamepad->GetDeviceState(sizeof(DIJOYSTATE2), &padState);
		if (hr == DIERR_INPUTLOST || hr == DIERR_NOTACQUIRED)
		{
			hr = pGamepad->Acquire();
			while (hr == DIERR_INPUTLOST)
			{
				hr = pGamepad->Acquire();
			}
		}

		// �\���L�[�̓��͂��g���ĂȂ������Ƃ���ɓ��ꂿ�Ⴆ
		if (padState.rgdwPOV[0] == 0)padState.rgbButtons[12] = 0x80;
		if (padState.rgdwPOV[0] == 4500)
		{
			padState.rgbButtons[12] = 0x80; padState.rgbButtons[13] = 0x80;
		}
		if (padState.rgdwPOV[0] == 9000)padState.rgbButtons[13] = 0x80;
		if (padState.rgdwPOV[0] == 13500)
		{
			padState.rgbButtons[13] = 0x80; padState.rgbButtons[14] = 0x80;
		}
		if (padState.rgdwPOV[0] == 18000)padState.rgbButtons[14] = 0x80;
		if (padState.rgdwPOV[0] == 22500)
		{
			padState.rgbButtons[14] = 0x80; padState.rgbButtons[15] = 0x80;
		}
		if (padState.rgdwPOV[0] == 27000)padState.rgbButtons[15] = 0x80;
		if (padState.rgdwPOV[0] == 31500)
		{
			padState.rgbButtons[12] = 0x80; padState.rgbButtons[15] = 0x80;
		}

		for (int i = 0; i < 128; ++i)
		{
			padDown.rgbButtons[i] = ((oldPadState.rgbButtons[i] ^ padState.rgbButtons[i]) & padState.rgbButtons[i]);
			padStay.rgbButtons[i] = padDown.rgbButtons[i];
			padDouble.rgbButtons[i] = 0;
			padUp.rgbButtons[i] = ((oldPadState.rgbButtons[i] ^ padState.rgbButtons[i]) & ~padState.rgbButtons[i]);

			if (padDown.rgbButtons[i])
			{
				padStayCount[i]++;
				if (padStayCount[i] >= 20)
				{
					padStay.rgbButtons[i] = padState.rgbButtons[i];
				}

				if (padIntervalCount[i] >= doubleInterval)
					padDouble.rgbButtons[i] = padState.rgbButtons[i];

				padIntervalCount[i] = 0;
			}
			else
			{
				if (padIntervalCount[i] != 0)
				{
					++padIntervalCount[i];
				}
				else if (padStayCount[i] != 0)
				{
					++padIntervalCount[i];
				}

				padStayCount[i] = 0;
				padStay.rgbButtons[i] = 0;
			}

		}

		//ImGui::SetNextWindowPos(ImVec2(20, 20));
		//ImGui::SetNextWindowSize(ImVec2(200, 560));
		//ImGui::Begin("Input Check");

		//ImGui::Text("lX:%d", padState.lX);
		//ImGui::Text("lY:%d", padState.lY);
		//ImGui::Text("lZ:%d", padState.lZ);
		//ImGui::Text("lRx:%d", padState.lRx);
		//ImGui::Text("lRy:%d", padState.lRy);
		//ImGui::Text("lRz:%d", padState.lRz);
		//ImGui::Text("lARx:%d", padState.lARx);
		//ImGui::Text("lARy:%d", padState.lARy);
		//ImGui::Text("lARz:%d", padState.lARz);
		//ImGui::Text("lVX:%d", padState.lVX);
		//ImGui::Text("lVY:%d", padState.lVY);
		//ImGui::Text("lVZ:%d", padState.lVZ);
		//ImGui::Text("lAX:%d", padState.lAX);
		//ImGui::Text("lAY:%d", padState.lAY);
		//ImGui::Text("lAZ:%d", padState.lAZ);
		//ImGui::Text("lFRx:%d", padState.lFRx);
		//ImGui::Text("lFRy:%d", padState.lFRy);
		//ImGui::Text("lFRz:%d", padState.lFRz);
		//ImGui::Text("lFX:%d", padState.lFX);
		//ImGui::Text("lFY:%d", padState.lFY);
		//ImGui::Text("lFZ:%d", padState.lFZ);
		//ImGui::Text("lVRx:%d", padState.lVRx);
		//ImGui::Text("lVRy:%d", padState.lVRy);
		//ImGui::Text("lVRz:%d", padState.lVRz);
		//ImGui::Text("Pov0:%d", padState.rgdwPOV[0]);
		//ImGui::Text("Pov1:%d", padState.rgdwPOV[1]);
		//ImGui::Text("Pov2:%d", padState.rgdwPOV[2]);
		//ImGui::Text("Pov3:%d", padState.rgdwPOV[3]);

		//ImGui::End();
		return S_OK;
	}

	//=============================================================================
	// �Q�[���p�b�h�̐��������̓��͂��擾
	//=============================================================================
	void Gamepad::SetDoubleInterval(DWORD _interval)
	{
		doubleInterval = _interval;
	}
}