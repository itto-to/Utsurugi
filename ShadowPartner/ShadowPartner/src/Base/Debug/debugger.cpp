//==========================================================
// 概要  :デバッグ用のクラス
// Author:Itsuki Namito
// Copyright(c) Utsurugi.All right reserved.
//==========================================================

#include "debugger.h"
#include <stdio.h>
#include <stdarg.h>
#include <signal.h>

#include "../Input/input.h"
#include "../Time/time.h"

#ifdef _WIN32
#include <Windows.h>
#endif

#include <crtdbg.h>

#define DEBUG_UPDATE_INTERVAL (6)
#define DEBUG_LOG_LINE_MAX (5)			// 同時に表示できるログの数

#define DEBUG_HEADEER_LINE_COUNT (3)
const char CONSOLE_HEADER[DEBUG_HEADEER_LINE_COUNT][DEBUG_LOG_STRING_LENGTH] =
{
	"=========================\n",
	"| Debug Mode            |\n",
	"=========================\n"
};

namespace debug
{
	// Static変数
	DebugView Debug::debug_view_ = DebugView::Menu;
	char Debug::log_lines_[DEBUG_LOG_LINE_MAX][DEBUG_LOG_STRING_LENGTH] = { 0 };
	int Debug::log_line_count_ = 0;
	int Debug::log_interval_count_ = 0;

	bool Debug::draw_physics_wireframe = false;
	bool Debug::draw_sprite_wireframe = false;

	StopWatch Debug::stop_watches_[DEBUG_STOP_WATCH_NUM];

	// 初期化処理
	void Debug::Init()
	{
		log_line_count_ = 0;
	}

	// 更新処理
	void Debug::Draw()
	{
		++log_interval_count_ %= (DEBUG_UPDATE_INTERVAL + 1);

		if (input::Input::Instance()->GetButtonDown(input::InputButton::Function1))
		{
			debug_view_ = DebugView::Menu;
		}
		else if (input::Input::Instance()->GetButtonDown(input::InputButton::Function2))
		{
			debug_view_ = DebugView::Performance;
		}
		else if (input::Input::Instance()->GetButtonDown(input::InputButton::Function3))
		{
			debug_view_ = DebugView::Visualization;
		}

		if (log_interval_count_ == 0)
		{
			system("cls");

			// ヘッダー表示
			ShawHeader();

			switch (debug_view_)
			{
			case debug::Menu:
			{
				ShawMenu();
			}
				break;

			case debug::Performance:
			{
				ShawPerformance();
			}
				break;

			case debug::Visualization:
			{
				ShawVisualization();
			}
				break;
			default:
			{
				ShawMenu();
			}
				break;
			}

			// ログを表示
			for (int i = 0;i < log_line_count_ + 1;++i)
			{
				printf("%s\n", &log_lines_[i][0]);
			}

			// 
		}
	}

	// 終了処理
	void Debug::Uninit()
	{

	}

	//==========================================================
	// 概要  :ログを表示させます。
	// 引数  :ログの内容。printfと同じ。
	// 説明  :同時に表示できるログの数には限りがあります。
	//        もし上限に達したら古いのから削除されます。
	//==========================================================
	void Debug::Log(char *format, ...)
	{
		int insert_line;	// 新しくログを挿入する行

		// もしLineの上限まで来たら最古のログは消える
		if (log_line_count_ == DEBUG_LOG_LINE_MAX)
		{
			for (int i = 1;i < log_line_count_;++i)
			{
				strcpy_s(&log_lines_[i - 1][0], DEBUG_LOG_STRING_LENGTH, &log_lines_[i][0]);
			}
			insert_line = DEBUG_LOG_LINE_MAX - 1;
		}
		else
		{
			insert_line = log_line_count_++;
		}

		va_list list;
		char *current;
		char buffer[1024] = { "\0" };
		char wark[32];

		va_start(list, format);
		current = format;
		while (*current)
		{
			if (*current != '%')
			{
				sprintf_s(wark, "%c", *current);
			}
			else
			{
				++current;

				switch (*current)
				{
				case 'd':
				{
					sprintf_s(wark, "%d", va_arg(list, int));
				}
				break;

				case 'f':
				{
					sprintf_s(wark, "%.2f", va_arg(list, double));
				}
				break;

				case 's':
				{
					sprintf_s(wark, "%s", va_arg(list, char *));
				}
				break;

				case 'c':
				{
					sprintf_s(wark, "%c", va_arg(list, char));
				}
				break;

				default:
				{
					sprintf_s(wark, "%c", *current);
				}
				break;
				}
			}
			strcat_s(buffer, wark);

			++current;
		}

		va_end(list);

		strcpy_s(&log_lines_[insert_line][0], DEBUG_LOG_STRING_LENGTH, buffer);
	}

	//==========================================================
	// 概要  :ログをクリアする
	//==========================================================
	void Debug::ClaerLog()
	{
		log_line_count_ = 0;
	}

	//==========================================================
	// 概要  :プログラム上でプレークポイントを付ける
	// 引数  :Breakする条件を設定することもできる。なくてもいい。
	//==========================================================
	void Debug::BreakPoint(bool condition)
	{
		if (condition)
			_CrtDbgBreak();
	}

	//==========================================================
	// 概要  :警告のメッセージボックスを表示します。
	// 引数  :警告文
	//==========================================================
	void Debug::WarningBox(const char *text)
	{
		MessageBox(NULL, text, "Warning!", MB_ICONWARNING);
	}

	// ヘッダーを表示
	void Debug::ShawHeader()
	{
		for (int i = 0;i < DEBUG_HEADEER_LINE_COUNT;++i)
		{
			printf("%s", &CONSOLE_HEADER[i][0]);
		}
	}

#define DEBUG_MENU_LINE_COUNT (5)
	const char DEBUG_MENU_TEXT[DEBUG_MENU_LINE_COUNT][DEBUG_LOG_STRING_LENGTH] =
	{
		"== 利用したい機能を選択してください ==",
		"F1:メニュー",
		"F2:性能表示",
		"F3:デバック表示",
		"F4:"
	};

	//==========================================================
	// 概要  :メニューを表示します。
	//==========================================================
	void Debug::ShawMenu()
	{
		for (int i = 0;i < DEBUG_MENU_LINE_COUNT;++i)
		{
			printf("%s\n", &DEBUG_MENU_TEXT[i][0]);
		}

	}

	//==========================================================
	// 概要  :性能表示を行います。
	//==========================================================
	void Debug::ShawPerformance()
	{
		ShawMenu();

		printf("\n");

		printf("== 性能表示です ==\n");
		printf("FPS      :%d\n", shadowpartner::Time::Instance()->current_fps_);
		printf("TimeScale:%.2f\n", shadowpartner::Time::Instance()->GetTimeScale());
		printf("DeltaTime:%7.4f\n", (float)shadowpartner::Time::Instance()->delta_time_ / 1000.0f);
		printf("AppTime  :%7.2f秒\n", (float)shadowpartner::Time::Instance()->app_time_ / 1000.0f);

		for (int i = 0;i < DEBUG_STOP_WATCH_NUM;++i)
		{
			printf("ストップウォッチ%d:%dms\n", i, stop_watches_[i].finish_ - stop_watches_[i].start_);
		}
	}

	//==========================================================
	// 概要  :デバック用に可視化します
	//==========================================================
	void Debug::ShawVisualization()
	{
		ShawMenu();

		printf("\n");

		printf("== 可視化の状態 ==\n");
		printf("当たり判定:%s\n", (draw_physics_wireframe) ? ("true") : ("false"));
		printf(" static:青  dynamic:赤\n");
		printf("スプライト:%s\n", (draw_sprite_wireframe) ? ("true") : ("false"));
	}

	//==========================================================
	// 概要  :ストップウォッチの計測を開始します。
	// 引数  :ストップウォッチの番号
	//==========================================================
	void Debug::StopWatchStart(int index)
	{
		if (index >= 0 || index < DEBUG_STOP_WATCH_NUM)
		{
			stop_watches_[index].start_ = timeGetTime();
		}
	}
	//==========================================================
	// 概要  :ストップウォッチの計測を終了します。
	// 引数  :ストップウォッチの番号
	//==========================================================
	void Debug::StopWatchFinish(int index)
	{
		if (index >= 0 || index < DEBUG_STOP_WATCH_NUM)
		{
			stop_watches_[index].finish_ = timeGetTime();
		}
	}

}
