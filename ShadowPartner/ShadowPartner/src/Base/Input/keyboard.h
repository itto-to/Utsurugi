//==========================================================
// �T�v  :�L�[�{�[�h����
// Author:Itsuki Namito
// Copyright(c) Utsurugi.All right reserved.
//==========================================================
#ifndef _BASE_INPUT_KEYBOARD_H_
#define _BASE_INPUT_KEYBOARD_H_

#include <windows.h>
#include <dinput.h>

#define	NUM_KEY_MAX		(256)		// �L�[�ő吔

namespace input
{
	class Keyboard
	{
	public:
		Keyboard() {};
		~Keyboard() {};
		Keyboard(const Keyboard &i) {};
		Keyboard &operator=(const Keyboard &) { return *this; };

		HRESULT Init(HINSTANCE hInst, HWND hWnd, LPDIRECTINPUT8 pDInput);
		void Uninit(void);
		HRESULT Update(void);

		//=============================================================================
		// �L�[�{�[�h�������Ă��
		//=============================================================================
		FORCEINLINE bool GetKey(int nKey)
		{
			return (keyState[nKey] & 0x80) ? true : false;
		}

		//=============================================================================
		// �L�[�{�[�h���������u��
		//=============================================================================
		FORCEINLINE bool GetKeyDown(int nKey)
		{
			return (keyStateDown[nKey] & 0x80) ? true : false;
		}

		//=============================================================================
		// �L�[�{�[�h�����������Ă���
		//�J�E���^:0�܂���2�`19�Ȃ�false,1�܂���20�ȏ�Ȃ�true
		//=============================================================================
		FORCEINLINE bool GetKeyStay(int nKey)
		{
			return (keyStateStay[nKey] & 0x80) ? true : false;
		}

		//=============================================================================
		// �L�[�{�[�h�𗣂����u��
		//=============================================================================
		FORCEINLINE bool GetKeyUp(int nKey)
		{
			return (keyStateUp[nKey] & 0x80) ? true : false;
		}

		//=============================================================================
		// �L�[�{�[�h���_�u���N���b�N�����u��
		//=============================================================================
		FORCEINLINE bool GetKeyDouble(int nKey)
		{
			return (keyStateDouble[nKey] & 0x80) ? true : false;
		}

		void SetDoubleInterval(DWORD _interval);

	private:
		DWORD doubleInterval;
		LPDIRECTINPUTDEVICE8	pKeyboard;						// IDirectInputDevice8�C���^�[�t�F�[�X�ւ̃|�C���^(�L�[�{�[�h)
		BYTE					keyState[NUM_KEY_MAX];			// �L�[�{�[�h�̉�����Ԃ�ێ����郏�[�N
		BYTE					keyStateDown[NUM_KEY_MAX];		// �L�[�{�[�h�̉������u�Ԃ�ێ����郏�[�N
		BYTE					keyStateUp[NUM_KEY_MAX];		// �L�[�{�[�h�̗������u�Ԃ�ێ����郏�[�N
		BYTE					keyStateStay[NUM_KEY_MAX];		// �L�[�{�[�h�̉�������������ێ����郏�[�N
		BYTE					keyStateDouble[NUM_KEY_MAX];	// �L�[�{�[�h�̓�x������ێ����郏�[�N
		int						keyStateStayCnt[NUM_KEY_MAX];	// �L�[�{�[�h�����������Ă��鎞�Ԃ��v��
		int						keyStateIntervalCnt[NUM_KEY_MAX];	// �L�[�{�[�h���Ō�ɗ����Ă���̎��Ԃ��v��
	};
}
#endif