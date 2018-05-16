//==========================================================
// 概要  :アプリケーション
// Author:Itsuki Namito
// Copyright(c) Utsurugi.All right reserved.
//==========================================================
#include "application.h"

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
