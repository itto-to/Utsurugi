//==========================================================
// 概要  :時間処理
// Author:Itsuki Namito
// Copyright(c) Utsurugi.All right reserved.
//==========================================================
#include "time.h"

namespace shadowpartner
{

	//**********************************************************
	// 定数
	//**********************************************************
	const int DEFAULT_FPS = 60;
	const float DEFAULT_TIME_SCALE = 1.0;
	const int UPDATE_FPS_COUNT = 1000;

	//**********************************************************
	// Static
	//**********************************************************
	Time *Time::instance_ = nullptr;

	Time *Time::Instance()
	{
		if (instance_ == nullptr)
		{
			instance_ = new Time();
		}

		return instance_;
	}

	// コンストラクタ
	Time::Time()
		:current_time_(0)
		,delta_time_(0)
		,unscaled_delta_time_(0)
		,current_fps_(0)
		,app_time_(0)
		,frame_count_(0)
		,fps_(DEFAULT_FPS)
		,time_scale_(DEFAULT_TIME_SCALE)
	{
		start_time_ =
			last_exe_time_ = 
			last_fps_time_ = timeGetTime();
	}

	//==========================================================
	// 概要  :タイマーの更新処理
	//==========================================================
	void Time::Update()
	{
		current_time_ = timeGetTime();
		app_time_ = current_time_ - start_time_;

		DWORD fps_count_delta = current_time_ - last_fps_time_; // 最後にFPSの計測をしてから経過した時間

		// FPSの計測
		if (fps_count_delta >= UPDATE_FPS_COUNT)
		{
			current_fps_ = frame_count_ * ((float)UPDATE_FPS_COUNT / (float)fps_count_delta);
			last_fps_time_ = current_time_;
			frame_count_ = 0;
		}
	}

	//==========================================================
	// 概要  :
	// 戻り値:
	//==========================================================
	bool Time::CheckUpdate()
	{
		DWORD elapsed_time = current_time_ - last_exe_time_; // 最後のUpdateからの経過時間
		//if(elapsed_time >= )
	}
}
