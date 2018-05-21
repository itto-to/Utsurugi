//==========================================================
// 概要  :入力処理
// Author:Itsuki Namito
// Copyright(c) Utsurugi.All right reserved.
//==========================================================
#include "input.h"


//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define INPUT_AXIS_MAX (1000)
#define INPUT_AXIS_MIN (-1000)
#define CLAMP(v,min,max) (v > max) ? max : (v < min) ? min : v

namespace input {
	//*****************************************************************************
	// インスタンス
	//*****************************************************************************
	Input *Input::instance_;

	Input *Input::Instance()
	{
		if (instance_ == nullptr)
		{
			instance_ = new Input();
		}

		return instance_;
	}

	//*****************************************************************************
	// コンストラクタ
	//*****************************************************************************
	Input::Input()
		: pInput(nullptr)
		, padCount(0)
	{
	}

	//**********************************************************
	// デストラクタ
	//**********************************************************
	Input::~Input()
	{
		if (instance_ != nullptr)
		{
			delete instance_;
			instance_ = nullptr;
		}
	}

	//=============================================================================
	// コールバック関数
	//=============================================================================
	bool CALLBACK Input::SearchGamepadCallback(LPDIDEVICEINSTANCE lpddi, LPVOID)
	{
		HRESULT hr;

		hr = instance_->pInput->CreateDevice(lpddi->guidInstance, &instance_->gamepad[instance_->padCount++].pGamepad, NULL);

		return DIENUM_CONTINUE;	//次のデバイスを列挙
	}

	//=============================================================================
	// 入力処理の初期化
	//=============================================================================
	HRESULT Input::Init(HINSTANCE hInst, HWND hWnd)
	{
		HRESULT hr;

		if (!pInput)
		{
			// DirectInputオブジェクトの作成
			hr = DirectInput8Create(hInst, DIRECTINPUT_VERSION,
				IID_IDirectInput8, (void**)&pInput, NULL);

			if (FAILED(hr))
			{
				MessageBox(hWnd, "DirectInputオブジェクトの作成に失敗しました", "警告！", MB_ICONWARNING);
				return hr;
			}
		}

		// 各入力装置初期化
		// キーボードの初期化
		hr = keyboard.Init(hInst, hWnd, pInput);
		if (FAILED(hr))
		{
			MessageBox(hWnd, "キーボードの初期化に失敗しました", "警告！", MB_ICONWARNING);
			return hr;
		}

		// マウスの初期化
		hr = mouse.Init(hInst, hWnd, pInput);
		if (FAILED(hr))
		{
			MessageBox(hWnd, "マウスの初期化に失敗しました", "警告！", MB_ICONWARNING);
			return hr;
		}

		// ゲームパッドの初期化
		padCount = 0;

		pInput->EnumDevices(DI8DEVCLASS_GAMECTRL, (LPDIENUMDEVICESCALLBACK)SearchGamepadCallback, NULL, DIEDFL_ATTACHEDONLY);

		for (int i = 0; i < padCount; ++i)
		{
			hr = gamepad[i].Init(hInst, hWnd, pInput);
			if (FAILED(hr))
			{
				MessageBox(hWnd, "ゲームパッドの初期化に失敗しました", "警告！", MB_ICONWARNING);
				return hr;
			}
		}

		return S_OK;
	}

	//=============================================================================
	// 入力処理の終了処理
	//=============================================================================
	void Input::Uninit(void)
	{
		// キーボードの終了処理
		keyboard.Uninit();

		// マウスの終了処理
		mouse.Uninit();

		// ゲームパッドの終了処理
		for (int i = 0; i < padCount; ++i)
		{
			gamepad[i].Uninit();
		}

		if (pInput)
		{// DirectInputオブジェクトの開放
			pInput->Release();
			pInput = NULL;
		}
	}

	//=============================================================================
	// 入力処理の更新処理
	//=============================================================================
	void Input::Update(void)
	{
		// キーボードの更新
		keyboard.Update();

		// マウスの更新
		mouse.Update();

		// ゲームパッドの更新
		for (int i = 0; i < padCount; ++i)
		{
			gamepad[i].Update();
		}

		UpdateButtons();
		UpdateAxis();
	}

	//=============================================================================
	// ダブルクリックの感覚を設定
	//=============================================================================
	void Input::SetDoubleInterval(DWORD _interval)
	{
		keyboard.SetDoubleInterval(_interval);
		mouse.SetDoubleInterval(_interval);

		for (int i = 0; i < padCount; ++i)
		{
			gamepad[i].SetDoubleInterval(_interval);
		}
	}

	//=============================================================================
	// 仮想ボタンを押している間
	//=============================================================================
	bool Input::GetButton(InputButton _button)
	{
		return (inputButtonState[_button] & 0x80) ? true : false;
	}

	//=============================================================================
	// 仮想ボタンを押した瞬間
	//=============================================================================
	bool Input::GetButtonDown(InputButton _button)
	{
		return (inputButtonDown[_button] & 0x80) ? true : false;
	}

	//=============================================================================
	// 仮想ボタンを押し続けている
	//カウンタ:0または2～19ならfalse,1または20以上ならtrue
	//=============================================================================
	bool Input::GetButtonStay(InputButton _button)
	{
		return (inputButtonStay[_button] & 0x80) ? true : false;
	}

	//=============================================================================
	// 仮想ボタンを離した瞬間
	//=============================================================================
	bool Input::GetButtonUp(InputButton _button)
	{
		return (inputButtonUp[_button] & 0x80) ? true : false;
	}

	//=============================================================================
	// 仮想ボタンを二度押しした瞬間
	//=============================================================================
	bool Input::GetButtonDouble(InputButton _button)
	{
		return (inputButtonDouble[_button] & 0x80) ? true : false;
	}

	//=============================================================================
	// 仮想軸の値を-1～1の範囲で返す
	//=============================================================================
	float Input::GetAxis(InputAxis _axis)
	{
		return CLAMP(((float)inputAxisValue[_axis] / 1000.0f), -1.0f, 1.0f);
	}

	//=============================================================================
	// 仮想ボタンの更新
	//=============================================================================
	void Input::UpdateButtons(void)
	{
		//いったんすべてのボタンをリセットする
		for (int i = 0; i < InputButton::ButtonCount; ++i)
		{
			inputButtonState[i] = 0;
			inputButtonDown[i] = 0;
			inputButtonStay[i] = 0;
			inputButtonUp[i] = 0;
			inputButtonDouble[i] = 0;
		}

		//指定した入力の組み合わせの内どれか一つでも条件を満たせば仮想ボタンもそれに合わせる
		for (int i = 0; i < CheckState::StateMax; ++i)
		{
			// アクションボタン(キーボードZとゲームパッド〇)
			if (CheckKey(DIK_Z, i) || CheckPad(0, 2, i))
			{
				MeetButton(InputButton::Action, i);
			}

			// スキルボタン(キーボードCとゲームパッド△)
			if (CheckKey(DIK_C, i) || CheckPad(0, 3, i))
			{
				MeetButton(InputButton::Skill, i);
			}

			// アタックボタン(キーボードVとゲームパッド□)
			if (CheckKey(DIK_V, i) || CheckPad(0, 0, i))
			{
				MeetButton(InputButton::Attack, i);
			}

			// ジャンプボタン(キーボードSpaceとゲームパッド×)
			if (CheckKey(DIK_SPACE, i) || CheckPad(0, 1, i))
			{
				MeetButton(InputButton::Jump, i);
			}

			// キャンセルボタン(キーボードXとゲームパッド×)
			if (CheckKey(DIK_X, i) || CheckPad(0, 1, i))
			{
				MeetButton(InputButton::Cancel, i);
			}

			// 上ボタン(キーボードWとキーボード↑とゲームパッド十字上)
			if (CheckKey(DIK_W, i) || CheckKey(DIK_UP, i) || CheckPad(0, 12, i))
			{
				MeetButton(InputButton::Up, i);
			}

			// 右ボタン(キーボードDとキーボード→とゲームパッド十字右)
			if (CheckKey(DIK_D, i) || CheckKey(DIK_RIGHT, i) || CheckPad(0, 13, i))
			{
				MeetButton(InputButton::Right, i);
			}

			// 下ボタン(キーボードSとキーボード↓とゲームパッド十字下)
			if (CheckKey(DIK_S, i) || CheckKey(DIK_DOWN, i) || CheckPad(0, 14, i))
			{
				MeetButton(InputButton::Down, i);
			}

			// 左ボタン(キーボードAとキーボード←とゲームパッド十字左)
			if (CheckKey(DIK_A, i) || CheckKey(DIK_LEFT, i) || CheckPad(0, 15, i))
			{
				MeetButton(InputButton::Left, i);
			}

			// R1ボタン(ゲームパッドR1)
			if (CheckPad(0, 5, i))
			{
				MeetButton(InputButton::R1, i);
			}

			// R2ボタン(ゲームパッドR2)
			if (CheckPad(0, 7, i))
			{
				MeetButton(InputButton::R2, i);
			}

			// R3ボタン(ゲームパッドR3)
			if (CheckPad(0, 11, i))
			{
				MeetButton(InputButton::R3, i);
			}

			// L1ボタン(ゲームパッドL1)
			if (CheckPad(0, 4, i))
			{
				MeetButton(InputButton::L1, i);
			}

			// L2ボタン(ゲームパッドL2)
			if (CheckPad(0, 6, i))
			{
				MeetButton(InputButton::L2, i);
			}

			// L3ボタン(ゲームパッドL3)
			if (CheckPad(0, 10, i))
			{
				MeetButton(InputButton::L3, i);
			}

			// スタートボタン(キーボード1とゲームパッドStart)
			if (CheckKey(DIK_1, i) || CheckPad(0, 9, i))
			{
				MeetButton(InputButton::Start, i);
			}

			// セレクトボタン(キーボード2とゲームパッドSelect)
			if (CheckKey(DIK_2, i) || CheckPad(0, 8, i))
			{
				MeetButton(InputButton::Select, i);
			}

			// 機能1ボタン(キーボードF1)
			if (CheckKey(DIK_F1, i))
			{
				MeetButton(InputButton::Function1, i);
			}

			// 機能2ボタン(キーボードF2)
			if (CheckKey(DIK_F2, i))
			{
				MeetButton(InputButton::Function2, i);
			}

			// 機能3ボタン(キーボードF3)
			if (CheckKey(DIK_F3, i))
			{
				MeetButton(InputButton::Function3, i);
			}

			// 機能4ボタン(キーボードF4)
			if (CheckKey(DIK_F4, i))
			{
				MeetButton(InputButton::Function4, i);
			}
		}

		// おしまい
	}

	//=============================================================================
	// 仮想軸の更新
	//=============================================================================
	void Input::UpdateAxis(void)
	{
		// 水平軸
		{
			long value = gamepad[0].GetPadHorizontal();

			if (keyboard.GetKey(DIK_A) || keyboard.GetKey(DIK_LEFT))
			{
				value -= 1000;
			}
			if (keyboard.GetKey(DIK_D) || keyboard.GetKey(DIK_RIGHT))
			{
				value += 1000;
			}

			inputAxisValue[InputAxis::Horizontal] = CLAMP(value, INPUT_AXIS_MIN, INPUT_AXIS_MAX);
		}

		// 垂直軸
		{
			long value = gamepad[0].GetPadVertical();

			if (keyboard.GetKey(DIK_S) || keyboard.GetKey(DIK_DOWN))
			{
				value -= 1000;
			}
			if (keyboard.GetKey(DIK_W) || keyboard.GetKey(DIK_UP))
			{
				value += 1000;
			}

			inputAxisValue[InputAxis::Vertical] = CLAMP(value, INPUT_AXIS_MIN, INPUT_AXIS_MAX);
		}

		// Fire1
		{
			long value = 0;

			if (mouse.GetMouseDown(MouseClick::MouseLeft))
			{
				value += 1000;
			}

			inputAxisValue[InputAxis::Fire1] = CLAMP(value, INPUT_AXIS_MIN, INPUT_AXIS_MAX);
		}

		// Fire2
		{
			long value = 0;

			if (mouse.GetMouseDown(MouseClick::MouseRight))
			{
				value += 1000;
			}

			inputAxisValue[InputAxis::Fire2] = CLAMP(value, INPUT_AXIS_MIN, INPUT_AXIS_MAX);
		}

		// Fire3
		{
			long value = 0;

			if (mouse.GetMouseDown(MouseClick::MouseCenter))
			{
				value += 1000;
			}

			inputAxisValue[InputAxis::Fire3] = CLAMP(value, INPUT_AXIS_MIN, INPUT_AXIS_MAX);
		}

		// MouseX
		{
			long value = mouse.GetMouseX();

			inputAxisValue[InputAxis::MouseX] = CLAMP(value, INPUT_AXIS_MIN, INPUT_AXIS_MAX);
		}

		// MouseY
		{
			long value = mouse.GetMouseY();

			inputAxisValue[InputAxis::MouseY] = CLAMP(value, INPUT_AXIS_MIN, INPUT_AXIS_MAX);
		}

		// MouseScrollWheel
		{
			long value = mouse.GetMouseWheel();

			inputAxisValue[InputAxis::MouseScrollWheel] = CLAMP(value, INPUT_AXIS_MIN, INPUT_AXIS_MAX);
		}

		// RotateX
		{
			long value = gamepad[0].GetPadRotateX();

			inputAxisValue[InputAxis::RotateX] = CLAMP(value, INPUT_AXIS_MIN, INPUT_AXIS_MAX);
		}

		// RotateX
		{
			long value = gamepad[0].GetPadRotateY();

			inputAxisValue[InputAxis::RotateY] = CLAMP(value, INPUT_AXIS_MIN, INPUT_AXIS_MAX);
		}

		// おしまい
	}
}