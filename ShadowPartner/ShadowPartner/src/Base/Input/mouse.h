//==========================================================
// �T�v  :�}�E�X����
// Author:Itsuki Namito
// Copyright(c) Utsurugi.All right reserved.
//==========================================================
#ifndef _BASE_INPUT_MOUSE_H_
#define _BASE_INPUT_MOUSE_H_

#include <windows.h>
#include <dinput.h>

namespace input
{
	enum MouseClick
	{
		MouseLeft,
		MouseRight,
		MouseCenter,
		MouseClickCount
	};

	class Mouse
	{
	public:
		Mouse() {};
		~Mouse() {};
		Mouse(const Mouse &i) {};
		Mouse &operator=(const Mouse &) { return *this; };

		HRESULT Init(HINSTANCE hInst, HWND hWnd, LPDIRECTINPUT8 pDInput);
		void Uninit(void);
		HRESULT Update(void);

		//=============================================================================
		// �}�E�X�������Ă��
		//=============================================================================
		FORCEINLINE bool GetMouse(MouseClick click)
		{
			return (mouseState.rgbButtons[click] & 0x80) ? true : false;
		}

		//=============================================================================
		// �}�E�X���������u��
		//=============================================================================
		FORCEINLINE bool GetMouseDown(MouseClick click)
		{
			return (mouseDown.rgbButtons[click] & 0x80) ? true : false;
		}

		//=============================================================================
		// �}�E�X�����������Ă���
		//�J�E���^:0�܂���2�`19�Ȃ�false,1�܂���20�ȏ�Ȃ�true
		//=============================================================================
		FORCEINLINE bool GetMouseStay(MouseClick click)
		{
			return (mouseStay.rgbButtons[click] & 0x80) ? true : false;
		}

		//=============================================================================
		// �}�E�X�𗣂����u��
		//=============================================================================
		FORCEINLINE bool GetMouseUp(MouseClick click)
		{
			return (mouseUp.rgbButtons[click] & 0x80) ? true : false;
		}

		//=============================================================================
		// �}�E�X���_�u���N���b�N�����u��
		//=============================================================================
		FORCEINLINE bool GetMouseDouble(MouseClick click)
		{
			return (mouseDouble.rgbButtons[click] & 0x80) ? true : false;
		}

		//=============================================================================
		// �}�E�X��X���ړ��ʂ��擾
		//=============================================================================
		FORCEINLINE long GetMouseX(void)
		{
			return mouseState.lX;
		}

		//=============================================================================
		// �}�E�X��Y���ړ��ʂ��擾
		//=============================================================================
		FORCEINLINE long GetMouseY(void)
		{
			return mouseState.lY;
		}

		//=============================================================================
		// �}�E�X�̃z�C�[���ړ��ʂ��擾
		//=============================================================================
		FORCEINLINE long GetMouseWheel(void)
		{
			return mouseState.lZ;
		}

		void SetDoubleInterval(DWORD _interval);

	private:
		DWORD doubleInterval;			// �_�u���N���b�N���e�Ԋu
		LPDIRECTINPUTDEVICE8	pMouse;	// IDirectInputDevice8�C���^�[�t�F�[�X�ւ̃|�C���^(�}�E�X)
		DIMOUSESTATE2 mouseState;		// �}�E�X�̏��
		DIMOUSESTATE2 mouseDown;	// �}�E�X�������ꂽ�u�Ԃ��L��
		DIMOUSESTATE2 mouseStay;		// �}�E�X�������������Ă����Ԃ��L��
		DIMOUSESTATE2 mouseUp;			// �}�E�X�������ꂽ�u�Ԃ��L��
		DIMOUSESTATE2 mouseDouble;		// �}�E�X���_�u���N���b�N���ꂽ�u�Ԃ��L��
		int mouseStayCnt[8];			// �}�E�X�����������Ă��鎞�Ԃ��v��
		int mouseIntervalCnt[8];		// �}�E�X��
	};
}
#endif