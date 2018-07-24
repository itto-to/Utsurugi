//==========================================================
// 概要  :テクスチャクラス
// Author:Itsuki Namito
// Copyright(c) Utsurugi.All right reserved.
//==========================================================
#include "../../Game/Application/application.h"
#include "texture.h"

namespace shadowpartner
{
	//**********************************************************
	// マクロ
	//**********************************************************

		//**********************************************************
		// 定数
		//**********************************************************

		// コンストラクタ
	Texture::Texture()
		:tex_(nullptr)
		,width_(10.0f)
		,height_(10.0f)
		,order_in_layer_(0)
	{
		if (tex_ != nullptr)
		{
			tex_->Release();
			tex_ = nullptr;
		}
	}

	Texture::Texture(const char *file_name)
		:tex_(nullptr)
		,width_(10.0f)
		,height_(10.0f)
		,order_in_layer_(0)
	{
		if (FAILED(D3DXCreateTextureFromFile(Application::Instance()->device, (LPCSTR)file_name, &tex_)))
		{
			MessageBox(NULL, "テクスチャーの読み込みに失敗しました。", "警告！", MB_ICONWARNING);
		}
	}

	Texture::~Texture()
	{
		if (tex_ != nullptr)
		{
			tex_->Release();
			tex_ = nullptr;
		}
	}

	// 画像読み込み
	void Texture::Load(const char *file_name)
	{
		if (FAILED(D3DXCreateTextureFromFile(Application::Instance()->device, (LPCSTR)file_name, &tex_)))
		{
			MessageBox(NULL, "テクスチャーの読み込みに失敗しました。", "警告！", MB_ICONWARNING);
		}
	}

	//==========================================================
	// 概要  :TriangleStripで描画します。
	// 引数  :頂点配列の先頭ポインタ
	//==========================================================
	void Texture::DrawTriangleStrip(const Vertex2D *vertices)
	{
		LPDIRECT3DDEVICE9 device = Application::Instance()->device;

		// ステンシルバッファ使う
		//device->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
		//device->SetRenderState(D3DRS_STENCILENABLE, TRUE);
		//device->SetRenderState(D3DRS_STENCILMASK, 0xff);				// ステンシルマスクの設定。データはそのまま使う。
		//device->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_GREATEREQUAL);	// 現在のステンシル値以上なら合格
		//device->SetRenderState(D3DRS_COLORWRITEENABLE, 0x00);			// バックバッファへRGB値を書き込まない

		//device->SetRenderState(D3DRS_STENCILFAIL, D3DSTENCILCAPS_REPLACE);
		//device->SetRenderState(D3DRS_STENCILZFAIL, D3DSTENCILCAPS_REPLACE);

		//device->SetRenderState(D3DRS_STENCILPASS,D3DSTENCILCAPS_REPLACE);	// テストに合格したら書き換える

		//device->SetRenderState(D3DRS_STENCILREF, order_in_layer_);		// ステンシルバッファの値と比較する参照値
		//device->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_LESSEQUAL);	// 比較関数　条件が真のときステンシルテスト合格
		//device->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILOP_KEEP);	// ステンシルテストに合格した場合ステンシル値には何もしない

		//device->SetRenderState(D3DRS_COLORWRITEENABLE,
		//	D3DCOLORWRITEENABLE_RED |
		//	D3DCOLORWRITEENABLE_GREEN |
		//	D3DCOLORWRITEENABLE_BLUE |
		//	D3DCOLORWRITEENABLE_ALPHA);


		//device->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
		// ステンシルバッファここまで

		// 描画処理
		device->SetTexture(0, tex_);
		device->SetFVF(FVF_VERTEX_2D);
		device->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, vertices, sizeof(Vertex2D));

		//device->SetRenderState(D3DRS_STENCILENABLE, FALSE);
	}

	//==========================================================
	// 概要  :TriangleFanで描画します。
	// 引数  :頂点配列の先頭ポインタ
	//==========================================================
	void Texture::DrawTriangleFan(const Vertex2D *vertices, UINT primitive_count)
	{
		LPDIRECT3DDEVICE9 device = Application::Instance()->device;

		device->SetTexture(0, tex_);
		device->SetFVF(FVF_VERTEX_2D);
		device->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, primitive_count, vertices, sizeof(Vertex2D));
	}

	//==========================================================
	// 概要  :テクスチャーのサイズを指定します。
	// 引数  :
	//	width :横幅
	//	height:縦幅
	//==========================================================
	void Texture::SetSize(float width, float height)
	{
		width_ = width;
		height_ = height;
	}

	//==========================================================
	// 概要  :テクスチャーの横幅を指定します。
	// 引数  :横幅
	//==========================================================
	void Texture::SetWidth(float width)
	{
		width_ = width;
	}

	//==========================================================
	// 概要  :テクスチャーの横幅を取得します。
	// 戻り値:横幅
	//==========================================================
	float Texture::GetWidth()
	{
		return width_;
	}

	//==========================================================
	// 概要  :テクスチャーの縦幅を指定します。
	// 引数  :縦幅
	//==========================================================
	void Texture::SetHeight(float height)
	{
		height_ = height;
	}

	//==========================================================
	// 概要  :テクスチャーの縦幅を取得します。
	// 戻り値:縦幅
	//==========================================================
	float Texture::GetHeight()
	{
		return height_;
	}

	void Texture::SetOrderInLayer(const int &layer)
	{
		order_in_layer_ = layer;
	}
}
