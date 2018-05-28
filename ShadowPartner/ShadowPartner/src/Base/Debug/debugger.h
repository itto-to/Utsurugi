//==========================================================
// 概要  :デバッグ用のクラス
// Author:Itsuki Namito
// Copyright(c) Utsurugi.All right reserved.
//==========================================================
#ifndef _BASE_DEBUG_DEBUGGER_H_
#define _BASE_DEBUG_DEBUGGER_H_

#ifdef _DEBUG

#include <stdarg.h>

#define DEBUG_LOG_STRING_LENGTH (60)	// 一行の文字の最大
#define DEBUG_STOP_WATCH_NUM (4)

namespace debug
{
	enum DebugView
	{
		Menu = 0,
		Performance,
		Visualization,
		DebugViewCount
	};

	struct StopWatch
	{
		long start_;
		long finish_;
	};

	class Debug
	{
	public:
		// methods
		// 適切なタイミングで要呼び出し
		static void Init();
		static void Draw();
		static void Uninit();
		static void Reset();

		static void Log(char *format, ...);
		static void ClaerLog();
		static void BreakPoint(bool condition = true);
		static void WarningBox(const char *text);

		static void SetView(DebugView view);

		static void StopWatchStart(int index = 0);
		static void StopWatchFinish(int index = 0);

	private:
		// variables
		static DebugView debug_view_;
		static char log_lines_[][DEBUG_LOG_STRING_LENGTH];
		static int log_line_count_;
		static int log_interval_count_;

		static bool draw_physics_wireframe;
		static bool draw_sprite_wireframe;

		static StopWatch stop_watches_[];

		// methods
		static void ShawHeader();

		static void ShawMenu();
		static void ShawPerformance();
		static void ShawVisualization();

		static void ShawLog();
		static void ShawFooter();
	};

	typedef void (PrintfFunc)(const char *msg);
}

#endif // end of _DEBUG

#endif // end of _BASE_DEBUG_DEBUGGER_H_