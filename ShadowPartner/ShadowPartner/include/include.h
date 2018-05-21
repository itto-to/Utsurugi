//==========================================================
// �T�v  :�܂Ƃ߂ăC���N���[�h����p
// Author:Itsuki Namito
// Copyright(c) Utsurugi.All right reserved.
//==========================================================

#ifndef _INCLUDE_INCLUDE_H_
#define _INCLUDE_INCLUDE_H_

//**********************************************************
// �C���N���[�h�t�@�C��
//**********************************************************
// �f�o�b�O�p�̃C���N���[�h
#ifdef _DEBUG
#include "../src/Base/Debug/debugger.h"
#endif

// �V�X�e���n�̃C���N���[�h
#include "../src/Base/System/scene.h"
#include "../src/Base/System/scene_manager.h"
#include "../src/Base/Element/component.h"
#include "../src/Base/Element/transform.h"
#include "../src/Base/Element/gameobject.h"

// 2D�֌W�̃C���N���[�h
#include "../src/Base/2D/camera.h"
#include "../src/Base/2D/sprite.h"

// ���͏����̃C���N���[�h
#include "../src/Base/Input/input.h"

// �Z�p�����̃C���N���[�h
#include "../src/Base/Math/math.h"

// using
using namespace input;
using namespace math;
using namespace debug;

#endif