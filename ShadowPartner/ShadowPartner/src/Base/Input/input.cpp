//==========================================================
// �T�v  :���͏���
// Author:Itsuki Namito
// Copyright(c) Utsurugi.All right reserved.
//==========================================================
#include "input.h"


//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define INPUT_AXIS_MAX (1000)
#define INPUT_AXIS_MIN (-1000)
#define CLAMP(v,min,max) (v > max) ? max : (v < min) ? min : v

namespace input {
	//*****************************************************************************
	// �C���X�^���X
	//*****************************************************************************
	Input *Input::instance_;

	Input *Input::Instance()
	{
		if (instance_ == nullptr)
		{
			instance_ = new Input();
		}

		return instance_;
	}

	//*****************************************************************************
	// �R���X�g���N�^
	//*****************************************************************************
	Input::Input()
		: pInput(nullptr)
		, padCount(0)
	{
	}

	//**********************************************************
	// �f�X�g���N�^
	//**********************************************************
	Input::~Input()
	{
		if (instance_ != nullptr)
		{
			delete instance_;
			instance_ = nullptr;
		}
	}

	//=============================================================================
	// �R�[���o�b�N�֐�
	//=============================================================================
	bool CALLBACK Input::SearchGamepadCallback(LPDIDEVICEINSTANCE lpddi, LPVOID)
	{
		HRESULT hr;

		hr = instance_->pInput->CreateDevice(lpddi->guidInstance, &instance_->gamepad[instance_->padCount++].pGamepad, NULL);

		return DIENUM_CONTINUE;	//���̃f�o�C�X���
	}

	//=============================================================================
	// ���͏����̏�����
	//=============================================================================
	HRESULT Input::Init(HINSTANCE hInst, HWND hWnd)
	{
		HRESULT hr;

		if (!pInput)
		{
			// DirectInput�I�u�W�F�N�g�̍쐬
			hr = DirectInput8Create(hInst, DIRECTINPUT_VERSION,
				IID_IDirectInput8, (void**)&pInput, NULL);

			if (FAILED(hr))
			{
				MessageBox(hWnd, "DirectInput�I�u�W�F�N�g�̍쐬�Ɏ��s���܂���", "�x���I", MB_ICONWARNING);
				return hr;
			}
		}

		// �e���͑��u������
		// �L�[�{�[�h�̏�����
		hr = keyboard.Init(hInst, hWnd, pInput);
		if (FAILED(hr))
		{
			MessageBox(hWnd, "�L�[�{�[�h�̏������Ɏ��s���܂���", "�x���I", MB_ICONWARNING);
			return hr;
		}

		// �}�E�X�̏�����
		hr = mouse.Init(hInst, hWnd, pInput);
		if (FAILED(hr))
		{
			MessageBox(hWnd, "�}�E�X�̏������Ɏ��s���܂���", "�x���I", MB_ICONWARNING);
			return hr;
		}

		// �Q�[���p�b�h�̏�����
		padCount = 0;

		pInput->EnumDevices(DI8DEVCLASS_GAMECTRL, (LPDIENUMDEVICESCALLBACK)SearchGamepadCallback, NULL, DIEDFL_ATTACHEDONLY);

		for (int i = 0; i < padCount; ++i)
		{
			hr = gamepad[i].Init(hInst, hWnd, pInput);
			if (FAILED(hr))
			{
				MessageBox(hWnd, "�Q�[���p�b�h�̏������Ɏ��s���܂���", "�x���I", MB_ICONWARNING);
				return hr;
			}
		}

		return S_OK;
	}

	//=============================================================================
	// ���͏����̏I������
	//=============================================================================
	void Input::Uninit(void)
	{
		// �L�[�{�[�h�̏I������
		keyboard.Uninit();

		// �}�E�X�̏I������
		mouse.Uninit();

		// �Q�[���p�b�h�̏I������
		for (int i = 0; i < padCount; ++i)
		{
			gamepad[i].Uninit();
		}

		if (pInput)
		{// DirectInput�I�u�W�F�N�g�̊J��
			pInput->Release();
			pInput = NULL;
		}
	}

	//=============================================================================
	// ���͏����̍X�V����
	//=============================================================================
	void Input::Update(void)
	{
		// �L�[�{�[�h�̍X�V
		keyboard.Update();

		// �}�E�X�̍X�V
		mouse.Update();

		// �Q�[���p�b�h�̍X�V
		for (int i = 0; i < padCount; ++i)
		{
			gamepad[i].Update();
		}

		UpdateButtons();
		UpdateAxis();
	}

	//=============================================================================
	// �_�u���N���b�N�̊��o��ݒ�
	//=============================================================================
	void Input::SetDoubleInterval(DWORD _interval)
	{
		keyboard.SetDoubleInterval(_interval);
		mouse.SetDoubleInterval(_interval);

		for (int i = 0; i < padCount; ++i)
		{
			gamepad[i].SetDoubleInterval(_interval);
		}
	}

	//=============================================================================
	// ���z�{�^���������Ă����
	//=============================================================================
	bool Input::GetButton(InputButton _button)
	{
		return (inputButtonState[_button] & 0x80) ? true : false;
	}

	//=============================================================================
	// ���z�{�^�����������u��
	//=============================================================================
	bool Input::GetButtonDown(InputButton _button)
	{
		return (inputButtonDown[_button] & 0x80) ? true : false;
	}

	//=============================================================================
	// ���z�{�^�������������Ă���
	//�J�E���^:0�܂���2�`19�Ȃ�false,1�܂���20�ȏ�Ȃ�true
	//=============================================================================
	bool Input::GetButtonStay(InputButton _button)
	{
		return (inputButtonStay[_button] & 0x80) ? true : false;
	}

	//=============================================================================
	// ���z�{�^���𗣂����u��
	//=============================================================================
	bool Input::GetButtonUp(InputButton _button)
	{
		return (inputButtonUp[_button] & 0x80) ? true : false;
	}

	//=============================================================================
	// ���z�{�^�����x���������u��
	//=============================================================================
	bool Input::GetButtonDouble(InputButton _button)
	{
		return (inputButtonDouble[_button] & 0x80) ? true : false;
	}

	//=============================================================================
	// ���z���̒l��-1�`1�͈̔͂ŕԂ�
	//=============================================================================
	float Input::GetAxis(InputAxis _axis)
	{
		return CLAMP(((float)inputAxisValue[_axis] / 1000.0f), -1.0f, 1.0f);
	}

	//=============================================================================
	// ���z�{�^���̍X�V
	//=============================================================================
	void Input::UpdateButtons(void)
	{
		//�������񂷂ׂẴ{�^�������Z�b�g����
		for (int i = 0; i < InputButton::ButtonCount; ++i)
		{
			inputButtonState[i] = 0;
			inputButtonDown[i] = 0;
			inputButtonStay[i] = 0;
			inputButtonUp[i] = 0;
			inputButtonDouble[i] = 0;
		}

		//�w�肵�����͂̑g�ݍ��킹�̓��ǂꂩ��ł������𖞂����Ή��z�{�^��������ɍ��킹��
		for (int i = 0; i < CheckState::StateMax; ++i)
		{
			// �A�N�V�����{�^��(�L�[�{�[�hZ�ƃQ�[���p�b�h�Z)
			if (CheckKey(DIK_Z, i) || CheckPad(0, 2, i))
			{
				MeetButton(InputButton::Action, i);
			}

			// �X�L���{�^��(�L�[�{�[�hC�ƃQ�[���p�b�h��)
			if (CheckKey(DIK_C, i) || CheckPad(0, 3, i))
			{
				MeetButton(InputButton::Skill, i);
			}

			// �A�^�b�N�{�^��(�L�[�{�[�hV�ƃQ�[���p�b�h��)
			if (CheckKey(DIK_V, i) || CheckPad(0, 0, i))
			{
				MeetButton(InputButton::Attack, i);
			}

			// �W�����v�{�^��(�L�[�{�[�hSpace�ƃQ�[���p�b�h�~)
			if (CheckKey(DIK_SPACE, i) || CheckPad(0, 1, i))
			{
				MeetButton(InputButton::Jump, i);
			}

			// �L�����Z���{�^��(�L�[�{�[�hX�ƃQ�[���p�b�h�~)
			if (CheckKey(DIK_X, i) || CheckPad(0, 1, i))
			{
				MeetButton(InputButton::Cancel, i);
			}

			// ��{�^��(�L�[�{�[�hW�ƃL�[�{�[�h���ƃQ�[���p�b�h�\����)
			if (CheckKey(DIK_W, i) || CheckKey(DIK_UP, i) || CheckPad(0, 12, i))
			{
				MeetButton(InputButton::Up, i);
			}

			// �E�{�^��(�L�[�{�[�hD�ƃL�[�{�[�h���ƃQ�[���p�b�h�\���E)
			if (CheckKey(DIK_D, i) || CheckKey(DIK_RIGHT, i) || CheckPad(0, 13, i))
			{
				MeetButton(InputButton::Right, i);
			}

			// ���{�^��(�L�[�{�[�hS�ƃL�[�{�[�h���ƃQ�[���p�b�h�\����)
			if (CheckKey(DIK_S, i) || CheckKey(DIK_DOWN, i) || CheckPad(0, 14, i))
			{
				MeetButton(InputButton::Down, i);
			}

			// ���{�^��(�L�[�{�[�hA�ƃL�[�{�[�h���ƃQ�[���p�b�h�\����)
			if (CheckKey(DIK_A, i) || CheckKey(DIK_LEFT, i) || CheckPad(0, 15, i))
			{
				MeetButton(InputButton::Left, i);
			}

			// R1�{�^��(�Q�[���p�b�hR1)
			if (CheckPad(0, 5, i))
			{
				MeetButton(InputButton::R1, i);
			}

			// R2�{�^��(�Q�[���p�b�hR2)
			if (CheckPad(0, 7, i))
			{
				MeetButton(InputButton::R2, i);
			}

			// R3�{�^��(�Q�[���p�b�hR3)
			if (CheckPad(0, 11, i))
			{
				MeetButton(InputButton::R3, i);
			}

			// L1�{�^��(�Q�[���p�b�hL1)
			if (CheckPad(0, 4, i))
			{
				MeetButton(InputButton::L1, i);
			}

			// L2�{�^��(�Q�[���p�b�hL2)
			if (CheckPad(0, 6, i))
			{
				MeetButton(InputButton::L2, i);
			}

			// L3�{�^��(�Q�[���p�b�hL3)
			if (CheckPad(0, 10, i))
			{
				MeetButton(InputButton::L3, i);
			}

			// �X�^�[�g�{�^��(�L�[�{�[�h1�ƃQ�[���p�b�hStart)
			if (CheckKey(DIK_1, i) || CheckPad(0, 9, i))
			{
				MeetButton(InputButton::Start, i);
			}

			// �Z���N�g�{�^��(�L�[�{�[�h2�ƃQ�[���p�b�hSelect)
			if (CheckKey(DIK_2, i) || CheckPad(0, 8, i))
			{
				MeetButton(InputButton::Select, i);
			}

			// �@�\1�{�^��(�L�[�{�[�hF1)
			if (CheckKey(DIK_F1, i))
			{
				MeetButton(InputButton::Function1, i);
			}

			// �@�\2�{�^��(�L�[�{�[�hF2)
			if (CheckKey(DIK_F2, i))
			{
				MeetButton(InputButton::Function2, i);
			}

			// �@�\3�{�^��(�L�[�{�[�hF3)
			if (CheckKey(DIK_F3, i))
			{
				MeetButton(InputButton::Function3, i);
			}

			// �@�\4�{�^��(�L�[�{�[�hF4)
			if (CheckKey(DIK_F4, i))
			{
				MeetButton(InputButton::Function4, i);
			}
		}

		// �����܂�
	}

	//=============================================================================
	// ���z���̍X�V
	//=============================================================================
	void Input::UpdateAxis(void)
	{
		// ������
		{
			long value = gamepad[0].GetPadHorizontal();

			if (keyboard.GetKey(DIK_A) || keyboard.GetKey(DIK_LEFT))
			{
				value -= 1000;
			}
			if (keyboard.GetKey(DIK_D) || keyboard.GetKey(DIK_RIGHT))
			{
				value += 1000;
			}

			inputAxisValue[InputAxis::Horizontal] = CLAMP(value, INPUT_AXIS_MIN, INPUT_AXIS_MAX);
		}

		// ������
		{
			long value = gamepad[0].GetPadVertical();

			if (keyboard.GetKey(DIK_S) || keyboard.GetKey(DIK_DOWN))
			{
				value -= 1000;
			}
			if (keyboard.GetKey(DIK_W) || keyboard.GetKey(DIK_UP))
			{
				value += 1000;
			}

			inputAxisValue[InputAxis::Vertical] = CLAMP(value, INPUT_AXIS_MIN, INPUT_AXIS_MAX);
		}

		// Fire1
		{
			long value = 0;

			if (mouse.GetMouseDown(MouseClick::MouseLeft))
			{
				value += 1000;
			}

			inputAxisValue[InputAxis::Fire1] = CLAMP(value, INPUT_AXIS_MIN, INPUT_AXIS_MAX);
		}

		// Fire2
		{
			long value = 0;

			if (mouse.GetMouseDown(MouseClick::MouseRight))
			{
				value += 1000;
			}

			inputAxisValue[InputAxis::Fire2] = CLAMP(value, INPUT_AXIS_MIN, INPUT_AXIS_MAX);
		}

		// Fire3
		{
			long value = 0;

			if (mouse.GetMouseDown(MouseClick::MouseCenter))
			{
				value += 1000;
			}

			inputAxisValue[InputAxis::Fire3] = CLAMP(value, INPUT_AXIS_MIN, INPUT_AXIS_MAX);
		}

		// MouseX
		{
			long value = mouse.GetMouseX();

			inputAxisValue[InputAxis::MouseX] = CLAMP(value, INPUT_AXIS_MIN, INPUT_AXIS_MAX);
		}

		// MouseY
		{
			long value = mouse.GetMouseY();

			inputAxisValue[InputAxis::MouseY] = CLAMP(value, INPUT_AXIS_MIN, INPUT_AXIS_MAX);
		}

		// MouseScrollWheel
		{
			long value = mouse.GetMouseWheel();

			inputAxisValue[InputAxis::MouseScrollWheel] = CLAMP(value, INPUT_AXIS_MIN, INPUT_AXIS_MAX);
		}

		// RotateX
		{
			long value = gamepad[0].GetPadRotateX();

			inputAxisValue[InputAxis::RotateX] = CLAMP(value, INPUT_AXIS_MIN, INPUT_AXIS_MAX);
		}

		// RotateX
		{
			long value = gamepad[0].GetPadRotateY();

			inputAxisValue[InputAxis::RotateY] = CLAMP(value, INPUT_AXIS_MIN, INPUT_AXIS_MAX);
		}

		// �����܂�
	}
}