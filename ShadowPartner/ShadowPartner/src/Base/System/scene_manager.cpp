//==========================================================
// �T�v  :�A�v���P�[�V����
// Author:Itsuki Namito
// Copyright(c) Utsurugi.All right reserved.
//==========================================================
#include "application.h"

namespace shadowpartner
{

//**********************************************************
// �}�N��
//**********************************************************
#ifndef WINDOW_CLASSNAME
#define WINDOW_CLASSNAME "ShadowPartner"
#endif

	//**********************************************************
	// �萔
	//**********************************************************
	const int SCREEN_WIDTH = 1920;
	const int SCREEN_HEIGHT = 1080;

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


}
