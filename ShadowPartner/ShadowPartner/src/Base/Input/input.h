//==========================================================
// 概要  :入力処理
// Author:Itsuki Namito
// Copyright(c) Utsurugi.All right reserved.
//==========================================================
#ifndef _BASE_INPUT_INPUT_H_
#define _BASE_INPUT_INPUT_H_

#include <windows.h>
#include <d3dx9.h>
#define DIRECTINPUT_VERSION (0x0800)
#include <dinput.h>
#include "keyboard.h"
#include "mouse.h"
#include "gamepad.h"

#include <stdio.h>

#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")
#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define INPUT_DOUBLE_DEFAULT_INTERVAL (20)
#define GAMEPAD_MAX (1)

namespace input
{
	enum InputButton
	{
		Action,		//アクション（Z,〇）
		Skill,		//スキル（C,△）
		Attack,		//アタック（V,□）
		Jump,		//ジャンプボタン（SPACE,×）
		Cancel,		//キャンセルボタン（X,×）
		Up,			//十字上、上矢印
		Right,		//十字右、右矢印
		Down,		//十字下、下矢印
		Left,		//十字左、左矢印
		R1,			//R1ボタン
		R2,			//R2ボタン
		R3,			//R3ボタン
		L1,			//L1ボタン
		L2,			//L2ボタン
		L3,			//L3ボタン
		Start,		//スタートボタン
		Select,		//セレクトボタン
		Function1,
		Function2,
		Function3,
		Function4,
		ButtonCount	//ボタンの数
	};

	enum InputAxis
	{
		Horizontal,			//水平成分-1～1
		Vertical,			//水力成分-1～1
		Fire1,				//
		Fire2,				//
		Fire3,				//
		MouseX,				//
		MouseY,				//
		MouseScrollWheel,	//
		RotateX,
		RotateY,

		AxisCount
	};

	//*****************************************************************************
	// Inputクラス
	//*****************************************************************************
	class Input
	{
	public:

		//コンストラクタ
		Input();
		~Input();//デストラクタ

		Keyboard keyboard;
		Mouse mouse;
		Gamepad gamepad[GAMEPAD_MAX];

		HRESULT Init(HINSTANCE hInst, HWND hWnd);
		void Uninit(void);
		void Update(void);

		//入力を取得
		static Input *Instance();
		bool GetButton(InputButton _button);
		bool GetButtonDown(InputButton _button);
		bool GetButtonStay(InputButton _button);
		bool GetButtonUp(InputButton _button);
		bool GetButtonDouble(InputButton _button);

		float GetAxis(InputAxis _axis);

		void SetDoubleInterval(DWORD _interval);

	private:
		static Input *instance_;

		LPDIRECTINPUT8 pInput;	// IDirectInput8インターフェースへのポインタ
		int padCount;

		//シングルトン
		Input(const Input &i) {}
		Input &operator=(const Input &) { return *this; }

		// Private Functions
		// 仮想ボタンのワーク
		BYTE	inputButtonState[InputButton::ButtonCount];			//仮想ボタンの押下状態を保持するワーク
		BYTE	inputButtonDown[InputButton::ButtonCount];			//仮想ボタンの押下状態を保持するワーク
		BYTE	inputButtonStay[InputButton::ButtonCount];			//仮想ボタンの押下状態を保持するワーク
		BYTE	inputButtonUp[InputButton::ButtonCount];			//仮想ボタンの押下状態を保持するワーク
		BYTE	inputButtonDouble[InputButton::ButtonCount];		//仮想ボタンの押下状態を保持するワーク

		// 仮想軸のワーク
		long	inputAxisValue[InputAxis::AxisCount];

		// Private Functions
		static bool CALLBACK SearchGamepadCallback(LPDIDEVICEINSTANCE lpddi, LPVOID);
		void UpdateButtons(void);	// 仮想ボタンの更新。長くなるので分ける
		void UpdateAxis(void);		// 仮想軸の更新。長くなるので分ける

		enum CheckState
		{
			Pushed,
			StateDown,
			StateStay,
			StateUp,
			StateDouble,
			StateMax
		};

		//=============================================================================
		// キーボードの入力を確認する
		//=============================================================================
		FORCEINLINE bool CheckKey(int _key, int _checkState)
		{
			switch (_checkState)
			{
			case CheckState::Pushed:
			{
				return keyboard.GetKey(_key);
			}
			break;

			case CheckState::StateDown:
			{
				return keyboard.GetKeyDown(_key);
			}
			break;

			case CheckState::StateStay:
			{
				return keyboard.GetKeyStay(_key);
			}
			break;

			case CheckState::StateUp:
			{
				return keyboard.GetKeyUp(_key);
			}
			break;

			case CheckState::StateDouble:
			{
				return keyboard.GetKeyDouble(_key);
			}
			break;

			default:
			{
				return false;
			}
			break;
			}

			return false;
		}

		//=============================================================================
		// マウスの入力を確認する
		//=============================================================================
		FORCEINLINE bool CheckMouse(MouseClick _click, int _checkState)
		{
			switch (_checkState)
			{
			case CheckState::Pushed:
			{
				return mouse.GetMouse(_click);
			}
			break;

			case CheckState::StateDown:
			{
				return mouse.GetMouseDown(_click);
			}
			break;

			case CheckState::StateStay:
			{
				return mouse.GetMouseStay(_click);
			}
			break;

			case CheckState::StateUp:
			{
				return mouse.GetMouseUp(_click);
			}
			break;

			case CheckState::StateDouble:
			{
				return mouse.GetMouseDouble(_click);
			}
			break;

			default:
			{
				return false;
			}
			break;
			}

			return false;
		}

		//=============================================================================
		// ゲームパッドの入力を確認する
		//=============================================================================
		FORCEINLINE bool CheckPad(int padNo, int _button, int _checkState)
		{
			switch (_checkState)
			{
			case CheckState::Pushed:
			{
				return gamepad[padNo].GetPadButton(_button);
			}
			break;

			case CheckState::StateDown:
			{
				return gamepad[padNo].GetPadDown(_button);
			}
			break;

			case CheckState::StateStay:
			{
				return gamepad[padNo].GetPadStay(_button);
			}
			break;

			case CheckState::StateUp:
			{
				return gamepad[padNo].GetPadUp(_button);
			}
			break;

			case CheckState::StateDouble:
			{
				return gamepad[padNo].GetPadDouble(_button);
			}
			break;

			default:
			{
				return false;
			}
			break;
			}

			return false;
		}

		//=============================================================================
		// 仮想ボタンの状態を満たしている
		//=============================================================================
		FORCEINLINE void MeetButton(InputButton _button, int state)
		{
			switch (state)
			{
			case CheckState::Pushed:
			{
				inputButtonState[_button] = 0x80;
			}
			break;

			case CheckState::StateDown:
			{
				inputButtonDown[_button] = 0x80;
			}
			break;

			case CheckState::StateStay:
			{
				inputButtonStay[_button] = 0x80;
			}
			break;

			case CheckState::StateUp:
			{
				inputButtonUp[_button] = 0x80;
			}
			break;

			case CheckState::StateDouble:
			{
				inputButtonDouble[_button] = 0x80;
			}
			break;

			default:
				break;
			}
		}

	};
}
#endif