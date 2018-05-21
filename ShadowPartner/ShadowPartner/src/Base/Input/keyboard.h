//==========================================================
// 概要  :キーボード処理
// Author:Itsuki Namito
// Copyright(c) Utsurugi.All right reserved.
//==========================================================
#ifndef _BASE_INPUT_KEYBOARD_H_
#define _BASE_INPUT_KEYBOARD_H_

#include <windows.h>
#include <dinput.h>

#define	NUM_KEY_MAX		(256)		// キー最大数

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
		// キーボードを押してる間
		//=============================================================================
		FORCEINLINE bool GetKey(int nKey)
		{
			return (keyState[nKey] & 0x80) ? true : false;
		}

		//=============================================================================
		// キーボードを押した瞬間
		//=============================================================================
		FORCEINLINE bool GetKeyDown(int nKey)
		{
			return (keyStateDown[nKey] & 0x80) ? true : false;
		}

		//=============================================================================
		// キーボードを押し続けている
		//カウンタ:0または2～19ならfalse,1または20以上ならtrue
		//=============================================================================
		FORCEINLINE bool GetKeyStay(int nKey)
		{
			return (keyStateStay[nKey] & 0x80) ? true : false;
		}

		//=============================================================================
		// キーボードを離した瞬間
		//=============================================================================
		FORCEINLINE bool GetKeyUp(int nKey)
		{
			return (keyStateUp[nKey] & 0x80) ? true : false;
		}

		//=============================================================================
		// キーボードをダブルクリックした瞬間
		//=============================================================================
		FORCEINLINE bool GetKeyDouble(int nKey)
		{
			return (keyStateDouble[nKey] & 0x80) ? true : false;
		}

		void SetDoubleInterval(DWORD _interval);

	private:
		DWORD doubleInterval;
		LPDIRECTINPUTDEVICE8	pKeyboard;						// IDirectInputDevice8インターフェースへのポインタ(キーボード)
		BYTE					keyState[NUM_KEY_MAX];			// キーボードの押下状態を保持するワーク
		BYTE					keyStateDown[NUM_KEY_MAX];		// キーボードの押した瞬間を保持するワーク
		BYTE					keyStateUp[NUM_KEY_MAX];		// キーボードの離した瞬間を保持するワーク
		BYTE					keyStateStay[NUM_KEY_MAX];		// キーボードの押し続けたかを保持するワーク
		BYTE					keyStateDouble[NUM_KEY_MAX];	// キーボードの二度押しを保持するワーク
		int						keyStateStayCnt[NUM_KEY_MAX];	// キーボードを押し続けている時間を計測
		int						keyStateIntervalCnt[NUM_KEY_MAX];	// キーボードを最後に離してからの時間を計測
	};
}
#endif