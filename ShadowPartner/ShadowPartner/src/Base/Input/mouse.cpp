//==========================================================
// 概要  :マウス処理
// Author:Itsuki Namito
// Copyright(c) Utsurugi.All right reserved.
//==========================================================
#include "mouse.h"
#include "Input.h"

namespace input
{
	//*****************************************************************************
	// staticメンバ
	//*****************************************************************************

	//=============================================================================
	// マウスの初期化処理
	//=============================================================================
	HRESULT Mouse::Init(HINSTANCE hInst, HWND hWnd, LPDIRECTINPUT8 pDInput)
	{
		HRESULT hr;

		// デバイスオブジェクトを作成
		hr = pDInput->CreateDevice(GUID_SysMouse, &pMouse, NULL);
		if (FAILED(hr) || pMouse == NULL)
		{
			MessageBox(hWnd, "マウスがありません", "警告！", MB_ICONWARNING);
			return hr;
		}

		// データフォーマットを設定
		hr = pMouse->SetDataFormat(&c_dfDIMouse2);
		if (FAILED(hr))
		{
			MessageBox(hWnd, "マウスのデータフォーマットを設定できませんでした。", "警告！", MB_ICONWARNING);
			return hr;
		}

		// 協調モードを設定（フォアグラウンド＆非排他モード）
		hr = pMouse->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE));
		if (FAILED(hr))
		{
			MessageBox(hWnd, "マウスの協調モードを設定できませんでした。", "警告！", MB_ICONWARNING);
			return hr;
		}

		// デバイスの設定
		DIPROPDWORD prop;
		prop.diph.dwSize = sizeof(prop);
		prop.diph.dwHeaderSize = sizeof(prop.diph);
		prop.diph.dwObj = 0;
		prop.diph.dwHow = DIPH_DEVICE;
		prop.dwData = DIPROPAXISMODE_REL;

		hr = pMouse->SetProperty(DIPROP_AXISMODE, &prop.diph);
		if (FAILED(hr))
		{
			MessageBox(hWnd, "マウスのプロパティを設定できませんでした。", "警告!", MB_ICONWARNING);
			return hr;
		}

		// マウスへのアクセス権を獲得(入力制御開始)
		pMouse->Acquire();

		doubleInterval = INPUT_DOUBLE_DEFAULT_INTERVAL;

		return S_OK;
	}

	//=============================================================================
	// マウスの終了処理
	//=============================================================================
	void Mouse::Uninit(void)
	{
		if (pMouse)
		{
			pMouse->Unacquire();
			// デバイスオブジェクトの開放
			pMouse->Release();
			pMouse = NULL;
		}
	}

	//=============================================================================
	// マウスの更新処理
	//=============================================================================
	HRESULT Mouse::Update(void)
	{
		HRESULT hr;
		DIMOUSESTATE2 oldMouseState = mouseState;

		// デバイスからデータを取得
		hr = pMouse->GetDeviceState(sizeof(mouseState), &mouseState);
		if (SUCCEEDED(hr))
		{
			mouseDown.lX = mouseState.lX;
			mouseDown.lY = mouseState.lY;
			mouseDown.lZ = mouseState.lZ;

			//マウスの状態
			for (int i = 0; i < 8; ++i)
			{
				//新しく押されたかどうか
				mouseDown.rgbButtons[i] = ((oldMouseState.rgbButtons[i] ^ mouseState.rgbButtons[i]) & mouseState.rgbButtons[i]);

				//
				mouseStay.rgbButtons[i] = mouseState.rgbButtons[i];
				mouseDouble.rgbButtons[i] = 0;

				//離されたかどうか
				mouseUp.rgbButtons[i] = ((oldMouseState.rgbButtons[i] ^ mouseState.rgbButtons[i]) & ~mouseState.rgbButtons[i]);	// ~は反転させる

				if (mouseDown.rgbButtons[i])
				{
					mouseStayCnt[i]++;
					if (mouseStayCnt[i] >= 20)
					{
						mouseStay.rgbButtons[i] = mouseState.rgbButtons[i];
					}

					if (mouseIntervalCnt[i] >= doubleInterval)
						mouseDouble.rgbButtons[i] = mouseState.rgbButtons[i];
					mouseIntervalCnt[i] = 0;
				}
				else
				{
					if (mouseIntervalCnt[i] != 0)
						++mouseIntervalCnt[i];
					else if (mouseStayCnt[i] != 0)
						++mouseIntervalCnt[i];

					mouseStayCnt[i] = 0;
					mouseStay.rgbButtons[i] = 0;
				}
			}
		}
		else
		{
			//アクセス権を得る
			hr = pMouse->Acquire();
		}

		return hr;
	}

	void Mouse::SetDoubleInterval(DWORD _interval)
	{
		doubleInterval = _interval;
	}
}