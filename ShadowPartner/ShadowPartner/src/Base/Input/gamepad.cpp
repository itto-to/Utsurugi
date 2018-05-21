//==========================================================
// 概要  :ゲームパッド処理
// Author:Itsuki Namito
// Copyright(c) Utsurugi.All right reserved.
//==========================================================
#include "gamepad.h"
#include "Input.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define DEADZONE (2500)
#define RANGE_MAX (1000)
#define RANGE_MIN (-1000)

namespace input
{
	//=============================================================================
	// ゲームパッドの初期化処理
	//=============================================================================
	HRESULT Gamepad::Init(HINSTANCE hInst, HWND hWnd, LPDIRECTINPUT8 pDInput)
	{
		HRESULT hr;

		hr = pGamepad->SetDataFormat(&c_dfDIJoystick2);
		if (FAILED(hr))
		{
			MessageBox(hWnd, "ゲームパッドのデータフォーマットを設定できませんでした。", "警告！", MB_ICONWARNING);
			return hr;
		}

		// 協調モードを設定（フォアグラウンド＆非排他モード）
		hr = pGamepad->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE));
		if (FAILED(hr))
		{
			MessageBox(hWnd, "ゲームパッドの協調モードを設定できませんでした。", "警告！", MB_ICONWARNING);
			return hr;
		}

		// 軸の値域を設定
		// X軸、Y軸のそれぞれについて、オブジェクトを報告可能な地域をセットする
		// (max - min)は、最大10000。(max - min) / 2が中央値
		DIPROPRANGE diprg;
		ZeroMemory(&diprg, sizeof(diprg));
		diprg.diph.dwSize = sizeof(diprg);
		diprg.diph.dwHeaderSize = sizeof(diprg.diph);
		diprg.diph.dwHow = DIPH_BYOFFSET;
		diprg.lMin = RANGE_MIN;
		diprg.lMax = RANGE_MAX;

		// X軸の範囲を設定
		diprg.diph.dwObj = DIJOFS_X;
		pGamepad->SetProperty(DIPROP_RANGE, &diprg.diph);
		// Y軸の範囲を設定
		diprg.diph.dwObj = DIJOFS_Y;
		pGamepad->SetProperty(DIPROP_RANGE, &diprg.diph);

		// 各軸ごとに無効ゾーン値を設定する。
		DIPROPDWORD dipdw;
		dipdw.diph.dwSize = sizeof(DIPROPDWORD);
		dipdw.diph.dwHeaderSize = sizeof(dipdw.diph);
		dipdw.diph.dwHow = DIPH_BYOFFSET;
		dipdw.dwData = DEADZONE;

		// X軸の無効ゾーンを設定
		dipdw.diph.dwObj = DIJOFS_X;
		pGamepad->SetProperty(DIPROP_DEADZONE, &dipdw.diph);
		// Y軸の無効ゾーンを設定
		dipdw.diph.dwObj = DIJOFS_Y;
		pGamepad->SetProperty(DIPROP_DEADZONE, &dipdw.diph);

		// ゲームパッドへのアクセス権を獲得(入力制御開始)
		pGamepad->Acquire();

		doubleInterval = INPUT_DOUBLE_DEFAULT_INTERVAL;

		return S_OK;
	}

	//=============================================================================
	// ゲームパッドの終了処理
	//=============================================================================
	void Gamepad::Uninit(void)
	{
		if (pGamepad)
		{
			pGamepad->Unacquire();

			// デバイスオブジェクトの開放
			pGamepad->Release();
			pGamepad = NULL;
		}
	}

	//=============================================================================
	// ゲームパッドの更新処理
	//=============================================================================
	HRESULT Gamepad::Update(void)
	{
		HRESULT hr;
		DIJOYSTATE2 oldPadState = padState;

		hr = pGamepad->Poll();
		if (FAILED(hr))
		{
			hr = pGamepad->Acquire();
			while (hr == DIERR_INPUTLOST)
				hr = pGamepad->Acquire();
		}

		// デバイスからデータを取得
		hr = pGamepad->GetDeviceState(sizeof(DIJOYSTATE2), &padState);
		if (hr == DIERR_INPUTLOST || hr == DIERR_NOTACQUIRED)
		{
			hr = pGamepad->Acquire();
			while (hr == DIERR_INPUTLOST)
			{
				hr = pGamepad->Acquire();
			}
		}

		// 十字キーの入力を使われてなかったところに入れちゃえ
		if (padState.rgdwPOV[0] == 0)padState.rgbButtons[12] = 0x80;
		if (padState.rgdwPOV[0] == 4500)
		{
			padState.rgbButtons[12] = 0x80; padState.rgbButtons[13] = 0x80;
		}
		if (padState.rgdwPOV[0] == 9000)padState.rgbButtons[13] = 0x80;
		if (padState.rgdwPOV[0] == 13500)
		{
			padState.rgbButtons[13] = 0x80; padState.rgbButtons[14] = 0x80;
		}
		if (padState.rgdwPOV[0] == 18000)padState.rgbButtons[14] = 0x80;
		if (padState.rgdwPOV[0] == 22500)
		{
			padState.rgbButtons[14] = 0x80; padState.rgbButtons[15] = 0x80;
		}
		if (padState.rgdwPOV[0] == 27000)padState.rgbButtons[15] = 0x80;
		if (padState.rgdwPOV[0] == 31500)
		{
			padState.rgbButtons[12] = 0x80; padState.rgbButtons[15] = 0x80;
		}

		for (int i = 0; i < 128; ++i)
		{
			padDown.rgbButtons[i] = ((oldPadState.rgbButtons[i] ^ padState.rgbButtons[i]) & padState.rgbButtons[i]);
			padStay.rgbButtons[i] = padDown.rgbButtons[i];
			padDouble.rgbButtons[i] = 0;
			padUp.rgbButtons[i] = ((oldPadState.rgbButtons[i] ^ padState.rgbButtons[i]) & ~padState.rgbButtons[i]);

			if (padDown.rgbButtons[i])
			{
				padStayCount[i]++;
				if (padStayCount[i] >= 20)
				{
					padStay.rgbButtons[i] = padState.rgbButtons[i];
				}

				if (padIntervalCount[i] >= doubleInterval)
					padDouble.rgbButtons[i] = padState.rgbButtons[i];

				padIntervalCount[i] = 0;
			}
			else
			{
				if (padIntervalCount[i] != 0)
				{
					++padIntervalCount[i];
				}
				else if (padStayCount[i] != 0)
				{
					++padIntervalCount[i];
				}

				padStayCount[i] = 0;
				padStay.rgbButtons[i] = 0;
			}

		}

		//ImGui::SetNextWindowPos(ImVec2(20, 20));
		//ImGui::SetNextWindowSize(ImVec2(200, 560));
		//ImGui::Begin("Input Check");

		//ImGui::Text("lX:%d", padState.lX);
		//ImGui::Text("lY:%d", padState.lY);
		//ImGui::Text("lZ:%d", padState.lZ);
		//ImGui::Text("lRx:%d", padState.lRx);
		//ImGui::Text("lRy:%d", padState.lRy);
		//ImGui::Text("lRz:%d", padState.lRz);
		//ImGui::Text("lARx:%d", padState.lARx);
		//ImGui::Text("lARy:%d", padState.lARy);
		//ImGui::Text("lARz:%d", padState.lARz);
		//ImGui::Text("lVX:%d", padState.lVX);
		//ImGui::Text("lVY:%d", padState.lVY);
		//ImGui::Text("lVZ:%d", padState.lVZ);
		//ImGui::Text("lAX:%d", padState.lAX);
		//ImGui::Text("lAY:%d", padState.lAY);
		//ImGui::Text("lAZ:%d", padState.lAZ);
		//ImGui::Text("lFRx:%d", padState.lFRx);
		//ImGui::Text("lFRy:%d", padState.lFRy);
		//ImGui::Text("lFRz:%d", padState.lFRz);
		//ImGui::Text("lFX:%d", padState.lFX);
		//ImGui::Text("lFY:%d", padState.lFY);
		//ImGui::Text("lFZ:%d", padState.lFZ);
		//ImGui::Text("lVRx:%d", padState.lVRx);
		//ImGui::Text("lVRy:%d", padState.lVRy);
		//ImGui::Text("lVRz:%d", padState.lVRz);
		//ImGui::Text("Pov0:%d", padState.rgdwPOV[0]);
		//ImGui::Text("Pov1:%d", padState.rgdwPOV[1]);
		//ImGui::Text("Pov2:%d", padState.rgdwPOV[2]);
		//ImGui::Text("Pov3:%d", padState.rgdwPOV[3]);

		//ImGui::End();
		return S_OK;
	}

	//=============================================================================
	// ゲームパッドの垂直成分の入力を取得
	//=============================================================================
	void Gamepad::SetDoubleInterval(DWORD _interval)
	{
		doubleInterval = _interval;
	}
}