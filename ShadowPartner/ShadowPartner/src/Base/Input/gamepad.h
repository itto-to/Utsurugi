//==========================================================
// �T�v  :�Q�[���p�b�h����
// Author:Itsuki Namito
// Copyright(c) Utsurugi.All right reserved.
//==========================================================
#ifndef _BASE_INPUT_GAMEPAD_H_
#define _BASE_INPUT_GAMEPAD_H_

#include <windows.h>
#include <dinput.h>

namespace input
{
	class Gamepad
	{
	public:
		Gamepad() {};
		~Gamepad() {};
		Gamepad(const Gamepad &i) {};
		Gamepad &operator=(const Gamepad &) { return *this; };

		//Public Variables
		LPDIRECTINPUTDEVICE8	pGamepad;							// IDirectInputDevice8�C���^�[�t�F�[�X�ւ̃|�C���^(�Q�[���p�b�h)

		//Public Functions
		HRESULT Init(HINSTANCE hInst, HWND hWnd, LPDIRECTINPUT8 pDInput);
		void Uninit(void);
		HRESULT Update(void);

		//=============================================================================
		// �Q�[���p�b�h�������Ă��
		//=============================================================================
		FORCEINLINE bool GetPadButton(int button)
		{
			return (padState.rgbButtons[button] & 0x80) ? true : false;
		}

		//=============================================================================
		// �Q�[���p�b�h���������u��
		//=============================================================================
		FORCEINLINE bool GetPadDown(int button)
		{
			return (padDown.rgbButtons[button] & 0x80) ? true : false;
		}

		//=============================================================================
		// �Q�[���p�b�h�����������Ă���
		//�J�E���^:0�܂���2�`19�Ȃ�false,1�܂���20�ȏ�Ȃ�true
		//=============================================================================
		FORCEINLINE bool GetPadStay(int button)
		{
			return (padStay.rgbButtons[button] & 0x80) ? true : false;
		}

		//=============================================================================
		// �Q�[���p�b�h�𗣂����u��
		//=============================================================================
		FORCEINLINE bool GetPadUp(int button)
		{
			return (padUp.rgbButtons[button] & 0x80) ? true : false;
		}

		//=============================================================================
		// �Q�[���p�b�h���x���������u��
		//=============================================================================
		FORCEINLINE bool GetPadDouble(int button)
		{
			return (padDouble.rgbButtons[button] & 0x80) ? true : false;
		}

		//=============================================================================
		// �Q�[���p�b�h�̐��������̓��͂��擾
		//=============================================================================
		FORCEINLINE long GetPadHorizontal(void)
		{
			return padState.lX;
		}

		//=============================================================================
		// �Q�[���p�b�h�̐��������̓��͂��擾
		//=============================================================================
		FORCEINLINE long GetPadVertical(void)
		{
			return padState.lY;
		}

		//=============================================================================
		// �Q�[���p�b�h�̉E�X�e�B�b�N�̍��E�̓��͂��擾
		//=============================================================================
		FORCEINLINE long GetPadRotateX(void)
		{
			long value = padState.lZ - 32768;
			value = (long)((float)value / 3276.8);
			return value;
		}

		//=============================================================================
		// �Q�[���p�b�h�̉E�X�e�B�b�N�㉺�̓��͂��擾
		//=============================================================================
		FORCEINLINE long GetPadRotateY(void)
		{
			long value = padState.lRz - 32768;
			value = (long)((float)value / 3276.8);
			return value;
		}

		void SetDoubleInterval(DWORD _interval);

	private:
		// Private Variables
		DWORD doubleInterval;
		DIJOYSTATE2	padState;				// �Q�[���p�b�h�̉�����Ԃ�ێ����郏�[�N
		DIJOYSTATE2	padDown;				// �Q�[���p�b�h�̃g���K�[��Ԃ�ێ����郏�[�N
		DIJOYSTATE2	padStay;				// �Q�[���p�b�h�̃����[�X��Ԃ�ێ����郏�[�N
		DIJOYSTATE2	padUp;					// �Q�[���p�b�h�̃��s�[�g��Ԃ�ێ����郏�[�N
		DIJOYSTATE2	padDouble;				// 
		int			padStayCount[128];		// �Q�[���p�b�h�̃��s�[�g�J�E���^
		int			padIntervalCount[128];	// 

	};
}
#endif