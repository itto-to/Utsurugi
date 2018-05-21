//==========================================================
// 概要  :まとめてインクルードする用
// Author:Itsuki Namito
// Copyright(c) Utsurugi.All right reserved.
//==========================================================

#ifndef _INCLUDE_INCLUDE_H_
#define _INCLUDE_INCLUDE_H_

//**********************************************************
// インクルードファイル
//**********************************************************
// デバッグ用のインクルード
#ifdef _DEBUG
#include "../src/Base/Debug/debugger.h"
#endif

// システム系のインクルード
#include "../src/Base/System/scene.h"
#include "../src/Base/System/scene_manager.h"
#include "../src/Base/Element/component.h"
#include "../src/Base/Element/transform.h"
#include "../src/Base/Element/gameobject.h"

// 2D関係のインクルード
#include "../src/Base/2D/camera.h"
#include "../src/Base/2D/sprite.h"

// 入力処理のインクルード
#include "../src/Base/Input/input.h"

// 算術処理のインクルード
#include "../src/Base/Math/math.h"

// using
using namespace input;
using namespace math;
using namespace debug;

#endif