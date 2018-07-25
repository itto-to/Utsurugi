//=============================================================================
//
// サウンド処理 [sound.h]
// Author : 
//
//=============================================================================
#ifndef _SOUND_H_
#define _SOUND_H_

#include <xaudio2.h>

namespace sound
{
	// サウンドファイル
	typedef enum
	{
		SOUND_LABEL_BGM_INTRO = 0,		// スタート画面BGM
		SOUND_LABEL_BGM_STAGE,			// ステージBGM
		SOUND_LABEL_BGM_STAGE_LOOP,		// ステージBGM　ループバージョン
		SOUND_LABEL_SE_CURSOR,			// スタート画面　選択カーソル
		SOUND_LABEL_SE_CHOOSE,			// スタート画面　決定ボタン
		//SOUND_LABEL_SE_SHOT,		// 弾発射音
		//SOUND_LABEL_SE_EXPLOSION,	// 爆発音
		//SOUND_LABEL_SE_COIN,		// 衝突音0
		SOUND_LABEL_MAX,
	} SOUND_LABEL;

	//*****************************************************************************
	// プロトタイプ宣言
	//*****************************************************************************
	HRESULT InitSound(HWND hWnd);
	void UninitSound(void);
	HRESULT PlaySound(SOUND_LABEL label);
	void StopSound(SOUND_LABEL label);
	void StopSound(void);
}
#endif
