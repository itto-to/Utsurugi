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

	const int FPS_MIN = 1;
	const int FPS_MAX = 120;

	const float TIME_SCALE_MIN = 0.01f;
	const float TIME_SCALE_MAX = 5.0f;

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

	// デストラクタ
	Time::~Time()
	{
		if (instance_ != nullptr)
		{
			delete instance_;
			instance_ = nullptr;
		}
	}

	//==========================================================
	// 概要  :タイマーの更新処理。
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
	// 概要  :フレームの更新を行うか判定します。
	// 戻り値:更新するならtrue。しないならfalse。
	//==========================================================
	bool Time::CheckUpdate()
	{
		DWORD unscaled_elapsed_time = current_time_ - last_exe_time_;
		DWORD elapsed_time = unscaled_elapsed_time * time_scale_; // 最後のUpdateからの経過時間
		
		if (elapsed_time >= 1000 / fps_)
		{
			// Updateを行う
			++frame_count_;

			//フレーム間の時間を記録する。
			unscaled_delta_time_ = unscaled_elapsed_time;
			delta_time_ = elapsed_time;

			last_exe_time_ = current_time_;
			return true;
		}

		return false;
	}

	//==========================================================
	// 概要  :FPSを設定します。設定された範囲でクランプします。
	//==========================================================
	void Time::SetFps(int fps)
	{
		fps_ = (fps > FPS_MAX) ? FPS_MAX : (fps < FPS_MIN) ? FPS_MIN : fps;
	}

	//==========================================================
	// 概要  :FPSを取得します。
	//==========================================================
	int Time::GetFps()
	{
		return fps_;
	}

	//==========================================================
	// 概要  :時間の圧縮率を設定します。
	//        指定された範囲でクランプします。
	//==========================================================
	void Time::SetTimeScale(float time_scale)
	{
		time_scale_ = (time_scale > TIME_SCALE_MAX) ? TIME_SCALE_MAX :
			(time_scale < TIME_SCALE_MIN) ? TIME_SCALE_MIN : time_scale;
	}

	//==========================================================
	// 概要  :時間の圧縮率を取得します。
	//==========================================================
	float Time::GetTimeScale()
	{
		return time_scale_;
	}
}
