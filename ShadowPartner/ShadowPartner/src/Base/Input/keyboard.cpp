//==========================================================
// �T�v  :�L�[�{�[�h����
// Author:Itsuki Namito
// Copyright(c) Utsurugi.All right reserved.
//==========================================================
#include "keyboard.h"
#include "Input.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************

namespace input
{
	//=============================================================================
	// �L�[�{�[�h�̏���������
	//=============================================================================
	HRESULT Keyboard::Init(HINSTANCE hInst, HWND hWnd, LPDIRECTINPUT8 pDInput)
	{
		HRESULT hr;

		// �f�o�C�X�I�u�W�F�N�g���쐬
		hr = pDInput->CreateDevice(GUID_SysKeyboard, &pKeyboard, NULL);
		if (FAILED(hr) || pKeyboard == NULL)
		{
			MessageBox(hWnd, "�L�[�{�[�h������܂���", "�x���I", MB_ICONWARNING);
			return hr;
		}

		// �f�[�^�t�H�[�}�b�g��ݒ�
		hr = pKeyboard->SetDataFormat(&c_dfDIKeyboard);
		if (FAILED(hr))
		{
			MessageBox(hWnd, "�L�[�{�[�h�̃f�[�^�t�H�[�}�b�g��ݒ�ł��܂���ł����B", "�x���I", MB_ICONWARNING);
			return hr;
		}

		// �������[�h��ݒ�i�t�H�A�O���E���h����r�����[�h�j
		hr = pKeyboard->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE));
		if (FAILED(hr))
		{
			MessageBox(hWnd, "�L�[�{�[�h�̋������[�h��ݒ�ł��܂���ł����B", "�x���I", MB_ICONWARNING);
			return hr;
		}

		// �L�[�{�[�h�ւ̃A�N�Z�X�����l��(���͐���J�n)
		pKeyboard->Acquire();

		doubleInterval = INPUT_DOUBLE_DEFAULT_INTERVAL;

		return S_OK;
	}

	//=============================================================================
	// �L�[�{�[�h�̏I������
	//=============================================================================
	void Keyboard::Uninit(void)
	{
		if (pKeyboard)
		{
			pKeyboard->Unacquire();
			// �f�o�C�X�I�u�W�F�N�g�̊J��
			pKeyboard->Release();
			pKeyboard = NULL;
		}
	}

	//=============================================================================
	// �L�[�{�[�h�̍X�V����
	//=============================================================================
	HRESULT Keyboard::Update(void)
	{
		HRESULT hr;
		BYTE aCurrentKeyState[NUM_KEY_MAX];

		// �f�o�C�X����f�[�^���擾
		hr = pKeyboard->GetDeviceState(sizeof(aCurrentKeyState), aCurrentKeyState);
		if (SUCCEEDED(hr))
		{
			for (int nCntKey = 0; nCntKey < NUM_KEY_MAX; nCntKey++)
			{
				// ^��XOR
				keyStateDown[nCntKey] = (keyState[nCntKey] ^ aCurrentKeyState[nCntKey]) & aCurrentKeyState[nCntKey];//��Ԃ��ω������A�������ꂽ
				keyStateUp[nCntKey] = (keyState[nCntKey] ^ aCurrentKeyState[nCntKey]) & ~aCurrentKeyState[nCntKey];	//��Ԃ��ω������A�������ꂽ
				keyStateStay[nCntKey] = keyStateDown[nCntKey];	//�ꎞ�I�ɑO�񉟂��ꂽ���ǂ����������
				keyStateDouble[nCntKey] = 0;

				//�L�[��������Ă���ꍇ
				if (keyState[nCntKey])
				{
					//���̃L�[��������Ă���Ȃ�J�E���g���A20�ȏ�Ȃ�1������
					keyStateStayCnt[nCntKey]++;
					if (keyStateStayCnt[nCntKey] >= 20)
					{
						keyStateStay[nCntKey] = aCurrentKeyState[nCntKey];
					}

					if (keyStateIntervalCnt[nCntKey] >= doubleInterval)
						keyStateDouble[nCntKey] = aCurrentKeyState[nCntKey];
					keyStateIntervalCnt[nCntKey] = 0;
				}
				else
				{
					if (keyStateIntervalCnt[nCntKey] != 0)
					{
						++keyStateIntervalCnt[nCntKey];
					}
					else if (keyStateStayCnt[nCntKey] != 0)
					{
						++keyStateIntervalCnt[nCntKey];	//�����������u�ԂȂ�J�E���g
					}
					//�L�[��������ĂȂ��Ȃ�J�E���^��0�ɂ��Ă�蒼��
					keyStateStayCnt[nCntKey] = 0;
					keyStateStay[nCntKey] = 0;
				}

				keyState[nCntKey] = aCurrentKeyState[nCntKey];
			}
		}
		else
		{
			// �L�[�{�[�h�ւ̃A�N�Z�X�����擾
			pKeyboard->Acquire();
		}

		return S_OK;
	}

	//=============================================================================
	// �_�u���N���b�N�̊��o��ݒ�
	//=============================================================================
	void Keyboard::SetDoubleInterval(DWORD _interval)
	{
		doubleInterval = _interval;
	}
}