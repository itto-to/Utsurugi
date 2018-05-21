//==========================================================
// �T�v  :���͏���
// Author:Itsuki Namito
// Copyright(c) Utsurugi.All right reserved.
//==========================================================
#ifndef _BASE_INPUT_INPUT_H_
#define _BASE_INPUT_INPUT_H_

#include <windows.h>
#include <d3dx9.h>
#define DIRECTINPUT_VERSION (0x0800)
#include <dinput.h>
#include "keyboard.h"
#include "mouse.h"
#include "gamepad.h"

#include <stdio.h>

#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")
#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define INPUT_DOUBLE_DEFAULT_INTERVAL (20)
#define GAMEPAD_MAX (1)

namespace input
{
	enum InputButton
	{
		Action,		//�A�N�V�����iZ,�Z�j
		Skill,		//�X�L���iC,���j
		Attack,		//�A�^�b�N�iV,���j
		Jump,		//�W�����v�{�^���iSPACE,�~�j
		Cancel,		//�L�����Z���{�^���iX,�~�j
		Up,			//�\����A����
		Right,		//�\���E�A�E���
		Down,		//�\�����A�����
		Left,		//�\�����A�����
		R1,			//R1�{�^��
		R2,			//R2�{�^��
		R3,			//R3�{�^��
		L1,			//L1�{�^��
		L2,			//L2�{�^��
		L3,			//L3�{�^��
		Start,		//�X�^�[�g�{�^��
		Select,		//�Z���N�g�{�^��
		Function1,
		Function2,
		Function3,
		Function4,
		ButtonCount	//�{�^���̐�
	};

	enum InputAxis
	{
		Horizontal,			//��������-1�`1
		Vertical,			//���͐���-1�`1
		Fire1,				//
		Fire2,				//
		Fire3,				//
		MouseX,				//
		MouseY,				//
		MouseScrollWheel,	//
		RotateX,
		RotateY,

		AxisCount
	};

	//*****************************************************************************
	// Input�N���X
	//*****************************************************************************
	class Input
	{
	public:

		//�R���X�g���N�^
		Input();
		~Input();//�f�X�g���N�^

		Keyboard keyboard;
		Mouse mouse;
		Gamepad gamepad[GAMEPAD_MAX];

		HRESULT Init(HINSTANCE hInst, HWND hWnd);
		void Uninit(void);
		void Update(void);

		//���͂��擾
		static Input *Instance();
		bool GetButton(InputButton _button);
		bool GetButtonDown(InputButton _button);
		bool GetButtonStay(InputButton _button);
		bool GetButtonUp(InputButton _button);
		bool GetButtonDouble(InputButton _button);

		float GetAxis(InputAxis _axis);

		void SetDoubleInterval(DWORD _interval);

	private:
		static Input *instance_;

		LPDIRECTINPUT8 pInput;	// IDirectInput8�C���^�[�t�F�[�X�ւ̃|�C���^
		int padCount;

		//�V���O���g��
		Input(const Input &i) {}
		Input &operator=(const Input &) { return *this; }

		// Private Functions
		// ���z�{�^���̃��[�N
		BYTE	inputButtonState[InputButton::ButtonCount];			//���z�{�^���̉�����Ԃ�ێ����郏�[�N
		BYTE	inputButtonDown[InputButton::ButtonCount];			//���z�{�^���̉�����Ԃ�ێ����郏�[�N
		BYTE	inputButtonStay[InputButton::ButtonCount];			//���z�{�^���̉�����Ԃ�ێ����郏�[�N
		BYTE	inputButtonUp[InputButton::ButtonCount];			//���z�{�^���̉�����Ԃ�ێ����郏�[�N
		BYTE	inputButtonDouble[InputButton::ButtonCount];		//���z�{�^���̉�����Ԃ�ێ����郏�[�N

		// ���z���̃��[�N
		long	inputAxisValue[InputAxis::AxisCount];

		// Private Functions
		static bool CALLBACK SearchGamepadCallback(LPDIDEVICEINSTANCE lpddi, LPVOID);
		void UpdateButtons(void);	// ���z�{�^���̍X�V�B�����Ȃ�̂ŕ�����
		void UpdateAxis(void);		// ���z���̍X�V�B�����Ȃ�̂ŕ�����

		enum CheckState
		{
			Pushed,
			StateDown,
			StateStay,
			StateUp,
			StateDouble,
			StateMax
		};

		//=============================================================================
		// �L�[�{�[�h�̓��͂��m�F����
		//=============================================================================
		FORCEINLINE bool CheckKey(int _key, int _checkState)
		{
			switch (_checkState)
			{
			case CheckState::Pushed:
			{
				return keyboard.GetKey(_key);
			}
			break;

			case CheckState::StateDown:
			{
				return keyboard.GetKeyDown(_key);
			}
			break;

			case CheckState::StateStay:
			{
				return keyboard.GetKeyStay(_key);
			}
			break;

			case CheckState::StateUp:
			{
				return keyboard.GetKeyUp(_key);
			}
			break;

			case CheckState::StateDouble:
			{
				return keyboard.GetKeyDouble(_key);
			}
			break;

			default:
			{
				return false;
			}
			break;
			}

			return false;
		}

		//=============================================================================
		// �}�E�X�̓��͂��m�F����
		//=============================================================================
		FORCEINLINE bool CheckMouse(MouseClick _click, int _checkState)
		{
			switch (_checkState)
			{
			case CheckState::Pushed:
			{
				return mouse.GetMouse(_click);
			}
			break;

			case CheckState::StateDown:
			{
				return mouse.GetMouseDown(_click);
			}
			break;

			case CheckState::StateStay:
			{
				return mouse.GetMouseStay(_click);
			}
			break;

			case CheckState::StateUp:
			{
				return mouse.GetMouseUp(_click);
			}
			break;

			case CheckState::StateDouble:
			{
				return mouse.GetMouseDouble(_click);
			}
			break;

			default:
			{
				return false;
			}
			break;
			}

			return false;
		}

		//=============================================================================
		// �Q�[���p�b�h�̓��͂��m�F����
		//=============================================================================
		FORCEINLINE bool CheckPad(int padNo, int _button, int _checkState)
		{
			switch (_checkState)
			{
			case CheckState::Pushed:
			{
				return gamepad[padNo].GetPadButton(_button);
			}
			break;

			case CheckState::StateDown:
			{
				return gamepad[padNo].GetPadDown(_button);
			}
			break;

			case CheckState::StateStay:
			{
				return gamepad[padNo].GetPadStay(_button);
			}
			break;

			case CheckState::StateUp:
			{
				return gamepad[padNo].GetPadUp(_button);
			}
			break;

			case CheckState::StateDouble:
			{
				return gamepad[padNo].GetPadDouble(_button);
			}
			break;

			default:
			{
				return false;
			}
			break;
			}

			return false;
		}

		//=============================================================================
		// ���z�{�^���̏�Ԃ𖞂����Ă���
		//=============================================================================
		FORCEINLINE void MeetButton(InputButton _button, int state)
		{
			switch (state)
			{
			case CheckState::Pushed:
			{
				inputButtonState[_button] = 0x80;
			}
			break;

			case CheckState::StateDown:
			{
				inputButtonDown[_button] = 0x80;
			}
			break;

			case CheckState::StateStay:
			{
				inputButtonStay[_button] = 0x80;
			}
			break;

			case CheckState::StateUp:
			{
				inputButtonUp[_button] = 0x80;
			}
			break;

			case CheckState::StateDouble:
			{
				inputButtonDouble[_button] = 0x80;
			}
			break;

			default:
				break;
			}
		}

	};
}
#endif