//==========================================================
// 概要  :時間処理
// Author:Itsuki Namito
// Copyright(c) Utsurugi.All right reserved.
//==========================================================

#ifndef _BASE_TIME_TIME_H_
#define _BASE_TIME_TIME_H_

namespace shadowpartner
{

//**********************************************************
// インクルードファイル
//**********************************************************
#include <windows.h>

	//==========================================================
	// 概要  :時間関係の処理を行うクラス
	//==========================================================
	class Time
	{
	public:
		// variables
		DWORD start_time_;			// タイマーの計測開始時間
		DWORD last_exe_time_;		// 1つ前のUpdateを開始した時間
		DWORD current_time_;		// 現在の時間
		DWORD delta_time_;			// 1つ前のUpdateにかかった時間
		DWORD unscaled_delta_time_;	// time_scale_に依存しない最後のフレームからの差分
		DWORD current_fps_;			// 現在のFPS
		DWORD app_time_;			// ゲームの起動時間

		// methods
		static Time *Instance();
		void Update();				// 
		bool CheckUpdate();			// Updateするか判定する

		// Accessor
		void SetFps(int fps);
		int GetFps();
		void SetTimeScale(float time_scale);
		float GetTimeScale();

	protected:
		Time();
		~Time();

		// methods

	private:
		// variables
		static Time *instance_;

		int frame_count_;			// 実際のFPSを計測
		DWORD last_fps_time_;		// 最後にFPSの計測を更新した時間
		int fps_;					// FPSの目標値
		DWORD time_scale_;			// 時間の圧縮率


		// methods
		// 利用禁止
		Time(const Time &t) {};
		Time &operator=(const Time &) { return *this; };

	};
}
#endif