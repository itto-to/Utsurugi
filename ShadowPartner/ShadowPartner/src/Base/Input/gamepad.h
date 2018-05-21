//==========================================================
// 概要  :ゲームパッド処理
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
		LPDIRECTINPUTDEVICE8	pGamepad;							// IDirectInputDevice8インターフェースへのポインタ(ゲームパッド)

		//Public Functions
		HRESULT Init(HINSTANCE hInst, HWND hWnd, LPDIRECTINPUT8 pDInput);
		void Uninit(void);
		HRESULT Update(void);

		//=============================================================================
		// ゲームパッドを押してる間
		//=============================================================================
		FORCEINLINE bool GetPadButton(int button)
		{
			return (padState.rgbButtons[button] & 0x80) ? true : false;
		}

		//=============================================================================
		// ゲームパッドを押した瞬間
		//=============================================================================
		FORCEINLINE bool GetPadDown(int button)
		{
			return (padDown.rgbButtons[button] & 0x80) ? true : false;
		}

		//=============================================================================
		// ゲームパッドを押し続けている
		//カウンタ:0または2～19ならfalse,1または20以上ならtrue
		//=============================================================================
		FORCEINLINE bool GetPadStay(int button)
		{
			return (padStay.rgbButtons[button] & 0x80) ? true : false;
		}

		//=============================================================================
		// ゲームパッドを離した瞬間
		//=============================================================================
		FORCEINLINE bool GetPadUp(int button)
		{
			return (padUp.rgbButtons[button] & 0x80) ? true : false;
		}

		//=============================================================================
		// ゲームパッドを二度押しした瞬間
		//=============================================================================
		FORCEINLINE bool GetPadDouble(int button)
		{
			return (padDouble.rgbButtons[button] & 0x80) ? true : false;
		}

		//=============================================================================
		// ゲームパッドの水平成分の入力を取得
		//=============================================================================
		FORCEINLINE long GetPadHorizontal(void)
		{
			return padState.lX;
		}

		//=============================================================================
		// ゲームパッドの垂直成分の入力を取得
		//=============================================================================
		FORCEINLINE long GetPadVertical(void)
		{
			return padState.lY;
		}

		//=============================================================================
		// ゲームパッドの右スティックの左右の入力を取得
		//=============================================================================
		FORCEINLINE long GetPadRotateX(void)
		{
			long value = padState.lZ - 32768;
			value = (long)((float)value / 3276.8);
			return value;
		}

		//=============================================================================
		// ゲームパッドの右スティック上下の入力を取得
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
		DIJOYSTATE2	padState;				// ゲームパッドの押下状態を保持するワーク
		DIJOYSTATE2	padDown;				// ゲームパッドのトリガー状態を保持するワーク
		DIJOYSTATE2	padStay;				// ゲームパッドのリリース状態を保持するワーク
		DIJOYSTATE2	padUp;					// ゲームパッドのリピート状態を保持するワーク
		DIJOYSTATE2	padDouble;				// 
		int			padStayCount[128];		// ゲームパッドのリピートカウンタ
		int			padIntervalCount[128];	// 

	};
}
#endif