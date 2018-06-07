//==========================================================
// 概要  :テクスチャクラス
// Author:Itsuki Namito
// Copyright(c) Utsurugi.All right reserved.
//==========================================================
#include "../../Game/Application/application.h"
#include "texture.h"

#define SPRITE_EFFECT "Shader/sprite_shader.hlsl"

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
	{

	}

	Texture::Texture(const char *file_name)
		:tex_(nullptr)
		,width_(10.0f)
		,height_(10.0f)
	{
		if (FAILED(D3DXCreateTextureFromFile(Application::Instance()->device, (LPCSTR)file_name, &tex_)))
		{
			MessageBox(NULL, "テクスチャーの読み込みに失敗しました。", "警告！", MB_ICONWARNING);
		}

		D3DXCreateEffectFromFile(
			Application::Instance()->device,
			SPRITE_EFFECT,
			NULL,
			NULL,
			D3DXSHADER_DEBUG,
			NULL,
			&effect,
			NULL
			);
	}

	Texture::~Texture()
	{

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

		UINT num_pass;

		//effect->Begin(&num_pass,0);
		//effect->BeginPass(0);

		device->SetTexture(0, tex_);
		device->SetFVF(FVF_VERTEX_2D);
		device->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, vertices, sizeof(Vertex2D));

		//effect->EndPass();
		//effect->End();
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
}
