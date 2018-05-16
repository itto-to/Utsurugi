//==========================================================
// �T�v  :���ԏ���
// Author:Itsuki Namito
// Copyright(c) Utsurugi.All right reserved.
//==========================================================
#include "time.h"

namespace shadowpartner
{

	//**********************************************************
	// �萔
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

	// �R���X�g���N�^
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

	// �f�X�g���N�^
	Time::~Time()
	{
		if (instance_ != nullptr)
		{
			delete instance_;
			instance_ = nullptr;
		}
	}

	//==========================================================
	// �T�v  :�^�C�}�[�̍X�V�����B
	//==========================================================
	void Time::Update()
	{
		current_time_ = timeGetTime();
		app_time_ = current_time_ - start_time_;

		DWORD fps_count_delta = current_time_ - last_fps_time_; // �Ō��FPS�̌v�������Ă���o�߂�������

		// FPS�̌v��
		if (fps_count_delta >= UPDATE_FPS_COUNT)
		{
			current_fps_ = frame_count_ * ((float)UPDATE_FPS_COUNT / (float)fps_count_delta);
			last_fps_time_ = current_time_;
			frame_count_ = 0;
		}
	}

	//==========================================================
	// �T�v  :�t���[���̍X�V���s�������肵�܂��B
	// �߂�l:�X�V����Ȃ�true�B���Ȃ��Ȃ�false�B
	//==========================================================
	bool Time::CheckUpdate()
	{
		DWORD unscaled_elapsed_time = current_time_ - last_exe_time_;
		DWORD elapsed_time = unscaled_elapsed_time * time_scale_; // �Ō��Update����̌o�ߎ���
		
		if (elapsed_time >= 1000 / fps_)
		{
			// Update���s��
			++frame_count_;

			//�t���[���Ԃ̎��Ԃ��L�^����B
			unscaled_delta_time_ = unscaled_elapsed_time;
			delta_time_ = elapsed_time;

			last_exe_time_ = current_time_;
			return true;
		}

		return false;
	}

	//==========================================================
	// �T�v  :FPS��ݒ肵�܂��B�ݒ肳�ꂽ�͈͂ŃN�����v���܂��B
	//==========================================================
	void Time::SetFps(int fps)
	{
		fps_ = (fps > FPS_MAX) ? FPS_MAX : (fps < FPS_MIN) ? FPS_MIN : fps;
	}

	//==========================================================
	// �T�v  :FPS���擾���܂��B
	//==========================================================
	int Time::GetFps()
	{
		return fps_;
	}

	//==========================================================
	// �T�v  :���Ԃ̈��k����ݒ肵�܂��B
	//        �w�肳�ꂽ�͈͂ŃN�����v���܂��B
	//==========================================================
	void Time::SetTimeScale(float time_scale)
	{
		time_scale_ = (time_scale > TIME_SCALE_MAX) ? TIME_SCALE_MAX :
			(time_scale < TIME_SCALE_MIN) ? TIME_SCALE_MIN : time_scale;
	}

	//==========================================================
	// �T�v  :���Ԃ̈��k�����擾���܂��B
	//==========================================================
	float Time::GetTimeScale()
	{
		return time_scale_;
	}
}
