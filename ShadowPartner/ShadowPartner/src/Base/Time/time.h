//==========================================================
// �T�v  :���ԏ���
// Author:Itsuki Namito
// Copyright(c) Utsurugi.All right reserved.
//==========================================================

#ifndef _BASE_TIME_TIME_H_
#define _BASE_TIME_TIME_H_

namespace shadowpartner
{

//**********************************************************
// �C���N���[�h�t�@�C��
//**********************************************************
#include <windows.h>

	//==========================================================
	// �T�v  :���Ԋ֌W�̏������s���N���X
	//==========================================================
	class Time
	{
	public:
		// variables
		DWORD start_time_;			// �^�C�}�[�̌v���J�n����
		DWORD last_exe_time_;		// 1�O��Update���J�n��������
		DWORD current_time_;		// ���݂̎���
		DWORD delta_time_;			// 1�O��Update�ɂ�����������
		DWORD unscaled_delta_time_;	// time_scale_�Ɉˑ����Ȃ��Ō�̃t���[������̍���
		DWORD current_fps_;			// ���݂�FPS
		DWORD app_time_;			// �Q�[���̋N������

		// methods
		static Time *Instance();
		void Update();				// 
		bool CheckUpdate();			// Update���邩���肷��

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

		int frame_count_;			// ���ۂ�FPS���v��
		DWORD last_fps_time_;		// �Ō��FPS�̌v�����X�V��������
		int fps_;					// FPS�̖ڕW�l
		DWORD time_scale_;			// ���Ԃ̈��k��


		// methods
		// ���p�֎~
		Time(const Time &t) {};
		Time &operator=(const Time &) { return *this; };

	};
}
#endif