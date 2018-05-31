////==========================================================
//// 概要  :ライトクラス
//// Author:Itsuki Namito
//// Copyright(c) Utsurugi.All right reserved.
////==========================================================
//
//#ifndef _BASE_LIGHT_LIGHT_H_
//#define _BASE_LIGHT_LIGHT_H_
//
////**********************************************************
//// インクルードファイル
////**********************************************************
//#include "../2D/texture.h"
//#include "../Element/component.h"
//
////==========================================================
//// マクロ
////==========================================================
//
//namespace shadowpartner
//{
//	//==========================================================
//	// 2Dオブジェクトの描画用クラス
//	//==========================================================
//	class Light:public Component
//	{
//	public:
//		Light();
//		~Light();
//
//		//variables
//
//		//methods
//		void SetColor(const D3DCOLOR &color);
//		void SetSize(const Vector2 &size);
//		void SetUvOffset(const Vector2 &offset);
//		void SetUvSize(const Vector2 &size);
//
//	protected:
//		void Draw();
//
//	private:
//		// variables
//		Texture texture_;
//		Vertex2D vertices_[NUM_TEXTURE_VERTEX];
//		Vector2 direction_;
//
//
//		// methods
//		void MakeVertex();
//		void SetVertex(const Vector3 &center, const float &width,
//			const float &height, const float &rotation);
//	};
//}
//
//#endif