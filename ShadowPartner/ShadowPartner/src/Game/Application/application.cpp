//==========================================================
// 概要  :アプリケーション
// Author:Itsuki Namito
// Copyright(c) Utsurugi.All right reserved.
//==========================================================
#include "application.h"
#include "../../Base/System/scene_manager.h"

#include "../../Base/Time/time.h"

namespace shadowpartner
{

//**********************************************************
// マクロ
//**********************************************************
#ifndef WINDOW_CLASSNAME
#define WINDOW_CLASSNAME "ShadowPartner"
#endif

	//**********************************************************
	// 定数
	//**********************************************************
	const int SCREEN_WIDTH = 1920;
	const int SCREEN_HEIGHT = 1080;

	const D3DCOLOR BACKGROUND_COLOR = D3DCOLOR_RGBA(255, 255, 255, 255);

	//**********************************************************
	// Static
	//**********************************************************
	Application *Application::instance_ = nullptr;

	Application *Application::Instance()
	{
		if (instance_ == nullptr)
		{
			instance_ = new Application();
		}

		return instance_;
	}

	// コンストラクタ
	Application::Application()
		:h_instance_(nullptr)
		,h_wnd_(nullptr)
		,d3d(nullptr)
		,device(nullptr)
	{
	}

	// デストラクタ
	Application::~Application()
	{
		if (instance_ != nullptr)
		{
			delete instance_;
			instance_ = nullptr;
		}
	}

	//**********************************************************
	// メソッド
	//**********************************************************

	//==========================================================
	// 概要  :アプリケーションを実行する
	//==========================================================
	void Application::Run()
	{
		if (FAILED(InitWindow()))
		{
			return;
		}

		if (FAILED(InitDirect3D()))
		{
			return;
		}

		MainLoop();

		UninitDirect3D();
		UninitWindow();

		// ウィンドウクラスの登録を解除
		UnregisterClass(WINDOW_CLASSNAME, h_instance_);

		// 終了処理

		Uninit();

		timeEndPeriod(1);				// 分解能を戻す
	}

	//==========================================================
	// 概要  :ゲームのメインループを回す
	//==========================================================
	int Application::MainLoop()
	{
		MSG msg;

		// メッセージループ
		while (1)
		{
			if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
			{
				if (msg.message == WM_QUIT)
				{	// PostQuitMessage()が呼ばれたらループ終了
					break;
				}
				else
				{
					// メッセージの翻訳と送出
					TranslateMessage(&msg);
					DispatchMessage(&msg);
				}
			}
			else
			{
				Time::Instance()->Update();	// タイマーだけ更新

				if (Time::Instance()->CheckUpdate())
				{
					Update();
					Draw();
				}
			}
		}

		return (int)msg.wParam;
	}

	//==========================================================
	// 概要  :メッセージプロシージャ。
	//==========================================================
	LRESULT CALLBACK Application::MsgProc(HWND h_wnd, UINT u_msg, WPARAM w_param, LPARAM l_param)
	{
		switch (u_msg)
		{
		case WM_DESTROY:
			PostQuitMessage(0);
			break;

		case WM_COMMAND:
		{

		}

		case WM_KEYDOWN:
		{
			switch (w_param)
			{
			case VK_ESCAPE:
			{
				DestroyWindow(h_wnd);	// 終了
			}
			break;

			case VK_F1:
			{
				// F1キーを押したときの動作
			}
			break;

			case VK_F2:
			{
				// F2キーを押したときの動作
			}
			break;

			default:
				break;
			}
		}
		break;

		default:
			break;
		}

		return DefWindowProc(h_wnd, u_msg, w_param, l_param);
	}

	//==========================================================
	// 概要  :初期化処理
	//==========================================================
	HRESULT Application::Init()
	{

		return S_OK;
	}

	//==========================================================
	// 概要  : ウィンドウの初期化を行う
	// 戻り値: 初期化の結果
	// 説明  : ウィンドウの設定、登録、作成、表示を行う
	//==========================================================
	HRESULT Application::InitWindow()
	{
		// インスタンスハンドルを取得.
		h_instance_ = GetModuleHandle(nullptr);
		if (!h_instance_)
		{
			return E_FAIL;
		}

		// 拡張ウィンドウクラスの設定.
		WNDCLASSEX wc =
		{
			sizeof(WNDCLASSEX),
			CS_CLASSDC,
			instance_->MsgProc,
			0,
			0,
			h_instance_,
			NULL,
			LoadCursor(NULL, IDC_ARROW),
			(HBRUSH)(COLOR_WINDOW + 1),
			NULL,
			WINDOW_CLASSNAME,
			NULL
		};

		// ウィンドウクラスの登録
		RegisterClassEx(&wc);

		// ウィンドウの作成
		h_wnd_ = CreateWindowEx
			(
				0,
				WINDOW_CLASSNAME,
				"Shadow Partner",
				WS_OVERLAPPEDWINDOW,
				CW_USEDEFAULT,
				CW_USEDEFAULT,
				SCREEN_WIDTH + GetSystemMetrics(SM_CXDLGFRAME) * 2,
				SCREEN_HEIGHT + GetSystemMetrics(SM_CYDLGFRAME) * 2 + GetSystemMetrics(SM_CYCAPTION),
				NULL,
				NULL,
				h_instance_,
				NULL
				);

		if (!h_wnd_)
		{
			return E_FAIL;
		}

		// ウィンドウを表示
		ShowWindow(h_wnd_, SW_SHOWNORMAL);
		UpdateWindow(h_wnd_);

		// 正常終了.
		return S_OK;
	}

	//==========================================================
	// 概要  ： Direct3Dの初期化を行う
	// 戻り値： 初期化の結果
	// 説明  ： Direct3Dオブジェクトとデバイスオブジェクトの作成、設定を行う
	//==========================================================
	HRESULT Application::InitDirect3D(void)
	{
		D3DPRESENT_PARAMETERS d3dpp;
		D3DDISPLAYMODE d3ddm;

		// Direct3Dオブジェクトの作成
		d3d = Direct3DCreate9(D3D_SDK_VERSION);
		if (d3d == NULL)
		{
			return E_FAIL;
		}

		// 現在のディスプレイモードを取得
		if (FAILED(d3d->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
		{
			return E_FAIL;
		}

		// デバイスのプレゼンテーションパラメータの設定
		ZeroMemory(&d3dpp, sizeof(d3dpp));			// ワークをゼロクリア
		d3dpp.BackBufferCount = 1;					// バックバッファの数
		d3dpp.BackBufferWidth = SCREEN_WIDTH;		// ゲーム画面サイズ(幅)
		d3dpp.BackBufferHeight = SCREEN_HEIGHT;		// ゲーム画面サイズ(高さ)
		d3dpp.BackBufferFormat = d3ddm.Format;		// バックバッファフォーマットはディスプレイモードに合わせて使う
		d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;	// 映像信号に同期してフリップする
		d3dpp.Windowed = TRUE;						// ウィンドウモード
		d3dpp.EnableAutoDepthStencil = TRUE;		// デプスバッファ（Ｚバッファ）とステンシルバッファを作成
		d3dpp.AutoDepthStencilFormat = D3DFMT_D16;	// デプスバッファとして16bitを使う

		if (TRUE)
		{// ウィンドウモード
			d3dpp.FullScreen_RefreshRateInHz = 0;						// リフレッシュレート
			d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;	// インターバル
		}
		else
		{// フルスクリーンモード
			d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;	// リフレッシュレート
			d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;	// インターバル
		}

		// デバイスオブジェクトの生成
		// [デバイス作成制御]<描画>と<頂点処理>をハードウェアで行なう
		if (FAILED(d3d->CreateDevice(D3DADAPTER_DEFAULT,
			D3DDEVTYPE_HAL,
			h_wnd_,
			D3DCREATE_HARDWARE_VERTEXPROCESSING,
			&d3dpp, &device)))
		{
			// 上記の設定が失敗したら
			// [デバイス作成制御]<描画>をハードウェアで行い、<頂点処理>はCPUで行なう
			if (FAILED(d3d->CreateDevice(D3DADAPTER_DEFAULT,
				D3DDEVTYPE_HAL,
				h_wnd_,
				D3DCREATE_SOFTWARE_VERTEXPROCESSING,
				&d3dpp, &device)))
			{
				// 上記の設定が失敗したら
				// [デバイス作成制御]<描画>と<頂点処理>をCPUで行なう
				if (FAILED(d3d->CreateDevice(D3DADAPTER_DEFAULT,
					D3DDEVTYPE_REF,
					h_wnd_,
					D3DCREATE_SOFTWARE_VERTEXPROCESSING,
					&d3dpp, &device)))
				{
					// 初期化失敗
					return E_FAIL;
				}
			}
		}

		// レンダーステートパラメータの設定
		device->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);				// 裏面をカリング
		device->SetRenderState(D3DRS_ZENABLE, TRUE);						// Zバッファを使用
		device->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);				// αブレンドを行う
		device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);		// αソースカラーの指定
		device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);	// αデスティネーションカラーの指定

		device->SetRenderState(D3DRS_LIGHTING, TRUE);					//ライト使う
		device->SetRenderState(D3DRS_AMBIENT, 0xff050505);				//環境光の設定、第二引数はD3DCOLOR

																		// サンプラーステートパラメータの設定
		device->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);	// テクスチャアドレッシング方法(U値)を設定
		device->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);	// テクスチャアドレッシング方法(V値)を設定
		device->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);	// テクスチャ縮小フィルタモードを設定
		device->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);	// テクスチャ拡大フィルタモードを設定

																		// テクスチャステージステートの設定
		device->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);	// アルファブレンディング処理を設定
		device->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);	// 最初のアルファ引数
		device->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);	// ２番目のアルファ引数

		Time::Instance();

		if (FAILED(Init()))
		{
			return E_FAIL;
		}

		return S_OK;
	}

	//==========================================================
	// 概要  :終了処理
	//==========================================================
	void Application::Uninit()
	{

	}

	//==========================================================
	// 概要  :ウィンドウの終了処理を行う。
	//==========================================================
	void Application::UninitWindow()
	{
		// ウィンドウクラスの登録を解除
		if (h_instance_)
		{
			UnregisterClassA(WINDOW_CLASSNAME, h_instance_);
		}
		h_instance_ = nullptr;
		h_wnd_ = nullptr;
	}

	//==========================================================
	// 概要  :Direct3Dの終了処理を行う
	//==========================================================
	void Application::UninitDirect3D()
	{
		Uninit();

		// Direct3Dの解放
		if (device != NULL)
		{// デバイスオブジェクトの開放
			device->Release();
			device = NULL;
		}

		if (d3d != NULL)
		{// Direct3Dオブジェクトの開放
			d3d->Release();
			d3d = NULL;
		}
	}

	//==========================================================
	// 概要  :更新処理を行う。
	//==========================================================
	void Application::Update()
	{
		SceneManager::Instance()->Update();
	}

	//==========================================================
	// 概要  :描画処理を行う。
	//==========================================================
	void Application::Draw()
	{
		// バックバッファ＆Ｚバッファのクリア
		device->Clear(0, NULL, (D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER), BACKGROUND_COLOR, 1.0f, 0);

		// 描画の開始
		if (SUCCEEDED(device->BeginScene()))
		{
			SceneManager::Instance()->Draw();

			// 描画の終了
			device->EndScene();
		}

		// バックバッファとフロントバッファの入れ替え
		device->Present(NULL, NULL, NULL, NULL);
	}


}
