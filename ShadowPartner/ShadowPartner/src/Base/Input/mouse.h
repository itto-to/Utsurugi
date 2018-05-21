//==========================================================
// 概要  :マウス処理
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
		// マウスを押してる間
		//=============================================================================
		FORCEINLINE bool GetMouse(MouseClick click)
		{
			return (mouseState.rgbButtons[click] & 0x80) ? true : false;
		}

		//=============================================================================
		// マウスを押した瞬間
		//=============================================================================
		FORCEINLINE bool GetMouseDown(MouseClick click)
		{
			return (mouseDown.rgbButtons[click] & 0x80) ? true : false;
		}

		//=============================================================================
		// マウスを押し続けている
		//カウンタ:0または2～19ならfalse,1または20以上ならtrue
		//=============================================================================
		FORCEINLINE bool GetMouseStay(MouseClick click)
		{
			return (mouseStay.rgbButtons[click] & 0x80) ? true : false;
		}

		//=============================================================================
		// マウスを離した瞬間
		//=============================================================================
		FORCEINLINE bool GetMouseUp(MouseClick click)
		{
			return (mouseUp.rgbButtons[click] & 0x80) ? true : false;
		}

		//=============================================================================
		// マウスをダブルクリックした瞬間
		//=============================================================================
		FORCEINLINE bool GetMouseDouble(MouseClick click)
		{
			return (mouseDouble.rgbButtons[click] & 0x80) ? true : false;
		}

		//=============================================================================
		// マウスのX軸移動量を取得
		//=============================================================================
		FORCEINLINE long GetMouseX(void)
		{
			return mouseState.lX;
		}

		//=============================================================================
		// マウスのY軸移動量を取得
		//=============================================================================
		FORCEINLINE long GetMouseY(void)
		{
			return mouseState.lY;
		}

		//=============================================================================
		// マウスのホイール移動量を取得
		//=============================================================================
		FORCEINLINE long GetMouseWheel(void)
		{
			return mouseState.lZ;
		}

		void SetDoubleInterval(DWORD _interval);

	private:
		DWORD doubleInterval;			// ダブルクリック許容間隔
		LPDIRECTINPUTDEVICE8	pMouse;	// IDirectInputDevice8インターフェースへのポインタ(マウス)
		DIMOUSESTATE2 mouseState;		// マウスの状態
		DIMOUSESTATE2 mouseDown;	// マウスが押された瞬間を記憶
		DIMOUSESTATE2 mouseStay;		// マウスが押し続けられている状態を記憶
		DIMOUSESTATE2 mouseUp;			// マウスが離された瞬間を記憶
		DIMOUSESTATE2 mouseDouble;		// マウスをダブルクリックされた瞬間を記憶
		int mouseStayCnt[8];			// マウスを押し続けている時間を計測
		int mouseIntervalCnt[8];		// マウスを
	};
}
#endif