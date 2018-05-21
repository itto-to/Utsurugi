//==========================================================
// 概要  :キーボード処理
// Author:Itsuki Namito
// Copyright(c) Utsurugi.All right reserved.
//==========================================================
#include "keyboard.h"
#include "Input.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

namespace input
{
	//=============================================================================
	// キーボードの初期化処理
	//=============================================================================
	HRESULT Keyboard::Init(HINSTANCE hInst, HWND hWnd, LPDIRECTINPUT8 pDInput)
	{
		HRESULT hr;

		// デバイスオブジェクトを作成
		hr = pDInput->CreateDevice(GUID_SysKeyboard, &pKeyboard, NULL);
		if (FAILED(hr) || pKeyboard == NULL)
		{
			MessageBox(hWnd, "キーボードがありません", "警告！", MB_ICONWARNING);
			return hr;
		}

		// データフォーマットを設定
		hr = pKeyboard->SetDataFormat(&c_dfDIKeyboard);
		if (FAILED(hr))
		{
			MessageBox(hWnd, "キーボードのデータフォーマットを設定できませんでした。", "警告！", MB_ICONWARNING);
			return hr;
		}

		// 協調モードを設定（フォアグラウンド＆非排他モード）
		hr = pKeyboard->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE));
		if (FAILED(hr))
		{
			MessageBox(hWnd, "キーボードの協調モードを設定できませんでした。", "警告！", MB_ICONWARNING);
			return hr;
		}

		// キーボードへのアクセス権を獲得(入力制御開始)
		pKeyboard->Acquire();

		doubleInterval = INPUT_DOUBLE_DEFAULT_INTERVAL;

		return S_OK;
	}

	//=============================================================================
	// キーボードの終了処理
	//=============================================================================
	void Keyboard::Uninit(void)
	{
		if (pKeyboard)
		{
			pKeyboard->Unacquire();
			// デバイスオブジェクトの開放
			pKeyboard->Release();
			pKeyboard = NULL;
		}
	}

	//=============================================================================
	// キーボードの更新処理
	//=============================================================================
	HRESULT Keyboard::Update(void)
	{
		HRESULT hr;
		BYTE aCurrentKeyState[NUM_KEY_MAX];

		// デバイスからデータを取得
		hr = pKeyboard->GetDeviceState(sizeof(aCurrentKeyState), aCurrentKeyState);
		if (SUCCEEDED(hr))
		{
			for (int nCntKey = 0; nCntKey < NUM_KEY_MAX; nCntKey++)
			{
				// ^はXOR
				keyStateDown[nCntKey] = (keyState[nCntKey] ^ aCurrentKeyState[nCntKey]) & aCurrentKeyState[nCntKey];//状態が変化した、かつ押された
				keyStateUp[nCntKey] = (keyState[nCntKey] ^ aCurrentKeyState[nCntKey]) & ~aCurrentKeyState[nCntKey];	//状態が変化した、かつ離された
				keyStateStay[nCntKey] = keyStateDown[nCntKey];	//一時的に前回押されたかどうかをいれる
				keyStateDouble[nCntKey] = 0;

				//キーが押されている場合
				if (keyState[nCntKey])
				{
					//そのキーが押されているならカウントし、20以上なら1を入れる
					keyStateStayCnt[nCntKey]++;
					if (keyStateStayCnt[nCntKey] >= 20)
					{
						keyStateStay[nCntKey] = aCurrentKeyState[nCntKey];
					}

					if (keyStateIntervalCnt[nCntKey] >= doubleInterval)
						keyStateDouble[nCntKey] = aCurrentKeyState[nCntKey];
					keyStateIntervalCnt[nCntKey] = 0;
				}
				else
				{
					if (keyStateIntervalCnt[nCntKey] != 0)
					{
						++keyStateIntervalCnt[nCntKey];
					}
					else if (keyStateStayCnt[nCntKey] != 0)
					{
						++keyStateIntervalCnt[nCntKey];	//もし離した瞬間ならカウント
					}
					//キーが押されてないならカウンタを0にしてやり直し
					keyStateStayCnt[nCntKey] = 0;
					keyStateStay[nCntKey] = 0;
				}

				keyState[nCntKey] = aCurrentKeyState[nCntKey];
			}
		}
		else
		{
			// キーボードへのアクセス権を取得
			pKeyboard->Acquire();
		}

		return S_OK;
	}

	//=============================================================================
	// ダブルクリックの感覚を設定
	//=============================================================================
	void Keyboard::SetDoubleInterval(DWORD _interval)
	{
		doubleInterval = _interval;
	}
}