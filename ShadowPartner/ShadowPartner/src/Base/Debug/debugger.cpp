//==========================================================
// �T�v  :�f�o�b�O�p�̃N���X
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
#define DEBUG_LOG_LINE_MAX (5)			// �����ɕ\���ł��郍�O�̐�

#define DEBUG_HEADEER_LINE_COUNT (3)
const char CONSOLE_HEADER[DEBUG_HEADEER_LINE_COUNT][DEBUG_LOG_STRING_LENGTH] =
{
	"=========================\n",
	"| Debug Mode            |\n",
	"=========================\n"
};

namespace debug
{
	// Static�ϐ�
	DebugView Debug::debug_view_ = DebugView::Menu;
	char Debug::log_lines_[DEBUG_LOG_LINE_MAX][DEBUG_LOG_STRING_LENGTH] = { 0 };
	int Debug::log_line_count_ = 0;
	int Debug::log_interval_count_ = 0;

	bool Debug::draw_physics_wireframe = false;
	bool Debug::draw_sprite_wireframe = false;

	StopWatch Debug::stop_watches_[DEBUG_STOP_WATCH_NUM];

	// ����������
	void Debug::Init()
	{
		log_line_count_ = 0;
	}

	// �X�V����
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

			// �w�b�_�[�\��
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

			// ���O��\��
			for (int i = 0;i < log_line_count_ + 1;++i)
			{
				printf("%s\n", &log_lines_[i][0]);
			}

			// 
		}
	}

	// �I������
	void Debug::Uninit()
	{

	}

	//==========================================================
	// �T�v  :���O��\�������܂��B
	// ����  :���O�̓��e�Bprintf�Ɠ����B
	// ����  :�����ɕ\���ł��郍�O�̐��ɂ͌��肪����܂��B
	//        ��������ɒB������Â��̂���폜����܂��B
	//==========================================================
	void Debug::Log(char *format, ...)
	{
		int insert_line;	// �V�������O��}������s

		// ����Line�̏���܂ŗ�����ŌẪ��O�͏�����
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
	// �T�v  :���O���N���A����
	//==========================================================
	void Debug::ClaerLog()
	{
		log_line_count_ = 0;
	}

	//==========================================================
	// �T�v  :�v���O������Ńv���[�N�|�C���g��t����
	// ����  :Break���������ݒ肷�邱�Ƃ��ł���B�Ȃ��Ă������B
	//==========================================================
	void Debug::BreakPoint(bool condition)
	{
		if (condition)
			_CrtDbgBreak();
	}

	//==========================================================
	// �T�v  :�x���̃��b�Z�[�W�{�b�N�X��\�����܂��B
	// ����  :�x����
	//==========================================================
	void Debug::WarningBox(const char *text)
	{
		MessageBox(NULL, text, "Warning!", MB_ICONWARNING);
	}

	// �w�b�_�[��\��
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
		"== ���p�������@�\��I�����Ă������� ==",
		"F1:���j���[",
		"F2:���\�\��",
		"F3:�f�o�b�N�\��",
		"F4:"
	};

	//==========================================================
	// �T�v  :���j���[��\�����܂��B
	//==========================================================
	void Debug::ShawMenu()
	{
		for (int i = 0;i < DEBUG_MENU_LINE_COUNT;++i)
		{
			printf("%s\n", &DEBUG_MENU_TEXT[i][0]);
		}

	}

	//==========================================================
	// �T�v  :���\�\�����s���܂��B
	//==========================================================
	void Debug::ShawPerformance()
	{
		ShawMenu();

		printf("\n");

		printf("== ���\�\���ł� ==\n");
		printf("FPS      :%d\n", shadowpartner::Time::Instance()->current_fps_);
		printf("TimeScale:%.2f\n", shadowpartner::Time::Instance()->GetTimeScale());
		printf("DeltaTime:%7.4f\n", (float)shadowpartner::Time::Instance()->delta_time_ / 1000.0f);
		printf("AppTime  :%7.2f�b\n", (float)shadowpartner::Time::Instance()->app_time_ / 1000.0f);

		for (int i = 0;i < DEBUG_STOP_WATCH_NUM;++i)
		{
			printf("�X�g�b�v�E�H�b�`%d:%dms\n", i, stop_watches_[i].finish_ - stop_watches_[i].start_);
		}
	}

	//==========================================================
	// �T�v  :�f�o�b�N�p�ɉ������܂�
	//==========================================================
	void Debug::ShawVisualization()
	{
		ShawMenu();

		printf("\n");

		printf("== �����̏�� ==\n");
		printf("�����蔻��:%s\n", (draw_physics_wireframe) ? ("true") : ("false"));
		printf(" static:��  dynamic:��\n");
		printf("�X�v���C�g:%s\n", (draw_sprite_wireframe) ? ("true") : ("false"));
	}

	//==========================================================
	// �T�v  :�X�g�b�v�E�H�b�`�̌v�����J�n���܂��B
	// ����  :�X�g�b�v�E�H�b�`�̔ԍ�
	//==========================================================
	void Debug::StopWatchStart(int index)
	{
		if (index >= 0 || index < DEBUG_STOP_WATCH_NUM)
		{
			stop_watches_[index].start_ = timeGetTime();
		}
	}
	//==========================================================
	// �T�v  :�X�g�b�v�E�H�b�`�̌v�����I�����܂��B
	// ����  :�X�g�b�v�E�H�b�`�̔ԍ�
	//==========================================================
	void Debug::StopWatchFinish(int index)
	{
		if (index >= 0 || index < DEBUG_STOP_WATCH_NUM)
		{
			stop_watches_[index].finish_ = timeGetTime();
		}
	}

}
