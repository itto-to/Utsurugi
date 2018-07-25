//=============================================================================
//
// �T�E���h���� [sound.h]
// Author : 
//
//=============================================================================
#ifndef _SOUND_H_
#define _SOUND_H_

#include <xaudio2.h>

namespace sound
{
	// �T�E���h�t�@�C��
	typedef enum
	{
		SOUND_LABEL_BGM_INTRO = 0,		// �X�^�[�g���BGM
		SOUND_LABEL_BGM_STAGE,			// �X�e�[�WBGM
		SOUND_LABEL_BGM_STAGE_LOOP,		// �X�e�[�WBGM�@���[�v�o�[�W����
		SOUND_LABEL_SE_CURSOR,			// �X�^�[�g��ʁ@�I���J�[�\��
		SOUND_LABEL_SE_CHOOSE,			// �X�^�[�g��ʁ@����{�^��
		//SOUND_LABEL_SE_SHOT,		// �e���ˉ�
		//SOUND_LABEL_SE_EXPLOSION,	// ������
		//SOUND_LABEL_SE_COIN,		// �Փˉ�0
		SOUND_LABEL_MAX,
	} SOUND_LABEL;

	//*****************************************************************************
	// �v���g�^�C�v�錾
	//*****************************************************************************
	HRESULT InitSound(HWND hWnd);
	void UninitSound(void);
	HRESULT PlaySound(SOUND_LABEL label);
	void StopSound(SOUND_LABEL label);
	void StopSound(void);
}
#endif
