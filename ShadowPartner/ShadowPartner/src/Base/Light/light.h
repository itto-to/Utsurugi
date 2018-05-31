////==========================================================
//// �T�v  :���C�g�N���X
//// Author:Itsuki Namito
//// Copyright(c) Utsurugi.All right reserved.
////==========================================================
//
//#ifndef _BASE_LIGHT_LIGHT_H_
//#define _BASE_LIGHT_LIGHT_H_
//
////**********************************************************
//// �C���N���[�h�t�@�C��
////**********************************************************
//#include "../2D/texture.h"
//#include "../Element/component.h"
//
////==========================================================
//// �}�N��
////==========================================================
//
//namespace shadowpartner
//{
//	//==========================================================
//	// 2D�I�u�W�F�N�g�̕`��p�N���X
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