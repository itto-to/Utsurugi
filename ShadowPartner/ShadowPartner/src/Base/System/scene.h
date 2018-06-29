//==========================================================
// �T�v  :�V�[��
// Author:Itsuki Namito
// Copyright(c) Utsurugi.All right reserved.
//==========================================================

#ifndef _BASE_SYSTEM_SCENE_H_
#define _BASE_SYSTEM_SCENE_H_

//**********************************************************
// �C���N���[�h�t�@�C��
//**********************************************************
#include <windows.h>
#include <vector>
#include "../Element/gameobject.h"

namespace shadowpartner
{

	//==========================================================
	// �T�v  :�A
	//==========================================================
	class Scene
	{
	public:
		Scene();
		virtual ~Scene();
		
		// variables
		bool is_active_;
		std::vector<GameObject *> game_objects_;

		// methods
		virtual HRESULT Init();
		void UpdateScene();
		void DrawScene();

		void AddGameObject(GameObject *game_object);

	protected:

		// methods
		virtual void Uninit();
		virtual void Update();
		virtual void Draw();

		void DestroyImmediate(GameObject *destroy_object);


	private:
		// variables

		// methods
		// ���p�֎~
	};
}

#endif